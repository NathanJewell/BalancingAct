#include "Utils.hpp"
#include <ctime>
#include <cmath>
#include <iostream>

using namespace utils;

inline double linear(const double& in)
{
	return in;
}

inline double linearD(const double& in)
{
	//not done
}

inline double sigmoid(const double& in)
{
	return 1 / (1 + pow(2.71828, in));
}

inline double sigmoidD(const double& in)
{
	return in * (1 - in);
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

inline double random()
{
	return ((double)rand() / (RAND_MAX));
}