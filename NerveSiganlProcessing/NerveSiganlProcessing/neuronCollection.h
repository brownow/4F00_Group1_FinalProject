///-------------------------------------------------------------------------------------------------
// file:	neuronCollection.h
// summary:	Declares the neuron collection class
///-------------------------------------------------------------------------------------------------
#pragma once
#include "cochlearProject.h"	//include the general header
#include "singleNeuron.h"		//include single axon
#include "wiresCollection.h"	//include wire collection for connection

///-------------------------------------------------------------------------------------------------
/// <summary>	Collection of neurons. </summary>
///	the neuronCollection class header
///-------------------------------------------------------------------------------------------------
class neuronCollection
{
	singleNeuron**** neurons;		//a 3-D array to hold our axons
	InputData _iData;				//input data holder
	connectionData result;			//temp object to hold calculated result
	Coordinates* neuronsLocation;	//locations that have neurons
	Coordinates convertToNormal(int x, int y, int z, int offset);	//convert Negative index to normal indexes
	Coordinates convertToHex(int x, int y, int z, int offset);		//convert normal index to negative indexes
	Coordinates hexToMaxtrix(int x, int y, int z, int offset);		//hex(has Negative) indexes to matrix indexes
	int getLayers(int neurons);		//get the number of layer
	void neuronCollection::markSurrounding(Coordinates centerPoint, int offset, int number, char c, Coordinates *collection, double markRatio);
	//take the hex(has negative) index, set it status to c
	void setValue(int x, int y, int z, int offset, char c);
	int offset;						//offset
	int sizeX;						//x coordinate size
	int sizeY;						//y coordinate size
	int sizeZ;						//z coordinate size
public:
	neuronCollection(InputData iData);	//constructor
										//return the result
	connectionData getResult() {
		return result;
	};
	//return neuron's location at i
	Coordinates getNeuronLocation(int i) {
		return neuronsLocation[i];
	};

	//return neuron's location at i, in normal form
	Coordinates getNormalNeuronLocation(int i) {
		return convertToNormal(neuronsLocation[i].coorX, neuronsLocation[i].coorY, neuronsLocation[i].coorZ, offset);

	};

	// return the single Neuron at Coordinates c
	singleNeuron *getSingleNeuron(Coordinates c) {
		return neurons[c.coorX][c.coorY][c.coorZ];
	};

	void printCurrentBoard();				//print the board
	void connectWire(wiresCollection *w);	//connetion wires with nerve
	~neuronCollection();					//deconstructor
};

