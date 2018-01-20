#include "Layer.h"

Layer::Layer(int nNeurons)
{
	for (int i = 0; i<nNeurons; i++)
	{
		layer.push_back(Neuron());
	}
}

Layer::~Layer()
{
	//dtor
}


