#include "NN.hpp"

Net::Net(const int& INnodes, const int& OUTnodes, fxnType a, fxnType da, fxnType c)
{

	srand((unsigned)time(NULL));

	tfuncs[LINEAR] = utils::linear;
	tfuncs[SIGMOID] = utils::sigmoid;
	tfuncs[STEP] = utils::step;
	tfuncs[SQUAREDERR] = utils::squaredErr;
	tfuncs[LINEARD] = utils::linearD;
	tfuncs[SIGMOIDD] = utils::sigmoidD;
	tfuncs[STEPD] = utils::stepD;

	//default values
	activation = tfuncs[a];
	dactivation = tfuncs[da];
	cost = tfuncs[c];

	layers.push_back(Layer(INnodes, activation, dactivation, cost));
	layers.push_back(Layer(OUTnodes, activation, dactivation, cost));
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
	layers.insert(it, Layer(nodes, activation, dactivation, cost));	//insert new layer with specified number of nodes
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

void Net::setActivationFxn(const fxnType& type)
{
	activation = tfuncs[type];
}

void Net::setCostFxn(const fxnType& type)
{
	cost = tfuncs[type];
}

void Net::setInput(const int& node, const double& value)
{
	layers[0].setValues(node, value);
}

void Net::setInput(const std::vector<double>& values)
{
	layers[0].setValues(values);
}

std::vector<double> Net::getOutput()
{
	return layers.back().getValues();
}

void Net::setDesiredOutput(const std::vector<double>& out)
{
	//layers.back().
}

void Net::feedForward()
{
	layers[1].feedForward();	//start at the second layer because first layer is just inputs
}


void Net::backPropogate(const double& fitness)
{
	layers.back().backPropogate(fitness);
}



