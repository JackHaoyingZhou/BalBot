/**
 * @file Gaussian.cpp
 * @author Dan Oates (WPI Class of 2020)
 */
#include "Gaussian.h"
#include <math.h>

/**
 * @brief Constructs Gaussian.
 * @param mean Mean
 * @param var Variance
 */
Gaussian::Gaussian(float mean, float var)
{
	this->mean = mean;
	this->var = var;
}

/**
 * @brief Constructs null gaussian (zero mean and variance).
 * WARNING: Do not do operations with this before assigning it!
 */
Gaussian::Gaussian()
{
	this->mean = 0.0f;
	this->var = 0.0f;
}

/**
 * @brief Returns mean of Gaussian.
 */
float Gaussian::get_mean() const
{
	return mean;
}

/**
 * @brief Returns variance of Gaussian.
 */
float Gaussian::get_var() const
{
	return var;
}

/**
 * @brief Gaussian negation
 */
Gaussian operator-(const Gaussian& g)
{
	return Gaussian(-g.mean, g.var);
}

/**
 * @brief Gaussian-scalar addition.
 */
Gaussian operator+(const Gaussian& g, float n)
{
	return Gaussian(g.mean + n, g.var);
}

/**
 * @brief Gaussian-scalar subtraction.
 */
Gaussian operator-(const Gaussian& g, float n)
{
	return Gaussian(g.mean - n, g.var);
}

/**
 * @brief Gaussian-scalar multiplication.
 */
Gaussian operator*(const Gaussian& g, float n)
{
	return Gaussian(g.mean * n, g.var * n * n);
}

/**
 * @brief Gaussian-scalar division.
 */
Gaussian operator/(const Gaussian& g, float n)
{
	const float n_inv = 1.0f / n;
	return Gaussian(g.mean * n_inv, g.var * n_inv * n_inv);
}

/**
 * @brief Gaussian addition.
 */
Gaussian operator+(const Gaussian& g1, const Gaussian& g2)
{
	return Gaussian(g1.mean + g2.mean, g1.var + g2.var);
}

/**
 * @brief Gaussian subtraction.
 */
Gaussian operator-(const Gaussian& g1, const Gaussian& g2)
{
	return Gaussian(g1.mean - g2.mean, g1.var + g2.var);
}

/**
 * @brief Gaussian arc-tangent 2 (linearization).
 * @param gy Gaussian of y
 * @param gx Gaussian of x
 */
Gaussian atan2(const Gaussian& gy, const Gaussian& gx)
{
	const float mean = atan2f(gy.mean, gx.mean);
	const float x_sq = gx.mean * gx.mean;
	const float y_sq = gy.mean * gy.mean;
	const float x_sq_plus_y_sq = x_sq + y_sq;
	const float var =
		(x_sq * gy.var + y_sq * gx.var) / 
		(x_sq_plus_y_sq * x_sq_plus_y_sq);
	return Gaussian(mean, var);
}

/**
 * @brief Kalman-filter Gaussian fusion.
 */
Gaussian fuse(const Gaussian& g1, const Gaussian& g2)
{
	const float var_sum_inv = 1.0f / (g1.var + g2.var);
	const float mean = (g1.mean * g2.var + g2.mean * g1.var) * var_sum_inv;
	const float var = g1.var * g2.var * var_sum_inv;
	return Gaussian(mean, var);
}