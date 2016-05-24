///-------------------------------------------------------------------------------------------------
// file:	main.cpp
// This is a test class
// This class will create nerve and wires
// Then connect them
// The comparison methods are included in this class for testing
///-------------------------------------------------------------------------------------------------

#include "cochlearProject.h"	//general header
#include "neuronCollection.h"	//axon collection
InputData iData;				//input data

								//compare two sets of pulses in the window
double compareWindows(vector<singlePulse> rWindow, vector<singlePulse> sWindow, double startPoint, double endPoint);

//compare two signals
double compareSignal(vector<singlePulse> received, vector<singlePulse> sent, InputData iData);

//return true if two coordinates are the same
bool isSameCoordinate(Coordinates a, Coordinates b);

//print result
void printResult(connectionData result, InputData iData);

///-------------------------------------------------------------------------------------------------
/// <summary>	Main entry-point for this application. </summary>
///
/// <param name="argc">	Number of command-line arguments. </param>
/// <param name="argv">	Array of command-line argument strings. </param>
///
/// <returns>	Exit-code for the process - 0 for success, else an error code. </returns>
///-------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{

	//	Wait for user's input
	//	enter 1 to use default parameters 
	cout << "Please only enter valid input" << endl;
	int defaultSetting = 1;	//default is one
	cout << "Enter 1 to use default parameters" << endl;
	cin >> defaultSetting;
	// if user's input is not 1
	// ask for parameters
	if (defaultSetting != 1) {
		cout << "\nTotal Neuron Number (int): ";
		cin >> iData.neuronNumber;
		cout << "\nTotal Wire Number (int): ";
		cin >> iData.wireNumber;
		cout << "\nSingle Signal Length (double): ";
		cin >> iData.signalLength;
		cout << "\nA seed (int), ENTER 0 -->Random seed: ";
		cin >> iData.seeds;
		// random seed settings
		// enter 0 to use random seed
		if (iData.seeds == 0) {
			iData.seeds = time(NULL);
		}
		cout << "\nWindow size (double): ";
		cin >> iData.windowSize;
		//invalid window size
		if (iData.windowSize > iData.signalLength) {
			cout << "\ninvalid window size, reset to signal length";
			iData.windowSize = iData.signalLength;
		}
		cout << "\nWindow displacement (double): ";
		cin >> iData.windowIncrement;
	}
	cout << "\nParameters are ready.\n";
	auto t0 = std::chrono::high_resolution_clock::now();			//running time counter
	neuronCollection *nCollection = new neuronCollection(iData);	//initialize neurons
	wiresCollection *wCollection = new wiresCollection(iData);		//initialize wires
	nCollection->printCurrentBoard();		//test --> print board
	nCollection->connectWire(wCollection);	//test --> connect the wires
	nCollection->printCurrentBoard();		//test --> print board
											//wCollection->printWiresSignal();		//test --> print received signal

											//compare the received signal on each wire with all the signals
	int totalMatchWires = 0;	//counter
								//the number of axons
	const int totalNeuronNumber = nCollection->getResult().count;
	//Compare the signal on each wire with all the signals
	for (int i = 0; i < iData.wireNumber; i++) {
		double bestSimilarity = 99999;	//store the highest similarity value
		int bestNeuronIndex = -1;	//store the best matched neuron
									//compare with each axon
		for (int j = 0; j < totalNeuronNumber; j++)
		{
			//return the distance between two signals
			double tempSimilarity = compareSignal(wCollection->getWire(i).getPulses(), nCollection->getSingleNeuron(nCollection->getNormalNeuronLocation(j))->getSignal()->getPulses(), iData);
			//the smaller distance is the best match
			if (tempSimilarity < bestSimilarity) {
				bestSimilarity = tempSimilarity;
				bestNeuronIndex = j;
			}
		}
		//save result location
		wCollection->getWire(i).setResultLocation(nCollection->getNeuronLocation(bestNeuronIndex));
		//compare the best neuron location with the wire location
		if (isSameCoordinate(wCollection->getWire(i).getCoordinate(), nCollection->getNeuronLocation(bestNeuronIndex))) {
			totalMatchWires++;
		}
		//print result
		cout << "\nSmallest distance for wire: ";
		wCollection->getWire(i).printSingleWireLocation();
		cout << " is " << bestSimilarity << "  It matches the Neuron: ";
		wCollection->getWire(i).printSingleResultLocation();
	}
	//print result
	cout << "\n\nTotal Match is : " << totalMatchWires << endl;
	printResult(nCollection->getResult(), iData); //test -->print result
	auto t1 = std::chrono::high_resolution_clock::now();	//time counter
	auto dt = 1.e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
	cout << "\nProgram runs: " << dt << " seconds" << endl;	//print the running time
}


//return true if two coordinates are the same
bool isSameCoordinate(Coordinates a, Coordinates b) {
	if (a.coorX == b.coorX && a.coorY == b.coorY &&a.coorZ == b.coorZ) {
		return true;
	}
	return false;
}



//compare two signals
//********************unfinished part*********************
double compareSignal(vector<singlePulse> received, vector<singlePulse> sent, InputData iData) {
	double windowStartLocation = 0;	//start location
	double windowEndLocation = iData.windowSize;	//end location
	double totalDistance = 0;	//total diatance of all windows
								// when the end point is less than the length of the signal, keep comparing
	while (windowEndLocation <= iData.signalLength) {
		//pass the start point, end point, and the two signals.
		totalDistance += compareWindows(received, sent, windowStartLocation, windowEndLocation);
		windowStartLocation += iData.windowIncrement; //move the window forward
		windowEndLocation += iData.windowIncrement; //move the window forward
	}
	return totalDistance;
}

//compare two sets of pulses in the window
//********************unfinished part*********************
double compareWindows(vector<singlePulse> rWindow, vector<singlePulse> sWindow, double startPoint, double endPoint) {
	double windowSize = endPoint - startPoint;
	int receivedStartIndex = 0;
	int sentStartIndex = 0;
	double totalReceived = 0;
	double totalSent = 0;
	//get to received start index
	while (totalReceived <= startPoint) {
		totalReceived += rWindow.at(receivedStartIndex).receivedLength;
		receivedStartIndex++;
	}
	receivedStartIndex--;
	//get sent signal at start index
	while (totalSent <= startPoint) {
		totalSent += sWindow.at(sentStartIndex).sentLength;
		sentStartIndex++;
	}
	sentStartIndex--;
	//so far, we only process one side --> from received to sent
	//start processing signal
	double processedLength = 0;
	//return the longest distance as our distance of two sets
	double returnDistance = 0;
	//process the first pulse
	//the first length of the received window
	double firstLengthReceived = totalReceived - startPoint;
	double firstLengthSent = totalSent - startPoint;

	//process the first one;
	//we only compare the first pulse in the window
	if (sWindow.at(sentStartIndex).state == rWindow.at(receivedStartIndex).state) {
		returnDistance = abs(firstLengthReceived - firstLengthSent);
	}
	else {
		returnDistance = abs(firstLengthReceived + firstLengthSent);
	}
	return returnDistance;
}

//print result
void printResult(connectionData result, InputData iData) {
	cout << "\n************REPORT**************" << endl;
	cout << "Total axons: " << iData.neuronNumber << " Total Wires: " << iData.wireNumber << endl;
	cout << "Unconnected Wire: " << result.unconnectedWire << " Connect Ratio: " << (double)(iData.wireNumber - result.unconnectedWire) / iData.wireNumber << endl;
	cout << "Original Length of Each Signal: " << iData.signalLength << endl;
	cout << "Neurons Density (which is the connect probability): " << result.density << endl;
	cout << "Seed: " << iData.seeds << endl;
}