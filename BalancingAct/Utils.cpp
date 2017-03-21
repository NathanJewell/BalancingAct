#include "Utils.hpp"

using namespace utils;

inline double linear(const double& in)
{
	return in;
}

inline double sigmoid(const double& in)
{
	return 1 / (1 + pow(2.71828, in));
}

inline double step(const double& in)
{
	if (in > .5)
	{
		return 1;
	}
	return 0;
}

inline double squaredErr(const double& in)
{
	return .5*pow(in, 2);
}