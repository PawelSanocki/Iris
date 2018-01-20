#ifndef NET_H
#define NET_H

#include "Layer.h"

using namespace std;

class Net
{
public:
	Net(int nNeuronFirst = NUMBER_OF_ATT, int nNeuronHidden = HIDDEN_LAYER, int nNeuronLast = LAST_LAYER);			// constructor giving the possibility to change number of neurons in each layer
	virtual ~Net();

	void connectLayers(int nNeuronFirst, int nNeuronHidden, int nNeuronLast);		// connecting the layers

	float* recognize(float *results);												// recognize returns the table of results, it also saves them into the table given as one of the arguments
	void fillRandomly();															// filling weights from some range given in Neuron class
	void loadWeights();																// loading weights from txt, no possibility of introducing your file out from the folder of the project
	void saveWeights();																// saving weights to txt
	void learn();																	// reading file from minst, and running function improve
	void improve(float* results, int label);										// calculating the error and correcting the weights and biases
	float test();												// how many wrong in first half, and second
	float netError(int number);														// calculating the net cost

	vector <Layer> net;																//  net is build of layers which contain neurons
};

#endif // NET_H
