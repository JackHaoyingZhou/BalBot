/**
 * @file EncoderDir.h
 * @brief Namespace for encoder direction constant.
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once

namespace EncoderDir
{
#if ES3011_BOT_ID == 0
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 1
	const float dir = -1.0f;
#elif ES3011_BOT_ID == 2
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 3
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 4
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 5
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 6
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 7
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 8
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 9
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 10
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 11
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 12
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 13
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 14
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 15
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 16
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 17
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 18
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 19
	const float dir = +1.0f;
#elif ES3011_BOT_ID == 20
	const float dir = +1.0f;
#else
#error Must define ES3011_BOT_ID in range [0,20]
#endif
}