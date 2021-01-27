/**
 * @file CppUtil.h
 * @brief Collection of commonly-used C++ functions
 * @author Dan Oates (WPI Class of 2020)
 */
#pragma once
#include <stdint.h>
#include <math.h>

/**
 * Namespace Declaration
 */
namespace CppUtil
{
	// Math Functions
	template <typename T> T add(T x, T y);
	template <typename T> T sub(T x, T y);
	template <typename T> T mul(T x, T y);
	template <typename T> T div(T x, T y);
	template <typename T> T square(T x);
	template <typename T> T min(T x, T y);
	template <typename T> T max(T x, T y);
	template <typename T> T clamp(T x, T x_min, T x_max);
	float wrap(float x, float x_min, float x_max);

	// Array Functions
	template <typename Ta, typename Ti> Ti find(Ta arr[], Ta val, Ti len, bool& found);
	template <typename Ta, typename Ti> Ti arg_min(Ta arr[], Ti len);
	template <typename Ta, typename Ti> Ti arg_max(Ta arr[], Ti len);
	template <typename Ta, typename Ti> Ta mean(Ta arr[], Ti len);
	template <typename Ta, typename Ti> Ta var(Ta arr[], Ti len, Ta mean);
	template <typename Ta, typename Ti> Ta var(Ta arr[], Ta len);
	template <typename Ti> float std(float arr[], Ti len, float mean);
	template <typename Ti> float std(float arr[], Ti len);
}

/**
 * @brief Generic addition x + y
 */
template <typename T>
T CppUtil::add(T x, T y)
{
	return x + y;
}

/**
 * @brief Generic subtraction x - y
 */
template <typename T>
T CppUtil::sub(T x, T y)
{
	return x - y;
}

/**
 * @brief Generic multiplication x * y
 */
template <typename T>
T CppUtil::mul(T x, T y)
{
	return x * y;
}

/**
 * @brief Generic division x / y
 */
template <typename T>
T CppUtil::div(T x, T y)
{
	return x / y;
}

/**
 * @brief Generic square x^2
 */
template <typename T>
T CppUtil::square(T x)
{
	return x * x;
}

/**
 * @brief Returns minimum of x and y
 */
template <typename T>
T CppUtil::min(T x, T y)
{
	return (x < y) ? x : y;
}

/**
 * @brief Returns maximum of x and y
 */
template <typename T>
T CppUtil::max(T x, T y)
{
	return (x > y) ? x : y;
}

/**
 * @brief Clamp limits x to range [x_min, x_max]
 */
template <typename T>
T CppUtil::clamp(T x, T x_min, T x_max)
{
	return (x < x_min) ? x_min : (x > x_max) ? x_max : x;
}

/**
 * @brief Finds index of first occurrence of val in arr
 * @param arr Array of data
 * @param val Value to find (with ==)
 * @param len Length of array
 * @param found False if value was not found
 */
template <typename Ta, typename Ti>
Ti CppUtil::find(Ta arr[], Ta val, Ti len, bool& found)
{
	// Search arr for val
	for (Ti i = 0; i < len; i++)
	{
		if (arr[i] == val)
		{
			found = true;
			return i;
		}
	}

	// If not found
	found = false;
	return 0;
}

/**
 * @brief Finds index of min of array
 * @param arr Array of comparable type
 * @param len Length of array
 */
template <typename Ta, typename Ti>
Ti CppUtil::arg_min(Ta arr[], Ti len)
{
	Ta arr_min = arr[0];
	Ti i_min = 0;
	for (Ti i = 1; i < len; i++)
	{
		if (arr[i] < arr_min)
		{
			arr_min = arr[i];
			i_min = i;
		}
	}
	return i_min;
}

/**
 * @brief Finds index of max of array
 * @param arr Array of comparable type
 * @param len Length of array
 */
template <typename Ta, typename Ti>
Ti CppUtil::arg_max(Ta arr[], Ti len)
{
	Ta arr_max = arr[0];
	Ti i_max = 0;
	for (Ti i = 1; i < len; i++)
	{
		if (arr[i] > arr_max)
		{
			arr_max = arr[i];
			i_max = i;
		}
	}
	return i_max;
}

/**
 * @brief Generic array mean
 * @param arr Array of data
 * @param len Length of array
 */
template <typename Ta, typename Ti>
Ta CppUtil::mean(Ta arr[], Ti len)
{
	Ta sum = 0;
	for (Ti i = 0; i < len; i++)
	{
		sum += arr[i];
	}
	return sum / len;
}

/**
 * @brief Generic array variance
 * @param arr Array of data
 * @param len Length of array
 * @param mean Mean of array
 */
template <typename Ta, typename Ti>
Ta CppUtil::var(Ta arr[], Ti len, Ta mean)
{
	Ta sum = 0;
	for (Ti i = 0; i < len; i++)
	{
		sum += square(arr[i] - mean);
	}
	return sum / len;
}

/**
 * @brief Generic array variance
 * @param arr Array of data
 * @param len Length of array
 */
template <typename Ta, typename Ti>
Ta CppUtil::var(Ta arr[], Ta len)
{
	return var(arr, len, mean(arr, len));
}

/**
 * @brief Floating-point standard deviation
 * @param arr Array of floats
 * @param len Length of array
 * @param mean Mean of array
 */
template <typename Ti>
float CppUtil::std(float arr[], Ti len, float mean)
{
	return sqrtf(variance(arr, len, mean));
}

/**
 * @brief Floating-point standard deviation
 * @param arr Array of floats
 * @param len Length of array
 */
template <typename Ti>
float CppUtil::std(float arr[], Ti len)
{
	return stdevf(arr, len, mean(arr, len));
}
