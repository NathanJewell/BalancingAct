#pragma once
#include <vector>

class Net
{
public:
	Net(const int& INnodes, const int& OUTnodes);

	//network retrieval
	Layer getOutputLayer();
	Layer getInputLayer();

	//network creation
	void makeHiddenLayer(const int& nodes);

	//network training
	void setInput(const int& node, const double& value);	//sets specified input node to specified value
	void setInput(const std::vector<double> & values);		//sets all input nodes values
	void feedForward();		//propogates inputs through network
	void backPropogate();	//adjusts weights based on utility analysis

private:
	double rate;	//learning rate for the network

	std::vector<Layer> layers;	//all layers for network

};

class Layer
{
public:
	Layer(const int& size);

private:
	std::vector<Node> nodes;
};

class Node
{
public:
	Node();

private:
	double weight;
	double deltaWeight;
	double value;
	double error;
	double biasValue;
	double biasWeight;
	std::vector<Node*> connections;

};