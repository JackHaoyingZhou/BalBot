/**
 * @file MotorConfig.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include <MotorConfig.h>

namespace MotorConfig
{
#if ES3011_BOT_ID == 0
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 1
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 2
	const float direction = -1.0f;
	const float cnt_per_rev = 2480.0f;
#elif ES3011_BOT_ID == 3
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 4
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 5
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 6
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 7
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 8
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 9
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 10
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 11
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 12
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 13
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 14
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 15
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 16
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 17
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 18
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 19
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#elif ES3011_BOT_ID == 20
	const float direction = +1.0f;
	const float cnt_per_rev = 1320.0f;
#else
#error Must define ES3011_BOT_ID in range [0, 20]
#endif
}