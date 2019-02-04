

#include "Sorting_heapSort/Sorting_heapSort_v.h"

namespace mm {

	//=======================+============+
	//                       | Heap Sort  |
	//=======================+============+

	//Common Helper Functions
	//------------------------------------------------------------------------------------

	int getLeftChildIndex(int index) {
		return (index * 2 + 1);
	}

	int getRightChildIndex(int index) {
		return (index * 2 + 2);
	}

	int getParentIndex(int index) {
		return ((index + 1) / 2 - 1);
	}

	int getLevel(int index) //level starts from zero
	{
		return floor(log(index + 1));
	}

	// sift up Functions
	//------------------------------------------------------------------------------------

	//This is equivalent to adding new element at the end of a valid heap
	//Used for heapify top-down		- Yes
	//Used for heapify bottom-up	- No
	//Used for extract Max			- No

	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- No
	//Used for extract Max			- Yes
	int leafSearch(DataSet& obj, int index)
	{
		int retVal = -1;
		size_t leftChildIndex = getLeftChildIndex(index);
		size_t rightChildIndex = getRightChildIndex(index); //OR rightChildIndex = leftChildIndex + 1
		if (leftChildIndex < obj.getSize())
		{
			retVal = leftChildIndex;
			if (rightChildIndex < obj.getSize())
			{
				if (obj[leftChildIndex] < obj[rightChildIndex])
					retVal = rightChildIndex;
				else
					retVal = leftChildIndex;
			}
		}
		return retVal;
	}
	void siftDown2(DataSet& obj, int heapSize, int index)
	{
		int biggestChild = leafSearch(obj, index);
		while (biggestChild != -1 && biggestChild > heapSize)
		{
			//Object temp = obj[index];
			obj[index] = obj[biggestChild];
			index = biggestChild;
			biggestChild = leafSearch(obj, index);
		}
	}


	// heapify bottom-up Functions
	//------------------------------------------------------------------------------------

	void heapify_BottomUp6(DataSet& obj)
	{
		int size = obj.getSize();
		int parentIndex = getParentIndex(size - 1);
		for (int subTreeRootIndex = parentIndex; subTreeRootIndex >= 0; subTreeRootIndex--)
			siftDown2(obj, size, subTreeRootIndex);
	}

	// Extract max Functions
	//------------------------------------------------------------------------------------

	//This is most optimized function as it avoids swaps
	void extractMax2(DataSet& obj)
	{
		// One by one extract an element from heap
		int size = obj.getSize();
		for (int heapSize = size - 1; heapSize > 0; heapSize--)
		{
			// Move current root to end
			Object temp = obj[0];

			// call max heapify on the reduced heap
			siftDown2(obj, heapSize, 0);

			obj[heapSize] = temp;
		}
	}

	// HeapSort
	//=======================================================================================

	//This is stable sort
	void HeapSortInPlace14(DataSet& obj)
	{
		heapify_BottomUp6(obj);
		extractMax2(obj);
	}

}