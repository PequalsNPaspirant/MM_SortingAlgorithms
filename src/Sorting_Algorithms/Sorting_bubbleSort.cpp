#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_bubbleSort.h"

namespace mm {


	//=======================+=============+
	//                       | Bubble Sort |
	//=======================+=============+

	// Bubble Sort - trial version 1
	//=======================================================================================

	//Stable sort
	void bubbleSort_t1(DataSet& obj)
	{
		int size = obj.getSize();
		for (int countOfElementsToBeSorted = size; countOfElementsToBeSorted > 0; countOfElementsToBeSorted--)
		{
			bool nothingSwappedInLastIteration = true;
			for (int j = 1; j < countOfElementsToBeSorted; j++)
			{
				if (obj[j] < obj[j - 1])
				{
					obj[j - 1].swap(obj[j]);
					nothingSwappedInLastIteration = false;
				}
			}
			if (nothingSwappedInLastIteration)
				break;
		}
	}

	// Bubble Sort - 1
	//=======================================================================================

	//Stable sort
	//Optimizes the next iteration. Keeps track of last swap happened in last iteration. No comparison required after this position.
	void bubbleSort_1(DataSet& obj)
	{
		int size = obj.getSize();
		int newSize = size;
		while (newSize > 0)
		{
			int sizeAfterThisIteration = 0;
			for (int j = 1; j < newSize; j++)
			{
				if (obj[j] < obj[j - 1])
				{
					obj[j - 1].swap(obj[j]);
					sizeAfterThisIteration = j;
				}
			}
			newSize = sizeAfterThisIteration;
		}
	}

}