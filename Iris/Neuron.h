#ifndef NEURON_H
#define NEURON_H

#include "header.h"

using namespace std;

class Neuron
{
public:
	Neuron();
	virtual ~Neuron();

	vector <float> weight;
	float bias;
	float error;		// error
	float e;			// the vaue got from previous layer before adding bias and skaling to 0 - 1

	vector <Neuron*> prev;
	vector <Neuron*> next;

	float value;
	void setValue(float v);
	void getValue();
	float showValue();
	float cost(float v);
	void fillRandomly();
	void get_error(int number_of_the_asking_neuron);
	void correct_weights();
	void correct_bias();
	float derivative();
};


#endif // NEURON_H
