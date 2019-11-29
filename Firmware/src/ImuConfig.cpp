/**
 * @file ImuConfig.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include <ImuConfig.h>

/**
 * Namespace Definitions
 */
namespace ImuConfig
{
#if ES3011_BOT_ID == 0
	#warning NOT RECALIBRATED!
	const float gyr_x_cal = +0.0000000000000f;
	const float gyr_y_cal = +0.0000000000000f;
	const float gyr_z_cal = +0.0000000000000f;
	const float gyr_x_var = 0.00000000000000f;
	const float gyr_y_var = 0.00000000000000f;
	const float gyr_z_var = 0.00000000000000f;
	const float acc_x_var = 0.00000000000000f;
	const float acc_y_var = 0.00000000000000f;
	const float acc_z_var = 0.00000000000000f;
#elif ES3011_BOT_ID == 1
	const float gyr_x_cal = +0.0003701793300f;
	const float gyr_y_cal = -0.0758841110000f;
	const float gyr_z_cal = -0.0199697190000f;
	const float gyr_x_var = 0.00000215523980f;
	const float gyr_y_var = 0.00000358851340f;
	const float gyr_z_var = 0.00000316657540f;
	const float acc_x_var = 0.00077350164000f;
	const float acc_y_var = 0.00102186380000f;
	const float acc_z_var = 0.00129695180000f;
#elif ES3011_BOT_ID == 2
	#warning NOT RECALIBRATED!
	const float gyr_x_cal = +0.0000000000000f;
	const float gyr_y_cal = +0.0000000000000f;
	const float gyr_z_cal = +0.0000000000000f;
	const float gyr_x_var = 0.00000000000000f;
	const float gyr_y_var = 0.00000000000000f;
	const float gyr_z_var = 0.00000000000000f;
	const float acc_x_var = 0.00000000000000f;
	const float acc_y_var = 0.00000000000000f;
	const float acc_z_var = 0.00000000000000f;
#elif ES3011_BOT_ID == 3
	const float gyr_x_cal = -0.0461459160000f;
	const float gyr_y_cal = +0.0048815743000f;
	const float gyr_z_cal = -0.0158524590000f;
	const float gyr_x_var = 0.00000366372610f;
	const float gyr_y_var = 0.00000603395980f;
	const float gyr_z_var = 0.00000371762870f;
	const float acc_x_var = 0.00102829980000f;
	const float acc_y_var = 0.00118071350000f;
	const float acc_z_var = 0.00219102880000f;
#else
#error Must define ES3011_BOT_ID in range [0, 20]
#endif
}