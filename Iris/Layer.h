#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"


using namespace std;

class Layer
{
public:
	Layer(int nNeurons);
	virtual ~Layer();


	vector <Neuron*> prev;
	vector <Neuron*> next;

	vector <Neuron> layer;
};

#endif // LAYER_H
