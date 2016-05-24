///-------------------------------------------------------------------------------------------------
// file:	cochlearProject.h
//
// summary:	Declares a few structs that used in many classes
// SinglePulse, InputData, OutputData, and Coordinates
// Also includes some library that used very often
///-------------------------------------------------------------------------------------------------

#pragma once
#include <random>	//random generator
#include <queue>	//queue library
#include <vector>	//vector library
#include <iostream>	//input/output stream
#include <sstream>	//string
#include <string>	//string
#include <stdlib.h>	//rand
#include <time.h>	//time
#include <fstream>	//file
#include <chrono>	//measure time span	
using namespace std;	//std

						///-------------------------------------------------------------------------------------------------
						/// <summary>	a single pulse/silence stuct </summary>
						///-------------------------------------------------------------------------------------------------

struct singlePulse {
	double origLength = 0;		//original generated length of the single pulse/silence
	double sentLength = 0;		//length of the pulse added noise 1
	double receivedLength = 0;	//length of the pulse added noise 1 and 2
	int state = 0;				//1 is pulse, 0 is silence
	singlePulse() = default;	//constructor
};


///-------------------------------------------------------------------------------------------------
/// <summary>Save User Input Data for parameters passing </summary>
///
///-------------------------------------------------------------------------------------------------

struct InputData {
	int wireNumber = 7;			//number of wires
	int neuronNumber = 37;		//number of neurons
	int seeds = 2016;			//seed for random numbers
	double signalLength = 20;	//length of each signal
	int minPulseNum = 5;		//minimum pulse number
	double windowSize = 5;		//window size
	double windowIncrement = 4;	//window increment
};


//

///-------------------------------------------------------------------------------------------------
/// <summary>	coordinates of the neurons/wires </summary>
/// 
///-------------------------------------------------------------------------------------------------

struct Coordinates {
	int coorX = 0;				//x coordinate
	int coorY = 0;				//y coordinate	
	int coorZ = 0;				//z coordinate
	Coordinates() = default;	//default constructor
								//contructor with parameters
	Coordinates(int x, int y, int z) {
		coorX = x;
		coorY = y;
		coorZ = z;
	}
};



///-------------------------------------------------------------------------------------------------
/// <summary>temp store information of connection/neuron creation </summary>
/// This class is created for temporary storing connection data
/// You can get rid of this class or modify it later
///
///-------------------------------------------------------------------------------------------------

struct connectionData {
	int layers = 0;					//number of layers
	int unconnectedWire = 0;		//unconnected wires
	double bestConnectRatio = 0;	//best connection ratio
	double aveConnectRatio = 0;		//average connection ratio
	int count = 0;					//counter
	double density = 0;				//axons density
};
