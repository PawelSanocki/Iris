#include "Neuron.h"

Neuron::Neuron()
{
	e = 0;
	error = 0;
	value = 0;
	bias = 0;
}

Neuron::~Neuron()
{
	//dtor
}

void Neuron::setValue(float v)
{
	this->value = (1 / (1 + pow(M_E, -v)));
}

void Neuron::getValue()
{
	this->e = 0;
	for (int i = 0; i < this->weight.size(); i++)
	{
		this->e += (this->prev[i]->value) * this->weight[i];
	}
	setValue(this->e + this->bias);
}

float Neuron::showValue()
{
	return this->value;
}

float Neuron::cost(float v)
{
	return pow(this->value - v, 2);
}

void Neuron::fillRandomly()
{
	for (unsigned int i = 0; i < this->prev.size(); i++)
	{
		this->weight.push_back((rand() % 10) / 10.0);
	}
	this->bias = (rand() % 20) / 100.0 - 0.1;
}

void Neuron::get_error(int number_of_the_asking_neuron)
{
	this->error = 0;
	for (int i = 0; i < this->next.size(); i++)
	{
		this->error += (this->next[i]->error * this->next[i]->weight[number_of_the_asking_neuron] * this->derivative());
	}
}

void Neuron::correct_weights()
{
	for (int i = 0; i < this->weight.size(); i++)
	{
		this->weight[i] += LEARNING_FACTOR * (this->prev[i]->value) * (this->error);
	}
}

void Neuron::correct_bias()
{
	this->bias += LEARNING_FACTOR * (this->error);
}

float Neuron::derivative()
{
	double help = pow(M_E, -this->e);
	return (help / (pow((1 + help), 2)));
}