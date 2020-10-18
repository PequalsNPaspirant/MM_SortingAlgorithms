#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

	//=======================+=============+
	//                       | Bubble Sort |
	//=======================+=============+

	// Bubble Sort - trial version 1
	//=======================================================================================

	//Stable sort
	void bubbleSort_t1(DataSet& obj);

	// Bubble Sort - 1
	//=======================================================================================

	//Stable sort
	//Optimizes the next iteration. Keeps track of last swap happened in last iteration. No comparison required after this position.
	void bubbleSort_1(DataSet& obj);

}