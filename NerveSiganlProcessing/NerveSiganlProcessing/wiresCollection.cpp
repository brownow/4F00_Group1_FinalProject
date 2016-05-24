///-------------------------------------------------------------------------------------------------
// file:	wiresCollection.cpp
//
// summary:	Implements the wires collection class
///-------------------------------------------------------------------------------------------------
#include "wiresCollection.h"

///-------------------------------------------------------------------------------------------------
/// <summary>	Constructor. </summary>
///
/// <param name="iData"> Input data. </param>
///-------------------------------------------------------------------------------------------------
wiresCollection::wiresCollection(InputData iData)
{
	wires = new singleWire[iData.wireNumber];
	_iData = iData;

}


///-------------------------------------------------------------------------------------------------
/// <summary>print the location of each wire </summary>
///-------------------------------------------------------------------------------------------------
void wiresCollection::printWiresLocation() {
	for (int i = 0; i < _iData.wireNumber; i++) {
		cout << "Wire Location:";
		wires[i].printSingleWireLocation();
		cout << "Result Location:";
		wires[i].printSingleResultLocation();
		cout << "\n";
	}
}

///-------------------------------------------------------------------------------------------------
/// <summary>print out the received signal of each wire</summary>
///-------------------------------------------------------------------------------------------------
void wiresCollection::printWiresSignal() {
	for (int i = 0; i < _iData.wireNumber; i++) {
		wires[i].printReceivedSignal();
	}
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Destructor. </summary>
///-------------------------------------------------------------------------------------------------

wiresCollection::~wiresCollection()
{
}
