#pragma once

#include <vector>
//Nearest neighbor approach for learning to balance

class NHood
{
public:
	NHood(const int& dimensions, const int& classes);
	int classify(const std::vector<double>& input);
	void setHoodSize(const double& radius);

private:
	int dimensions;	//how many dimensions of data we will have to compare
	int classes;	//number of classes to categorize points into
	int radius;		//maximum search radius for neighbors

};