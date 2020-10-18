#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_selectionSort.h"

namespace mm {


	//=======================+================+
	//                       | Selection Sort |
	//=======================+================+

	// Selection Sort - Trial Version 1
	//=======================================================================================

	//NOT Stable sort
	void SelectionSort_t1(DataSet& obj)
	{
		int size = obj.getSize();
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (obj[j] < obj[i])
					obj[i].swap(obj[j]);
			}
		}
	}

	// Selection Sort - 1
	//=======================================================================================

	//NOT Stable sort
	void SelectionSort_1(DataSet& obj)
	{
		int size = obj.getSize();
		for (int i = 0; i < size - 1; i++)
		{
			int iMin = i;
			for (int j = i + 1; j < size; j++)
			{
				if (obj[j] < obj[iMin])
					iMin = j;
			}
			if (i != iMin)
				obj[i].swap(obj[iMin]);
		}
	}

}