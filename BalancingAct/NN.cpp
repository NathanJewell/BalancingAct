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

	layers.push_back(Layer(OUTnodes, activation, cost));
	layers.push_back(Layer(INnodes, activation, cost));
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
	layers.insert(it, Layer(nodes, activation, cost));	//insert new layer with specified number of nodes
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

void Net::feedForward()
{
	layers[1].feedForward();	//start at the second layer because first layer is just inputs
}


void Net::backPropogate(const double& fitness)
{
	layers.back().backPropogate();
}



Layer::Layer(const int& numNodes, tfunc a, tfunc c)
{
	size = numNodes;
	activation = a;
	cost = c;
}

void Layer::randomize()
{
	errors.clear();
	values.clear();
	biasValues.clear();
	biasWeights.clear();
	weights.clear();
	for (unsigned int i = 0; i < size; i++)
	{
		errors.push_back(utils::random());
		values.push_back(utils::random());
		biasValues.push_back(utils::random());
		biasWeights.push_back(utils::random());
		std::vector<double> tmp;
		for (unsigned int b = 0; b < parent->getSize(); b++)
		{
			tmp.push_back(utils::random());
		}
		weights.push_back(tmp);
	}
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

	std::fill(values.begin(), values.end(), 0);	//reset all values to 0 
	//this is all kinda unsafe because not checking size of input/weight arrays but eh.
	for (unsigned int i = 0; i < weights.size(); i++)	//cycling through each node
	{
		double value = 0;
		for (unsigned int b = 0; b < weights[i].size(); b++)
		{
			value += inputs[b] * weights[i][b];
		}
		value += biasValues[i] * biasWeights[i];
		values[i] = activation(value);	//pass through activation function for final output
	}
	if (child)
	{
		child->feedForward();
	}

}

void Layer::backPropogate(const double& fitness)
{
	//calculating errors
	if (!child) //output layer
	{
		for (unsigned int i = 0; i < values.size(); i++)
		{
			errors[i] = cost();
		}
	}
	else if (!parent)	//input layer -- no errors
	{
		std::fill(errors.begin(), errors.end(), 0);
	}
	else //hidden layer
	{
		std::vector<double>& childErrors = child->getErrors();

		for (unsigned int i = 0; i < values.size(); i++)	//iterate through every node
		{
			double sum = 0;
			for (unsigned int b = 0; b < child->getSize(); b++)	//iterate through all nodes connected to that node downstream
			{
				sum += childErrors[b] * weights[i][b];
			}
			errors[i] = dactivation(sum);
		}

	}
	//adjusting weights
	if (child)
	{
		std::vector<double>& childErrors = child->getErrors();

		for (unsigned int i = 0; i < values.size(); i++)	//for each neuron in this layer
		{
			for (unsigned int b = 0; b < child->getSize(); b++)	//for each neuron in child layer
			{
				double dw = LEARNINGRATE * (childErrors[b] * values[i]);	//multiple child nodes error for this node by its value to find error
				weights[i][b] += dw;
			}
		}
		//adjust bias
	}
	if (parent)
	{
		parent->backPropogate();
	}
}

int Layer::getSize()
{
	return size;
}

std::vector<double> Layer::getValues()
{
	return values;
}

void Layer::setValues(const std::vector<double>& vals)
{
	values = vals;
}

void Layer::setValues(const int& index, const double& value)
{
	values[index] = value;
}

std::vector<double> Layer::getErrors()
{
	return errors;
}