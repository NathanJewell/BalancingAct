#pragma once
#include <math.h>
#define LEARNINGRATE .5

namespace utils
{
	inline double linear(const double& in);
	inline double linearD(const double& in);

	inline double sigmoid(const double& in);
	inline double sigmoidD(const double& in);

	inline double step(const double& in);
	inline double stepD(const double& in);

	inline double squaredErr(const double& in);

	inline double random();

	
}