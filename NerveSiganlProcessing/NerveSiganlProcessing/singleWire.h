///-------------------------------------------------------------------------------------------------
// file:	singleWire.h
// summary:	Declares the single wire class
///-------------------------------------------------------------------------------------------------

#pragma once
#include "cochlearProject.h"	//include the general header

///-------------------------------------------------------------------------------------------------
/// <summary>	A single wire. </summary>
///-------------------------------------------------------------------------------------------------

class singleWire
{
	Coordinates wireLocation;	//store the wire location
	vector<singlePulse> pulses;	//a vector to hold all pulses of the single signal
	Coordinates resultLocation;	//store the wire location
public:
	singleWire();	//constructor
					//set result location
	void setResultLocation(Coordinates c) {
		resultLocation.coorX = c.coorX;	//x
		resultLocation.coorY = c.coorY;	//y
		resultLocation.coorZ = c.coorZ;	//z
	}

	//get wire location
	Coordinates getCoordinate() {
		return wireLocation;
	};

	//set the wire location
	void setLocation(Coordinates c) {
		wireLocation.coorX = c.coorX;
		wireLocation.coorY = c.coorY;
		wireLocation.coorZ = c.coorZ;
	};

	//return the pulses of the wire
	vector<singlePulse> getPulses() {
		return pulses;
	};

	//set the pulses of the single wire
	void setPulses(vector<singlePulse> p) {
		pulses = p;
	};

	void printReceivedSignal();			//print the signal
	void printSingleWireLocation();		//print the wire location
	void printSingleResultLocation();	//print the matched location
	~singleWire();						//deconstructor
};

