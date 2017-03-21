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
	void makeHiddenLayer(const int& nodes);		//add hidden layer to network with specified amount of nodes
	///ADD THE LAST LAYER FIRST!!!
	void initialize();					//randomize weights and setup parent/child references
	///CALL THIS FUNCTION ONLY ONCE ALL LAYERS ARE SET UP
	void reset();	//re-randomize all weights

	//network training
	enum activationFunction {LINEAR, SIGMOID, STEP};
	enum costFunction {SQUAREDERR};
	void setActivationFxn(const activationFunction& type);	//set the networks activation function to one of the enumerated types
	void setCostFxn(const costFunction& type);

	void setInput(const int& node, const double& value);	//sets specified input node to specified value
	void setInput(const std::vector<double> & values);		//sets all input nodes values

	void feedForward();		//propogates inputs through network
	void backPropogate();	//adjusts weights based on utility analysis

	//activation functions

private:
	double rate;	//learning rate for the network


	std::vector<Layer> layers;	//all layers for network

};

class Layer
{
public:
	Layer(const int& size);
	
	void randomize();	//randomizes weight
	void initialize();

	void setChild(Layer* layer);
	void setParent(Layer* layer);

	void feedForward();
	void backPropogate();

	int getSize();
	std::vector<double> getValues();
private:
	int size;	//number of nodes

	Layer *parent;
	Layer *child;

	//no individual node/neuron/perceptron class all the stuff is right here
	std::vector<std::vector<double> > weights;		//each node has a weight for every node in the previous layer
	std::vector<std::vector<double> > deltaWeights;	//same deal
	std::vector<double> values;	//one output value is the sum of all weights*inputs passed through the activation fxn (also bias)

	std::vector<double> biasValues;
	std::vector<double> biasWeights;

	std::vector<double> errors;
};