#include "Utils.hpp"
#include <ctime>
#include <cmath>
#include <iostream>



 double utils::linear(const double& in)
{
	return in;
}

 double utils::linearD(const double& in)
{
	//not done
	return 0;
}

 double utils::sigmoid(const double& in)
{
	return 1 / (1 + pow(2.71828, in));
}

 double utils::sigmoidD(const double& in)
{
	return in * (1 - in);
}

 double utils::step(const double& in)
{
	if (in > .5)
	{
		return 1;
	}
	return 0;
}

 double utils::stepD(const double& in)
 {
	 return 0;
 }

 double utils::squaredErr(const double& in)
{
	return .5*pow(in, 2);
}

 double utils::random()
{
	return ((double)rand() / (RAND_MAX));
}