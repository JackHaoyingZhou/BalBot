/**
 * @file GRV.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "GRV.h"
#include <CppUtil.h>
using CppUtil::square;

/**
 * @brief Constructs Gaussian
 * @param mean Mean
 * @param var Variance
 */
GRV::GRV(float mean, float var)
{
	this->mean = mean;
	this->var = var;
}

/**
 * @brief Constructs standard normal Gaussian (mean = 0, var = 1)
 */
GRV::GRV()
{
	this->mean = 0.0f;
	this->var = 1.0f;
}

/**
 * @brief Gaussian sine
 */
GRV sin(const GRV& g)
{
	return GRV(sinf(g.mean), g.var * square(cosf(g.mean)));
}

/**
 * @brief Gaussian cosine
 */
GRV cos(const GRV& g)
{
	return GRV(cosf(g.mean), g.var * square(sinf(g.mean)));
}

/**
 * @brief Gaussian tangent
 */
GRV tan(const GRV& g)
{
	return GRV(tanf(g.mean), g.var * square(1.0f / square(cosf(g.mean))));
}

/**
 * @brief Gaussian inverse sine
 */
GRV asin(const GRV& g)
{
	return GRV(asinf(g.mean), g.var / fabsf(1.0f - square(g.mean)));
}

/**
 * @brief Gaussian inverse cosine
 */
GRV acos(const GRV& g)
{
	return GRV(acosf(g.mean), g.var / fabsf(1.0f - square(g.mean)));
}

/**
 * @brief Gaussian inverse tangent
 */
GRV atan(const GRV& g)
{
	return GRV(atanf(g.mean), g.var / square(1.0f + square(g.mean)));
}

/**
 * @brief Gaussian hyperbolic sine
 */
GRV sinh(const GRV& g)
{
	return GRV(sinhf(g.mean), g.var * square(coshf(g.mean)));
}

/**
 * @brief Gaussian hyperbolic cosine
 */
GRV cosh(const GRV& g)
{
	return GRV(coshf(g.mean), g.var * square(sinhf(g.mean)));
}

/**
 * @brief Gaussian hyperbolic tangent
 */
GRV tanh(const GRV& g)
{
	const float tanhm = tanhf(g.mean);
	return GRV(tanhm, g.var * square(1.0f - square(tanhm)));
}

/**
 * @brief Gaussian square root
 */
GRV sqrt(const GRV& g)
{
	return GRV(sqrtf(g.mean), g.var / (4.0f * fabsf(g.mean)));
}

/**
 * @brief Gaussian natural exponential
 */
GRV exp(const GRV& g)
{
	const float expm = exp(g.mean);
	return GRV(expm, g.var * square(expm));
}

/**
 * @brief Gaussian natural logarithm
 */
GRV log(const GRV& g)
{
	return GRV(logf(g.mean), g.var / square(g.mean));
}

/**
 * @brief Gaussian atan2(y, x)
 */
GRV atan2(const GRV& gy, const GRV& gx)
{
	const float mean = atan2f(gy.mean, gx.mean);
	const float x_sq = square(gx.mean);
	const float y_sq = square(gy.mean);
	const float var = (x_sq * gy.var + y_sq * gx.var) / square(x_sq + y_sq);
	return GRV(mean, var);
}

/**
 * @brief Gaussian fusion (point-by-point correlation)
 */
GRV fuse(const GRV& lhs, const GRV& rhs)
{
	const float var_sum_inv = 1.0f / (lhs.var + rhs.var);
	const float mean = (lhs.mean * rhs.var + rhs.mean * lhs.var) * var_sum_inv;
	const float var = lhs.var * rhs.var * var_sum_inv;
	return GRV(mean, var);
}

/**
 * @brief Gaussian negation
 */
GRV operator-(const GRV& g)
{
	return GRV(-g.mean, g.var);
}

/**
 * @brief Gaussian-scalar addition
 */
GRV operator+(const GRV& g, float n)
{
	return GRV(g.mean + n, g.var);
}

/**
 * @brief Gaussian-scalar subtraction
 */
GRV operator-(const GRV& g, float n)
{
	return GRV(g.mean - n, g.var);
}

/**
 * @brief Gaussian-scalar multiplication
 */
GRV operator*(const GRV& g, float n)
{
	return GRV(g.mean * n, g.var * square(n));
}

/**
 * @brief Gaussian-scalar division
 */
GRV operator/(const GRV& g, float n)
{
	return g * (1.0f / n);
}

/**
 * @brief Gaussian-scalar exponentiation
 */
GRV operator^(const GRV& g, float n)
{
	const float mean = powf(g.mean, n);
	const float var = g.var * square(n * powf(g.mean, n - 1.0f));
	return GRV(mean, var);
}

/**
 * @brief Gaussian addition
 */
GRV operator+(const GRV& lhs, const GRV& rhs)
{
	return GRV(lhs.mean + rhs.mean, lhs.var + rhs.var);
}

/**
 * @brief Gaussian subtraction
 */
GRV operator-(const GRV& lhs, const GRV& rhs)
{
	return GRV(lhs.mean - rhs.mean, lhs.var + rhs.var);
}

/**
 * @brief Gaussian multiplication
 */
GRV operator*(const GRV& lhs, const GRV& rhs)
{
	const float mean = lhs.mean * rhs.mean;
	const float var = square(lhs.mean) * rhs.var + square(rhs.mean) * lhs.var;
	return GRV(mean, var);
}

/**
 * @brief Gaussian division
 */
GRV operator/(const GRV& lhs, const GRV& rhs)
{
	const float mean = lhs.mean / rhs.mean;
	const float del_lhs_sq = 1.0f / square(rhs.mean);
	const float del_rhs_sq = square(lhs.mean * del_lhs_sq);
	const float var = del_lhs_sq * lhs.var + del_rhs_sq * rhs.var;
	return GRV(mean, var);
}

/**
 * @brief Gaussian exponentiation
 */
GRV operator^(const GRV& lhs, const GRV& rhs)
{
	const float mean = powf(lhs.mean, rhs.mean);
	const float del_lhs = rhs.mean * powf(lhs.mean, rhs.mean - 1.0f);
	const float del_rhs = mean * logf(lhs.mean);
	const float var = square(del_lhs) * lhs.var + square(del_rhs) * rhs.var;
	return GRV(mean, var);
}
