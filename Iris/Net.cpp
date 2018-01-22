#include "Net.h"

Net::Net(int nNeuronFirst, int nNeuronHidden, int nNeuronLast)
{
	srand(time(NULL));
	net.push_back(Layer(nNeuronFirst));
	for (int i = 0; i<N_HIDDEN; i++)
	{
		net.push_back(Layer(nNeuronHidden));
	}
	net.push_back(Layer(nNeuronLast));

	connectLayers(nNeuronFirst, nNeuronHidden, nNeuronLast);
}

Net::~Net()
{
	//dtor
}

void Net::connectLayers(int nNeuronFirst, int nNeuronHidden, int nNeuronLast)
{
	for (int j = 0; j < net.size() - 1; j++)
	{
		for (unsigned int i = 0; i < net[j + 1].layer.size(); i++)
		{
			net[j].next.push_back(&net[j + 1].layer[i]);
		}
		for (unsigned int i = 0; i<net[j].layer.size(); i++)
		{
			net[j].layer[i].next = net[j].next;
		}
	}
	for (int j = 1; j < net.size(); j++)
	{
		for (unsigned int i = 0; i < net[j - 1].layer.size(); i++)
		{
			net[j].prev.push_back(&net[j - 1].layer[i]);
		}
		for (unsigned int i = 0; i<net[j].layer.size(); i++)
		{
			net[j].layer[i].prev = net[j].prev;
		}
	}
}

float* Net::recognize(float *results)
{
	// checking if pointers are correct
	for (int i = 1; i < net.size(); i++)
	{
		if (net[i].prev.size() != net[i - 1].layer.size())
		{
			throw runtime_error("Connecting failed!");
		}
	}
	for (int i = 0; i < net.size() - 1; i++)
	{
		if (net[i].next.size() != net[i + 1].layer.size())
		{
			throw runtime_error("Connecting failed!");
		}
	}
	// passing signals throught the net
	for (unsigned int i = 1; i < this->net.size(); i++)
	{
		for (unsigned int j = 0; j < net[i].layer.size(); j++)
		{
			net[i].layer[j].getValue();
		}
	}
	// giving and saving results
	for (unsigned int i = 0; i < net[net.size() - 1].layer.size(); i++)
	{
		results[i] = net[net.size() - 1].layer[i].value;
	}
	return results;
}

void Net::fillRandomly()
{
	for (int i = 1; i < net.size(); i++)
	{
		for (unsigned int j = 0; j < this->net[i].layer.size(); j++)
		{
			this->net[i].layer[j].fillRandomly();
		}
	}
}

void Net::loadWeights()
{
	ifstream file("file.txt");
	float floatNumber;
	for (int i = 1; i < net.size(); i++)
	{
		for (unsigned int j = 0; j < this->net[i].layer.size(); j++)
		{
			for (unsigned int k = 0; k < net[i - 1].layer.size(); k++)
			{
				file >> floatNumber;
				net[i].layer[j].weight.push_back((float)floatNumber);
			}
			file >> floatNumber;
			net[i].layer[j].bias = (float)floatNumber;
		}
	}
	file.close();
}

void Net::saveWeights()
{
	ofstream file("file.txt", ios::trunc);
	for (unsigned int i = 1; i < net.size(); i++)
	{
		for (unsigned int j = 0; j < this->net[i].layer.size(); j++)
		{
			for (unsigned int k = 0; k < net[i].layer[j].weight.size(); k++)
			{
				file << this->net[i].layer[j].weight[k] << endl;
			}
			file << this->net[i].layer[j].bias << endl;
		}
	}
	file.close();
}

void Net::improve(float* results, int label)
{
	// calculating the error of the last layer neurons
	for (unsigned int j = 0; j < net[net.size() - 1].layer.size(); j++)
	{
		if (j == label)
		{
			net[net.size() - 1].layer[j].error = net[net.size() - 1].layer[j].derivative() * (1 - results[j]);
		}
		else
		{
			net[net.size() - 1].layer[j].error = net[net.size() - 1].layer[j].derivative() * (0 - results[j]);
		}
	}
	// backpropagating the error
	for (unsigned int i = this->net.size() - 2; i > 0; i--)
	{
		for (unsigned int j = 0; j < net[i].layer.size(); j++)
		{
			net[i].layer[j].get_error(j);
		}
	}
	// correcting the weights and biases
	for (unsigned int i = 1; i < this->net.size(); i++)
	{
		for (unsigned int j = 0; j < net[i].layer.size(); j++)
		{
			net[i].layer[j].correct_weights();
			net[i].layer[j].correct_bias();
			net[i].layer[j].error = 0;
		}
	}
	this->saveWeights();
}

float Net::test()
{
	float sepal_l,sepal_w,petal_l,petal_w ;
	cout << "Give sepal length, sepal width, petal length and petal width: " << endl; 
	cin >> sepal_l >> sepal_w >> petal_l >> petal_w;
	float results[LAST_LAYER];
	net[0].layer[0].setValue(sepal_l);
	net[0].layer[1].setValue(sepal_w);
	net[0].layer[2].setValue(petal_l);
	net[0].layer[3].setValue(petal_w);
	recognize(results);
	for (int i = 0; i < LAST_LAYER; i++)
	{
		cout << i << "-type chance: " << results[i] << endl;
	}
	cout << "It is: ";
	switch (biggest(results))
	{
	case 0:
	{
		cout << "Iris-setosa";
	}break;
	case 1:
	{
		cout << "Iris-versicolor";
	}break;
	case 2:
	{
		cout << "Iris-virginica";
	}break;
	}
	cout << endl;
	return 1;
}

void Net::learn()
{
	mix();
	ifstream file("data.txt");
	string str;
	float results[LAST_LAYER];
	float floatNumber;
	if (file.fail()) throw runtime_error("Wrong file");
	for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
	{
		for (int number_of_att = 0; number_of_att < NUMBER_OF_ATT; number_of_att++)
		{
			file >> floatNumber;
			net[0].layer[number_of_att].setValue(floatNumber);
			file.seekg(+1, ios_base::cur);
		}
		file >> str;
		
		if (str == "Iris-setosa")
		{
			improve(recognize(results), 0);
		}
		else if (str == "Iris-versicolor")
		{
			improve(recognize(results), 1);
		}
		else if (str == "Iris-virginica")
		{
			improve(recognize(results), 2);
		}
	}
	file.close();
}

float Net::netError(int number)
{
	float error = 0;

	for (int i = 0; i < 10; i++)
	{
		if (i == number)
		{
			error += pow(this->net[net.size() - 1].layer[i].value - 1, 2) / 2;
		}
		else
		{
			error += pow(this->net[net.size() - 1].layer[i].value - 0, 2) / 2;
		}

	}
	return error;
}
