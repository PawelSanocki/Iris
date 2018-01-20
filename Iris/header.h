#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <exception>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <exception>
#include <ctime>
#include <fstream>
#include <queue>
#include <windows.h>
#include <string>
#include <algorithm>

#define LEARNING_FACTOR 0.2																			// how fast should the net learn (how big impact on the weights and biases should have one sample)
#define M_E 2.71828182845904523536																	// needed for sigmoid function
#define N_HIDDEN 2																					// amount of hidden layers
#define NUMBER_OF_SAMPLES 150																		// needed to easily set number of samples for testing the program
#define NUMBER_OF_ATT 4																				// number of neurons in first layer
#define LAST_LAYER 3																				// number of neurons in output layer
#define HIDDEN_LAYER 5																				// number of neurons in hidden layer

using namespace std;

int biggest(float* tab);																			// returns index of the biggest number in the table of ten elements, needed to bing the final answer
void mix();


#endif // HEADER_H_INCLUDED
