///-------------------------------------------------------------------------------------------------
// file:	wiresCollection.h
// summary:	Declares the wires collection class
///-------------------------------------------------------------------------------------------------

#pragma once
#include "cochlearProject.h"	//general header
#include "singleWire.h"			//include single wire

///-------------------------------------------------------------------------------------------------
/// <summary>	Collection of wires. </summary>
///
///-------------------------------------------------------------------------------------------------

class wiresCollection
{
	singleWire *wires;	//array to hold wire collection
	InputData _iData;	//hold input data
public:
	wiresCollection(InputData iData);	//constructor
										//return the wire collection
	singleWire& getWire(int i) {
		return wires[i];
	}
	void printWiresLocation();	//print all the locations
	void printWiresSignal();	//print all the signals	
	~wiresCollection();			//deconstructor
};

