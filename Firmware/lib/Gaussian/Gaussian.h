/**
 * @file Gaussian.h
 * @brief Class for implementing 1-dimensional gaussian random variables.
 * @author Dan Oates (WPI Class of 2020)
 */

class Gaussian
{
public:
	Gaussian(float mean, float var);
	Gaussian();
	float get_mean() const;
	float get_var() const;
	friend Gaussian operator-(const Gaussian& g);
	friend Gaussian operator+(const Gaussian& g, float n);
	friend Gaussian operator-(const Gaussian& g, float n);
	friend Gaussian operator*(const Gaussian& g, float n);
	friend Gaussian operator/(const Gaussian& g, float n);
	friend Gaussian operator+(const Gaussian& g1, const Gaussian& g2);
	friend Gaussian operator-(const Gaussian& g1, const Gaussian& g2);
	friend Gaussian atan2(const Gaussian& gy, const Gaussian& gx);
	friend Gaussian fuse(const Gaussian& g1, const Gaussian& g2);
private:
	float mean, var;
};