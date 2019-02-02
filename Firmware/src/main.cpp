/**
 * @file main.cpp
 * @brief Main control code for BalBot.
 * @author Dan Oates (WPI Class of 2020)
 */
#include <Arduino.h>
#include <HBridgeMotor.h>
#include <Mpu6050.h>
#include <QuadEncoder.h>
#include <PinChangeInt.h>
#include <Timer.h>
#include <Pid.h>
#include <Gaussian.h>
#include <Differentiator.h>

/**
 * Macros
 */

// Program echoes info over USB serial at 115200 baud.
// #define SERIAL_DEBUG

// Disables motor driving.
// #define DISABLE_MOTORS

// Program estimates max control frequency.
// #define GET_MAX_CTRL_FREQ

// Program calculates IMU calibration and uncertainties.
// #define GET_IMU_CAL

/**
 * Pin Definitions
 */
const uint8_t pin_motor_en = 8;	// Motor driver enable (TB6612FNG)
const uint8_t pin_lm_pwm = 9;	// Left motor PWM
const uint8_t pin_lm_fwd = 6;	// Left motor forward enable
const uint8_t pin_lm_rev = 7;	// Left motor reverse enable
const uint8_t pin_lenc_a = 2;	// Left encoder A
const uint8_t pin_lenc_b = 3;	// Left encoder B
const uint8_t pin_rm_pwm = 10;	// Right motor PWM
const uint8_t pin_rm_fwd = 12;	// Right motor forward enable
const uint8_t pin_rm_rev = 13;	// Right motor reverse enable
const uint8_t pin_renc_a = 5;	// Right encoder A
const uint8_t pin_renc_b = 4;	// Right encoder B

/**
 * System Constants
 */

// Robot Physical Constants
const float r_wheel = 0.0336;	// Wheel radius [m]
const float motor_kv = 0.3f;	// Motor back-EMF [V/(rad/s)] 
const float v_bat = 12.0f;		// Battery voltage [V]

// Encoder Constants
const float encoder_cpr = 1320.0f;	// Encoder counts per revolution

// IMU Constants
const float imu_vel_x_cal = -0.0767443330f;	// Gyro x calibration offset [rad/s]
const float imu_vel_y_cal = +0.0393428880f;	// Gyro y calibration offset [rad/s]
const float imu_vel_z_cal = +0.0022024342f;	// Gyro z calibration offset [rad/s]
const float imu_vel_var = 0.0000035204512f;	// Angular velocity variance [(rad/s)^2]
const float imu_acc_var = 0.0012492317000f;	// Acceleration variance [(m/s^2)^2]

// Controller Constants
const float f_ctrl = 200.0f;		// Control frequency [Hz]
const float t_ctrl = 1.0f / f_ctrl;	// Control period [s]
const float pid_pitch_kp = 32.77f;	// Pitch P-gain [V/rad]
const float pid_pitch_ki = 0.0f;	// Pitch I-gain [V/(rad*s)]
const float pid_pitch_kd = 1.947f;	// Pitch D-gain [V/(rad/s)]
const float pitch_max = 0.1f;		// Max pitch command [rad]
const float pid_pos_kp = 1.0;		// Position P-gain [rad/m]
const float pid_pos_ki = 0.0f;		// Position I-gain [rad/(m*s)]
const float pid_pos_kd = 0.1f;		// Position D-gain [rad/(m/s)]

/**
 * Controller Interfaces
 */
Pid pid_pitch(pid_pitch_kp, pid_pitch_ki, pid_pitch_kd, -v_bat, v_bat, f_ctrl);
Pid pid_pos(pid_pos_kp, pid_pos_ki, pid_pos_kd, -pitch_max, pitch_max, f_ctrl);
Differentiator angle_L_diff(f_ctrl);
Differentiator angle_R_diff(f_ctrl);

/**
 * Hardware Interfaces
 */
HBridgeMotor motor_L(pin_lm_pwm, pin_lm_fwd, pin_lm_rev, v_bat);
HBridgeMotor motor_R(pin_rm_pwm, pin_rm_fwd, pin_rm_rev, v_bat);
QuadEncoder encoder_L(pin_lenc_a, pin_lenc_b, encoder_cpr);
QuadEncoder encoder_R(pin_renc_a, pin_renc_b, encoder_cpr);
Mpu6050 imu;
Timer timer;

/**
 * State Variables
 */
Gaussian pitch;
bool first_frame = true;

/**
 * ISRs
 */
void enc_L_isr_A() { encoder_L.interrupt_A(); }
void enc_L_isr_B() { encoder_L.interrupt_B(); }
void enc_R_isr_A() { encoder_R.interrupt_A(); }
void enc_R_isr_B() { encoder_R.interrupt_B(); }

/**
 * @brief Initializes Balbot.
 */
void setup()
{
#ifdef SERIAL_DEBUG
	Serial.begin(115200);
	Serial.println("SERIAL_DEBUG");
#endif

	// Enable motors
	pinMode(pin_motor_en, OUTPUT);
	digitalWrite(pin_motor_en, HIGH);
	motor_L.init();
	motor_R.init();
#ifndef DISABLE_MOTORS
	motor_L.enable();
	motor_R.enable();
#endif

	// Initialize Encoders
	encoder_L.init();
	encoder_R.init();
	attachInterrupt(digitalPinToInterrupt(pin_lenc_a), enc_L_isr_A, CHANGE);
	attachInterrupt(digitalPinToInterrupt(pin_lenc_b), enc_L_isr_B, CHANGE);
	attachPinChangeInterrupt(pin_renc_a, enc_R_isr_A, CHANGE);
	attachPinChangeInterrupt(pin_renc_b, enc_R_isr_B, CHANGE);

	// Initialize IMU
	imu.init();
#ifndef GET_IMU_CAL
	imu.set_gyro_cals(imu_vel_x_cal, imu_vel_y_cal, imu_vel_z_cal);
#else
	imu.calibrate();
	Serial.begin(115200);
	Serial.println("GET_IMU_CAL");
	Serial.println("Gyro X cal: " + String(imu.get_vel_x_cal(), 15));
	Serial.println("Gyro Y cal: " + String(imu.get_vel_y_cal(), 15));
	Serial.println("Gyro Z cal: " + String(imu.get_vel_z_cal(), 15));
	Serial.println("Vel var: " + String(imu.get_vel_variance(), 15));
	Serial.println("Acc var: " + String(imu.get_acc_variance(), 15));
	while(1);
#endif

	// Initialize filters
	angle_L_diff.init();
	angle_R_diff.init();
}

/**
 * Balbot Control Loop.
 */
void loop()
{
	// Start timing
	timer.tic();

	// Read IMU
	imu.update();

	// Estimate pitch from IMU
	Gaussian acc_y(imu.get_acc_y(), imu_acc_var);
	Gaussian acc_z(imu.get_acc_z(), imu_acc_var);
	Gaussian pitch_acc = -atan2(acc_y, acc_z);
	if(first_frame)
	{
		first_frame = false;
		pitch = pitch_acc;
	}
	else
	{
		Gaussian pitch_vel(-imu.get_vel_x(), imu_vel_var);
		Gaussian pitch_gyr = pitch + pitch_vel * t_ctrl;
		pitch = fuse(pitch_gyr, pitch_acc);
	}

	// Estimate position from encoders
	const float angle_L = encoder_L.read();
	const float angle_R = encoder_R.read();
	const float motor_vel_L = angle_L_diff.update(angle_L);
	const float motor_vel_R = angle_R_diff.update(angle_R);
	const float pos = r_wheel * 0.5 * (angle_L + angle_R);

	// Control position with pitch
	const float pitch_setpt = pid_pos.update(0.0f - pos);
	
	// Control pitch with voltage
	const float v_pid = -pid_pitch.update(pitch_setpt - pitch.get_mean());
	const float v_cmd_L = v_pid + motor_kv * motor_vel_L;
	const float v_cmd_R = v_pid + motor_kv * motor_vel_R;

	// Send voltage command to motors
	motor_L.set_voltage(v_cmd_L);
	motor_R.set_voltage(v_cmd_R);

	// Maintain timing
#ifndef GET_MAX_CTRL_FREQ
	timer.wait_until(t_ctrl);
#else
	motor_L.disable();
	motor_R.disable();
	const float f_ctrl_max = 1.0f / timer.toc();
	Serial.begin(115200);
	Serial.println("GET_MAX_CTRL_FREQ");
	Serial.println("Max ctrl freq: " + String(f_ctrl_max));
	while(1);
#endif
}