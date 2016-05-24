///-------------------------------------------------------------------------------------------------
// file:	singleSignal.cpp
//
// summary:	Implements the single signal class
///-------------------------------------------------------------------------------------------------
#include "singleSignal.h"

///-------------------------------------------------------------------------------------------------
/// <summary>	Constructor. </summary>
///
/// <param name="iData">Input data. </param>
///-------------------------------------------------------------------------------------------------

singleSignal::singleSignal(InputData iData)
{
	//random device
	random_device rd;
	//default_random_engine rd;
	// set the length to the parameter
	singleSignal::length = iData.signalLength;
	// generate pulse and silence means, from 0 to 1
	uniform_real_distribution<double> ud(0, 1);
	//we want save the mean for future use
	singleSignal::pulseMean = ud(rd);
	singleSignal::silenceMean = ud(rd);
	// random number generators and variables for pulse
	exponential_distribution<double> gen1(pulseMean);
	exponential_distribution<double> gen2(silenceMean);
	// set normal distribution for noises
	//********************************we set it around (-1, 1), centered 0*************/
	//*********************************need to change it later********************/
	normal_distribution<double> ud2(0, 0.2);
	//*********signal creation**********//
	//reset the current length before signal creation
	//this variable is temp, just to make sure the length we created is not greater than the limit
	double currentLength = 0;
	//state: 1 is pulse, 0 is silence
	//because the default of the state is 0 (silence)
	//so the first pulse we generate will be pulse
	//in the following while loop
	//we check (last) state, generate pulse, change the state, and save the pulse
	singlePulse pulseVal;
	while (true) {
		if (pulseVal.state == 0) {
			pulseVal.origLength = gen1(rd);
			pulseNum++;
		}
		else {
			pulseVal.origLength = gen2(rd);
			silenceNum++;
		}
		//change state before save
		pulseVal.state = 1 - pulseVal.state;
		//add to length
		currentLength += pulseVal.origLength;
		//if pulse legal, add it to vector
		//if not, cut it, add it to vector, and break
		if (currentLength < length) {
			pulses.push_back(pulseVal);
		}
		else {
			pulseVal.origLength = length - (currentLength - pulseVal.origLength);
			pulses.push_back(pulseVal);
			break;
		}
	}

	//add noise to create sent signal
	//which is add noise to orignal signal
	double currentSentLength = 0;	//temp variable to set the limit
									//iterate all pulses/silences
									//not necessary to be in the order as we generated them randomly
	for (auto &value : pulses) {
		//add the noise
		value.sentLength = value.origLength + ud2(rd);
		//if the result < 0, we can set it to 0
		if (value.sentLength < 0) value.sentLength = 0;
		//add to total length
		currentSentLength += value.sentLength;
		//cut it if the length is over the limit
		if (currentSentLength > length) {
			value.sentLength = length - (currentSentLength - value.sentLength);
			break;
		}
	}

	//add noise to create received signal
	//which is add noise to sent signal (double noise)
	double currentReceivedLength = 0;
	//same idea as sent signal, we write them separately for readability
	for (auto &value : pulses) {
		value.receivedLength = value.sentLength + ud2(rd);
		//if the result < 0, we can set it to 0
		if (value.receivedLength < 0) value.receivedLength = 0;
		currentReceivedLength += value.receivedLength;
		//cut it if the length is over the limit
		if (currentReceivedLength> length) {
			value.receivedLength = length - (currentReceivedLength - value.receivedLength);
			break;
		}
	}

}

///-------------------------------------------------------------------------------------------------
/// <summary>	print method for testing </summary>
///
/// <remarks>	Chang, 2016-04-18. </remarks>
///-------------------------------------------------------------------------------------------------

void singleSignal::printSingleSignal() {
	cout << "Original signal" << endl;
	for (auto &pulse : pulses) {
		cout << pulse.origLength << "\t";
	}
	cout << "\nSent signal" << endl;
	for (auto &pulse : pulses) {
		cout << pulse.sentLength << "\t";
	}
	cout << "\nReceived signal" << endl;
	for (auto &pulse : pulses) {
		cout << pulse.receivedLength << "\t";
	}
}