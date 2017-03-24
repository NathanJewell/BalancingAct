#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <iostream>
#include "Utils.hpp"
#include "Layer.hpp"
//network creation process steps **this can be streamlines... but for now...
//Create net(IN, OUT, activation, dactivation, cost)
//initialize net
//train network


class Net
{
public:
	Net(const int& INnodes, const int& OUTnodes, fxnType a, fxnType da, fxnType c);

	//network retrieval
	Layer getOutputLayer();
	Layer getInputLayer();

	//network creation
	void makeHiddenLayer(const int& nodes);		//add hidden layer to network with specified amount of nodes
	///ADD THE LAST LAYER FIRST!!!
	void initialize();					//randomize weights and setup parent/child references
	///CALL THIS FUNCTION ONLY ONCE ALL LAYERS ARE SET UP
	void reset();	//re-randomize all weights

	//network training

	

	std::map<fxnType, tfunc> tfuncs;

	void setActivationFxn(const fxnType& type);	//set the networks activation function to one of the enumerated types
	void setCostFxn(const fxnType& type);

	void setInput(const int& node, const double& value);	//sets specified input node to specified value
	void setInput(const std::vector<double> & values);		//sets all input nodes values

	std::vector<double> getOutput();
	void setDesiredOutput(const std::vector<double>& out);

	void feedForward();		//propogates inputs through network
	void backPropogate(const double& fitness);	//adjusts weights based on utility analysis

	//activation functions

private:
	double rate;	//learning rate for the network

	tfunc activation;
	tfunc dactivation;	//derivative of activation fxn
	tfunc cost;

	std::vector<Layer> layers;	//all layers for network

};

