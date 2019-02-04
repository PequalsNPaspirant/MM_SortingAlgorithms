#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

	//=======================+============+
	//                       | Heap Sort  |
	//=======================+============+

	//Common Helper Functions
	//------------------------------------------------------------------------------------

	int getLeftChildIndex(int index);
	int getRightChildIndex(int index);
	int getParentIndex(int index);
	int getLevel(int index);

	// sift up Functions
	//------------------------------------------------------------------------------------

	//This is equivalent to adding new element at the end of a valid heap
	//Used for heapify top-down		- Yes
	//Used for heapify bottom-up	- No
	//Used for extract Max			- No

	int leafSearch(DataSet& obj, int index);
	void siftDown2(DataSet& obj, int heapSize, int index);


	// heapify bottom-up Functions
	//------------------------------------------------------------------------------------

	void heapify_BottomUp6(DataSet& obj);

	// Extract max Functions
	//------------------------------------------------------------------------------------

	//This is most optimized function as it avoids swaps
	void extractMax2(DataSet& obj);

	// HeapSort
	//=======================================================================================

	//This is stable sort
	void HeapSortInPlace14(DataSet& obj);

}