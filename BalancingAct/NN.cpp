#include "NN.hpp"

Net::Net(const int& INnodes, const int& OUTnodes)
{
	layers.push_back(Layer(OUTnodes));
	layers.push_back(Layer(INnodes));
}

Layer Net::getOutputLayer()
{
	return layers.back();
}

Layer Net::getInputLayer()
{
	return layers.front();
}

void Net::makeHiddenLayer(const int& nodes)
{
	auto it = layers.begin() + 1;		//get iterator for second spot in array
	layers.insert(it, Layer(nodes));	//insert new layer with specified number of nodes
}

void Net::initialize()
{
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		if (i != 0)
		{
			//set the parent to previous layer (has to know this for propogation
			layers[i].setParent(&layers[i - 1]);	
		}
		if (i != layers.size() - 1)
		{
			//set child to next layer
			layers[i].setChild(&layers[i + 1]);
		}
	}
	reset();
}

void Net::reset()
{
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i].randomize();	//randomize layer weights
	}
}

void Net::setActivationFxn(const activationFunction& type)
{
	if (type == LINEAR)
	{

	}
	else if (type == SIGMOID)
	{

	}
	else if (type == STEP)
	{

	}
}

void Net::setInput(const int& node, const double& value)
{
	//set layer 0 values
}

void Net::setInput(const std::vector<double>& values)
{
	//set layer 0 values
}

void Net::feedForward()
{
	layers[1].feedForward();	//start at the second layer because first layer is just inputs
}


void Net::backPropogate()
{
	
}



Layer::Layer(const int& size)
{
	
}

void Layer::setChild(Layer* layer)
{
	child = layer;
}

void Layer::setParent(Layer* layer)
{
	parent = layer;
}

void Layer::feedForward()
{
	//calculate values
	std::vector<double>& inputs = parent->getValues();

	std::fill(values.begin(), values.end(), 0);	//reset all values to 0 so they can be summatively calculated
	//this is all kinda unsafe because not checking size of input/weight arrays but eh.
	for (unsigned int i = 0; i < weights.size(); i++)	//cycling through each node
	{
		for (unsigned int b = 0; b < weights[i].size(); b++)
		{
			values[i] += inputs[b] * weights[i][b];
		}
		values[i] += biasValues[i] * biasWeights[i];
	}
	child->feedForward();
}

void Layer::backPropogate()
{

}
