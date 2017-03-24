#include "Layer.hpp"

Layer::Layer(const int& numNodes, tfunc a, tfunc ad, tfunc c)
{
	size = numNodes;
	activation = a;
	dactivation = ad;
	cost = c;
	parent = NULL;
	child = NULL;
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

		if (child)
		{
			std::vector<double> tmp;
			for (unsigned int b = 0; b < child->getSize(); b++)
			{
				tmp.push_back(utils::random());
			}
			weights.push_back(tmp);
		}
	

	}
	
	std::fill(biasValues.begin(), biasValues.end(), 1);
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
	std::vector<std::vector< double> >& pweights = parent->getWeights();
	std::vector<double>& pBiasValues = parent->getBiasValues();
	std::vector<double>& pBiasWeights = parent->getBiasWeights();

	std::fill(values.begin(), values.end(), 0);	//reset all values to 0 
	//this is all kinda unsafe because not checking size of input/weight arrays but eh.
	for (unsigned int i = 0; i < size; i++)	//cycling through each node
	{
		double value = 0;
		for (unsigned int b = 0; b < parent->getSize(); b++)
		{
			value += inputs[b] * pweights[b][i];
		}
		value += pBiasValues[i] * pBiasWeights[i];
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
			errors[i] = fitness * dactivation(values[i]);	//fitness is actually difference in fitness for now
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
			errors[i] = sum * dactivation(values[i]);
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
		for (unsigned int i = 0; i < child->getSize(); i++)
		{
			biasWeights[i] += LEARNINGRATE * childErrors[i] * biasValues[i];
		}
		//adjust bias
	}
	if (parent)
	{
		parent->backPropogate(fitness);
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

std::vector<std::vector<double> > Layer::getWeights()
{
	return weights;
}
std::vector<double> Layer::getBiasValues()
{
	return biasValues;
}
std::vector<double> Layer::getBiasWeights()
{
	return biasWeights;
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