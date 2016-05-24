///-------------------------------------------------------------------------------------------------
// file:	neuronCollection.cpp
//
// summary:	Implements the neuron collection class
///-------------------------------------------------------------------------------------------------

#include "neuronCollection.h"
default_random_engine rd;
///-------------------------------------------------------------------------------------------------
/// <summary>	Constructor. </summary>
///
/// <param name="iData">	The data. </param>
///-------------------------------------------------------------------------------------------------

neuronCollection::neuronCollection(InputData iData)
{

	//set seed
	rd.seed(iData.seeds);
	//read input data
	_iData = iData;
	//calculate the layers that we need
	result.layers = getLayers(iData.neuronNumber);
	//number of neurons
	//lots of cells in the 3-D array are not used
	result.count = 3 * result.layers*(result.layers - 1) + 1;
	//initialize the 3-D array
	offset = result.layers - 1;
	sizeX = result.layers + offset;
	sizeY = result.layers + offset;
	sizeZ = result.layers + offset;
	neurons = new singleNeuron***[sizeX];
	for (int i = 0; i < sizeX; i++) {
		neurons[i] = new singleNeuron**[sizeY];
		for (int j = 0; j < sizeZ; j++) {
			neurons[i][j] = new singleNeuron*[sizeZ];
		}
	}
	//initialize all neurons
	//however we assign signals to those cells that we do not need
	//since still needs linear time, not a bit issue
	//we can change it later.
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {
				neurons[i][j][k] = new singleNeuron(iData);
			}
		}
	}
	//array that stores all neuron coordinates
	//only store those have neurons on them
	//however, the REAL neurons number would be = count * density
	neuronsLocation = new Coordinates[result.count];
	//set the neuron density
	result.density = (double)iData.neuronNumber / result.count;
	//initializing neurons layer by layer.
	if (result.layers > 0) {
		markSurrounding(Coordinates(0, 0, 0), offset, result.count, 'O', neuronsLocation, 1);
	}

}



///-------------------------------------------------------------------------------------------------
/// <summary>	connect wire with neurons.  </summary>
///
/// <param name="w">	[in,out] If non-null, the wiresCollection to process. </param>
///-------------------------------------------------------------------------------------------------

void neuronCollection::connectWire(wiresCollection *w) {
	result.unconnectedWire = 0;	//reset the unconnected wire
								//reset the board
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {
				if (neurons[i][j][k]->getStatus() == 'X') {
					neurons[i][j][k]->setStatus('O');
				}
			}
		}
	}
	//geometric distribution to make our insertion near the center
	geometric_distribution<int> geoDisGen(0.2);
	//Randomly generate one spot as the center of our brush
	int centerPointArrayIndex = geoDisGen(rd);
	if (centerPointArrayIndex >= result.count) centerPointArrayIndex = result.count - 1;
	//store the wire location
	//we do that in this way just because we want to reuse the markSurrounding function
	Coordinates* wireLocation = new Coordinates[_iData.wireNumber];
	markSurrounding(neuronsLocation[centerPointArrayIndex], offset, _iData.wireNumber, 'X', wireLocation, result.density);
	//save the info to the wire
	for (int i = 0; i < _iData.wireNumber; i++) {
		w->getWire(i).setLocation(wireLocation[i]);
		//get the neuron location
		Coordinates tempNeuronC = convertToNormal(wireLocation[i].coorX, wireLocation[i].coorY, wireLocation[i].coorZ, offset);
		//copy the pulse to wire
		w->getWire(i).setPulses(neurons[tempNeuronC.coorX][tempNeuronC.coorY][tempNeuronC.coorZ]->getSignal()->getPulses());
	}

}

///-------------------------------------------------------------------------------------------------
/// <summary>	Gets the layers. </summary>
/// input neuron numbers
/// output the layer we need to build a hexagon
/// 1 neurons-->1 layer
/// 7 neurons-->2 layers
/// <param name="neurons">	The neurons. </param>
///
/// <returns>	The layers. </returns>
///-------------------------------------------------------------------------------------------------
int neuronCollection::getLayers(int neurons) {
	if (neurons == 0) return 0;
	int i = 1;
	while (true) {
		if ((neurons - (3 * i*(i - 1) + 1)) > 0) {
			i++;
		}
		else
			break;
	}
	return i;
}

///-------------------------------------------------------------------------------------------------
/// <summary>	convert the negative index to normal </summary>
///
/// <param name="x">	 	The x coordinate. </param>
/// <param name="y">	 	The y coordinate. </param>
/// <param name="z">	 	The z coordinate. </param>
/// <param name="offset">	The offset. </param>
///
/// <returns>	The given data converted to a normal. </returns>
///-------------------------------------------------------------------------------------------------

Coordinates neuronCollection::convertToNormal(int x, int y, int z, int offset) {
	Coordinates temp;
	temp.coorX = x + offset;
	temp.coorY = y + offset;
	temp.coorZ = z + offset;
	return temp;
}

///-------------------------------------------------------------------------------------------------
/// <summary>convert normal to negative indexes</summary>
///
/// <param name="x">	 	The x coordinate. </param>
/// <param name="y">	 	The y coordinate. </param>
/// <param name="z">	 	The z coordinate. </param>
/// <param name="offset">	The offset. </param>
///
/// <returns>	The given data converted to a hexadecimal. </returns>
///-------------------------------------------------------------------------------------------------

Coordinates neuronCollection::convertToHex(int x, int y, int z, int offset) {
	Coordinates tempH;
	tempH.coorX = x - offset;
	tempH.coorY = y - offset;
	tempH.coorZ = z - offset;
	return tempH;
}


//

///-------------------------------------------------------------------------------------------------
/// <summary>	convert hex to matrix for printing </summary>
///
/// <param name="x">	 	The x coordinate. </param>
/// <param name="y">	 	The y coordinate. </param>
/// <param name="z">	 	The z coordinate. </param>
/// <param name="offset">	The offset. </param>
///
/// <returns>	The Coordinates. </returns>
///-------------------------------------------------------------------------------------------------

Coordinates neuronCollection::hexToMaxtrix(int x, int y, int z, int offset) {
	Coordinates tempOrig = convertToHex(x, y, z, offset);
	Coordinates tempMid;
	tempMid.coorX = (tempOrig.coorZ + offset);
	tempMid.coorY = (tempOrig.coorX - tempOrig.coorY) + (2 * offset);
	return tempMid;
}




///-------------------------------------------------------------------------------------------------
/// <summary>	Sets a value. </summary>
/// set the value of the array
/// input is the hex(negative) indexes
/// <param name="x">	 	The x coordinate. </param>
/// <param name="y">	 	The y coordinate. </param>
/// <param name="z">	 	The z coordinate. </param>
/// <param name="offset">	The offset. </param>
/// <param name="c">	 	The character. </param>
///-------------------------------------------------------------------------------------------------

void neuronCollection::setValue(int x, int y, int z, int offset, char c) {
	Coordinates tempCoor = convertToNormal(x, y, z, offset);
	neurons[tempCoor.coorX][tempCoor.coorY][tempCoor.coorZ]->setStatus(c);
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Mark surrounding. </summary>
/// mark certain number of neurons to be the char that we want around a center
/// <param name="centerPoint">	The center point. </param>
/// <param name="offset">	  	The offset. </param>
/// <param name="number">	  	Number of. </param>
/// <param name="c">		  	The character. </param>
/// <param name="collection"> 	[in,out] If non-null, the collection. </param>
/// <param name="markRatio">  	The mark ratio. </param>
///-------------------------------------------------------------------------------------------------

void neuronCollection::markSurrounding(Coordinates centerPoint, int offset, int number, char c, Coordinates *collection, double markRatio) {
	int index = 0;	//the index for neuronsCollection
	int count = 0;
	//mark them layer by layer
	for (int i = 0; i < result.layers; i++) {
		for (int l = -i + centerPoint.coorX; l <= i + centerPoint.coorX; l++) {
			for (int m = -i + centerPoint.coorY; m <= i + centerPoint.coorY; m++) {
				for (int n = -i + centerPoint.coorZ; n <= i + centerPoint.coorZ; n++) {
					//make sure x+y+z =0 and x, y, z are within the boundary
					if (((l + m + n) == 0) && abs(l) < result.layers&& abs(m) < result.layers&& abs(n) < result.layers) {
						//connect ratio
						//random number generated is (0,1)
						if (markRatio == 1 || (((double)rand() / (RAND_MAX)) <= markRatio)) {
							//since we have negative index, we need to convert it to normal index
							Coordinates tempLoc = convertToNormal(l, m, n, offset);
							//if the status is not c, change it to c and increase index
							//if it is c, do nothing
							if (neurons[tempLoc.coorX][tempLoc.coorY][tempLoc.coorZ]->getStatus() != c) {
								//we could we tempLoc.coorXYZ here, just need to change the function a little bit
								setValue(l, m, n, offset, c);
								//store them into collection
								collection[index] = Coordinates(l, m, n);
								index++;
								count++;
								if (count == number) return;
							}
						}
						//if we hit a dead area, just incease the count
						else {
							result.unconnectedWire++;
							count++;
							if (count == number) return;
						}
					}
				}
			}
		}
	}
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Print current board. </summary>
///-------------------------------------------------------------------------------------------------

void neuronCollection::printCurrentBoard() {
	//print to file if checkbox is selected
	//to print, we convert the hex into 2-D matrix
	//(layers * 4 - 3) by (layers * 4 - 3)
	int coordinateXY = result.layers * 4 - 3;
	//initialize a 2-D array
	char** printMatrix = new char*[coordinateXY];
	for (int i = 0; i < coordinateXY; i++) {
		printMatrix[i] = new char[coordinateXY];
	}
	//empty the matrix
	for (int i = 0; i < coordinateXY; i++) {
		for (int j = 0; j < coordinateXY; j++) {
			printMatrix[i][j] = ' ';
		}
	}
	//loop through all neurons
	//if find a neuron, put it to matrix
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {
				if (neurons[i][j][k]->getStatus() != ' ') {
					Coordinates temp = hexToMaxtrix(i, j, k, offset);
					printMatrix[temp.coorX][temp.coorY] = neurons[i][j][k]->getStatus();
				}
			}
		}
	}
	//print out the matrix
	for (int i = 0; i < coordinateXY; i++) {
		for (int j = 0; j < coordinateXY; j++) {
			cout << printMatrix[i][j];
		}
		cout << "\n";
	}
}