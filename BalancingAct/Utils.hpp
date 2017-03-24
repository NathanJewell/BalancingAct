#pragma once
#include <math.h>
#define LEARNINGRATE .5


typedef double(*tfunc)(const double&);
enum fxnType { LINEAR, SIGMOID, STEP, SQUAREDERR, LINEARD, SIGMOIDD, STEPD };

namespace utils
{
	double linear(const double& in);
	double linearD(const double& in);

	double sigmoid(const double& in);
	double sigmoidD(const double& in);

	double step(const double& in);
	double stepD(const double& in);

	double squaredErr(const double& in);

	double random();

	
}