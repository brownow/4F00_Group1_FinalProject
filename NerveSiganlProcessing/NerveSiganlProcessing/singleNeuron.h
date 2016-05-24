///-------------------------------------------------------------------------------------------------
// file:	singleNeuron.h
// summary:	Declares the single axon class
///-------------------------------------------------------------------------------------------------
#pragma once
#include "cochlearProject.h"	//include general header
#include "singleSignal.h"		//include single signal

class singleNeuron
{
	Coordinates neuronLocation;	//neuron location
	singleSignal *neuronSignal;	//neuron signal
	InputData _iData;			//input data holder
								//O means it has neuron, X means connected, ' 'means empty
	char neuronStatus = ' ';
public:
	//return the status of the axon
	char getStatus() {
		return neuronStatus;
	};

	//setter for status
	void setStatus(char c) {
		neuronStatus = c;
	};

	//return the Signal
	singleSignal* getSignal() {
		return neuronSignal;
	};
	//constructor
	singleNeuron(InputData iData);
	//deconstructor
	~singleNeuron();
};

