#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

	//=======================+============+
	//                       | Heap Sort |
	//=======================+============+

	//Common Helper Functions
	//------------------------------------------------------------------------------------

	int LeftChild(int index);

	int RightChild(int index);
	int Parent(int index);
	int getLeftChildIndex(int index);

	int getRightChildIndex(int index);

	//floor rounds towards negative infinity, while integer division rounds towards zero (truncates)
	// floor((2 - 1) / 2.0) = floor(0.5) = 0
	// (2 - 1) / 2 = 1 / 2 = 0   ( .5 is truncated from actual result 0.5. In fact, integer division does not calculate anything after decimal point)
	// (2 + 1) / 2 - 1 = 3 / 2 - 1 = 1 - 1 = 0

	int getParentIndex(int index);

	int getParentIndex2(int index);

	int getParentIndex3(int index);

	int getParentIndex4(int index);
	int getLevel(int index); //level starts from zero


	// sift up Functions
	//------------------------------------------------------------------------------------

	//This is equivalent to adding new element at the end of a valid heap
	//Used for heapify top-down		- Yes
	//Used for heapify bottom-up	- No
	//Used for extract Max			- No

	void siftUp1(DataSet& obj, int childIndex);

	//This is equivalent to replacing the top element of a valid heap. So new top element needs to be places at appropriate position
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftUp2(DataSet& obj, const int heapSize, const int index);

	//This is optimized version of siftUp2(). Do binary search in SECOND while loop along the path the root element can descend. So the element can be positioned in O(log log n)
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftUp3(DataSet& obj, const int heapSize, const int index);

	//This is optimized version of siftUp3(). Return if the top element is already at right position.
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftUp4(DataSet& obj, const int heapSize, const int index);

	//This is optimized version of siftUp4(). Return if the top element is already at right position. But do binary search more efficiently.
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftUp5(DataSet& obj, const int heapSize, const int index);


	//This is optimized version of siftUp2(). Do binary search in FIRST while loop along the path the root element can descend. 
	//So the element can be positioned in O(log log n). Second while loop may not be needed. This may give same performace as siftDown3().
	//In fact it is same as siftDown3() because the first loop descends down, so it is sift-down.
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftDown3(DataSet& obj, const int heapSize, const int index);
	void siftUp6(DataSet& obj, const int heapSize, const int index);

	// sift down Functions
	//------------------------------------------------------------------------------------

	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftDown1_usingRecursion(DataSet& obj, int heapSize, int subTreeRootIndex);
	void siftDown1_withoutRecursion(DataSet& obj, int heapSize, int subTreeRootIndex);

	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- No
	//Used for extract Max			- Yes
	int leafSearch(DataSet& obj, int index);
	void siftDown2(DataSet& obj, int heapSize, int index);

	//This is optimized version of siftDown1_withoutRecursion(). Do binary search along the path the root element can descend. So the element can be positioned in O(log log n)
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftDown3(DataSet& obj, int heapSize, int index);

	//This is optimized version of siftDown3(). Return if the top element is already at right position.
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftDown4(DataSet& obj, int heapSize, int index);

	// heapify top-down Functions
	//------------------------------------------------------------------------------------

	void heapify_TopDown1(DataSet& obj);

	// heapify bottom-up Functions
	//------------------------------------------------------------------------------------

	void heapify_BottomUp1_usingRecursion(DataSet& obj);

	void heapify_BottomUp1_withoutRecursion(DataSet& obj);
	void heapify_BottomUp2(DataSet& obj);

	void heapify_BottomUp3(DataSet& obj);
	void heapify_BottomUp4(DataSet& obj);
	void heapify_BottomUp5(DataSet& obj);

	void heapify_BottomUp6(DataSet& obj);

	// Extract max Functions
	//------------------------------------------------------------------------------------

	void extractMax1_usingRecursion(DataSet& obj);

	void extractMax1_withoutRecursion(DataSet& obj);

	//This is most optimized function as it avoids swaps
	void extractMax2(DataSet& obj);

	void extractMax3(DataSet& obj);

	void extractMax4(DataSet& obj);

	// HeapSort
	//=======================================================================================

	//This is NOT stable sort
	void HeapSortInPlace1(DataSet& obj);

	//This is stable sort
	void HeapSortInPlace2(DataSet& obj);

	//This is NOT stable sort
	void HeapSortInPlace3(DataSet& obj);

	//This is NOT stable sort
	void HeapSortInPlace4(DataSet& obj);

	//This is NOT stable sort
	void HeapSortInPlace5(DataSet& obj);

	//This is stable sort
	void HeapSortInPlace6(DataSet& obj);

	//This is NOT stable sort
	void HeapSortInPlace7(DataSet& obj);

	//This is NOT stable sort
	void HeapSortInPlace8(DataSet& obj);

	//This is stable sort
	void HeapSortInPlace9(DataSet& obj);

	//This is NOT stable sort
	void HeapSortInPlace10(DataSet& obj);

	//This is stable sort
	void HeapSortInPlace11(DataSet& obj);

	//This is stable sort
	void HeapSortInPlace12(DataSet& obj);

	//This is stable sort
	void HeapSortInPlace13(DataSet& obj);

	//This is stable sort
	void HeapSortInPlace14(DataSet& obj);

}