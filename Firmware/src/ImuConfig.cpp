/**
 * @file ImuConfig.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include <ImuConfig.h>

namespace ImuConfig
{
#if ES3011_BOT_ID == 0
	const float vel_x_cal = -0.0767443330f;
	const float vel_y_cal = +0.0393428880f;
	const float vel_z_cal = +0.0022024342f;
	const float vel_var = 0.0000035204512f;
	const float acc_var = 0.0012492317000f;
#elif ES3011_BOT_ID == 1
	const float vel_x_cal = -0.0138670760f;
	const float vel_y_cal = -0.0743288400f;
	const float vel_z_cal = -0.0213452480f;
	const float vel_var = 0.0000040159848f;
	const float acc_var = 0.0010868423000f;
#elif ES3011_BOT_ID == 2
	const float vel_x_cal = +0.0332801940f;
	const float vel_y_cal = +0.0021518338f;
	const float vel_z_cal = -0.0119056640f;
	const float vel_var = 0.0000057464463f;
	const float acc_var = 0.0005833894200f;
#elif ES3011_BOT_ID == 3
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 4
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 5
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 6
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 7
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 8
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 9
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 10
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 11
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 12
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 13
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 14
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 15
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 16
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 17
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 18
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 19
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#elif ES3011_BOT_ID == 20
	const float vel_x_cal = +0.0f;
	const float vel_y_cal = +0.0f;
	const float vel_z_cal = +0.0f;
	const float vel_var = 0.0f;
	const float acc_var = 0.0f;
#else
#error Must define ES3011_BOT_ID in range [0, 20]
#endif
}