#pragma once

#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <iostream>
#include "Utils.hpp"

class Layer
{
public:
	Layer(const int& numNodes, tfunc a, tfunc ad, tfunc c);

	void randomize();	//randomizes weight

	void setChild(Layer* layer);
	void setParent(Layer* layer);

	void feedForward();
	void backPropogate(const double& fitness);

	int getSize();
	std::vector<double> getValues();
	std::vector<std::vector< double> > getWeights();
	std::vector<double> getBiasValues();
	std::vector<double> getBiasWeights();
	void setValues(const std::vector<double>& vals);
	void setValues(const int& index, const double& value);

	std::vector<double> getErrors();

private:
	int size;	//number of nodes

	Layer *parent;
	Layer *child;

	//no individual node/neuron/perceptron class all the stuff is right here
	std::vector<std::vector<double> > weights;		//each node has a weight for every node in the previous layer
	std::vector<double> values;	//one output value is the sum of all weights*inputs passed through the activation fxn (also bias)

	std::vector<double> biasValues;
	std::vector<double> biasWeights;

	std::vector<double> errors;

	tfunc activation;	//pointer to activation fxn pointer
	tfunc dactivation;
	tfunc cost;		//pointer to cost fxn pointer
};