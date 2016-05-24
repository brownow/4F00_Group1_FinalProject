///-------------------------------------------------------------------------------------------------
// file:	singleSignal.h
// summary:	Declares the single signal class
///-------------------------------------------------------------------------------------------------

#pragma once
#include "cochlearProject.h"	//include general header

///-------------------------------------------------------------------------------------------------
/// <summary>	A single signal header </summary>
/// single signal creation
///-------------------------------------------------------------------------------------------------

class singleSignal
{
	double length;				//length of the generated signal	
	double pulseMean;			//mean used to generate pulse
	double silenceMean;			//mean used to generate silense
	int pulseNum = 0;			//total pulse number
	int silenceNum = 0;			//total silence number
	vector<singlePulse> pulses;	//a vector to hold all pulses of the single signal


public:
	singleSignal() = default;		//default constructor
	singleSignal(InputData iData);	//constructor
	void printSingleSignal();		//print the signal
	vector<singlePulse> getPulses() { return pulses; }	//return the pulses vector
	~singleSignal();
};

