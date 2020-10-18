#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_insertionSort.h"

namespace mm {


	//=======================+================+
	//                       | Insertion Sort |
	//=======================+================+

	// Insertion Sort - Trial Version 1
	//=======================================================================================

	//Stable sort
	void InsertionSort_t1(DataSet& obj)
	{
		int size = obj.getSize();
		for (int i = 1; i < size; i++)
		{
			for (int j = i; j > 0; j--)
			{
				if (obj[j] < obj[j - 1])
					obj[j].swap(obj[j - 1]);
				else
					break;
			}
		}
	}

	// Insertion Sort - Trial Version 2
	//=======================================================================================

	//Stable sort
	//This is slightly faster than above
	void InsertionSort_t2(DataSet& obj)
	{
		int size = obj.getSize();
		for (int i = 1; i < size; i++)
		{
			Object temp = obj[i];
			int j;
			for (j = i; j > 0; j--)
			{
				if (temp < obj[j - 1])
					obj[j] = (obj[j - 1]);
				else
					break;
			}
			if (i != j)
				obj[j] = temp;
		}
	}

	// Insertion Sort - Trial Version 3
	//=======================================================================================

	//Stable sort
	//This is slightly faster than above. Some silly effort to save initial assignment temp = obj[i];
	void InsertionSort_t3(DataSet& obj)
	{
		int size = obj.getSize();
		for (int i = 1; i < size; i++)
		{
			if (obj[i] < obj[i - 1])
			{
				Object temp = obj[i];
				obj[i] = obj[i - 1];
				int j;
				for (j = i - 1; j > 0; j--)
				{
					if (temp < obj[j - 1])
						obj[j] = (obj[j - 1]);
					else
						break;
				}
				if (i != j)
					obj[j] = temp;
			}
		}
	}

	// Insertion Sort - Trial Version 4
	//=======================================================================================

	//Stable sort
	//Different implementation. Go on comparing adjusant elements. Iterate backwards when conflict is found. 
	void InsertionSort_t4(DataSet& obj)
	{
		int size = obj.getSize();
		int newSize = size;
		for (int i = 1; i < newSize; i++)
		{
			if (obj[i] < obj[i - 1])
			{
				obj[i].swap(obj[i - 1]);
				for (int j = i - 1; j > 0 && obj[j] < obj[j - 1]; j--)
					obj[j].swap(obj[j - 1]);
			}
		}
	}

	// Insertion Sort - Trial Version 5
	//=======================================================================================

	//Stable sort
	//Binary insertion sort
	//Do binary search to reduce comparisons.
	void InsertionSort_t5(DataSet& obj)
	{
		int size = obj.getSize();
		for (int current = 1; current < size; current++)
		{
			int left = 0;
			int right = current - 1;
			int targetPos = current;

			if (!(obj[current] < obj[right]))  // OR if (obj[right] <= obj[current])
			{
				continue;
			}
			else if (obj[current] < obj[left])
			{
				targetPos = left;
			}
			else
			{
				while ((right - left) > 1)
				{
					int mid = (left + right) / 2;
					if (obj[current] < obj[mid])
						right = mid;
					else //if (obj[mid] <= obj[current])
						left = mid;
				}
				targetPos = right;
			}

			if (current != targetPos)
			{
				Object temp = obj[current];
				for (int j = current; j > targetPos; j--)
					obj[j] = obj[j - 1];
				obj[targetPos] = temp;
			}
		}
	}

	// Insertion Sort - 1
	//=======================================================================================

	//Stable sort
	//Binary insertion sort
	//Do binary search more effectively than above algo.
	void InsertionSort_1(DataSet& obj)
	{
		int size = obj.getSize();
		for (int current = 1; current < size; current++)
		{
			int left = 0;
			int right = current;

			while (left < right)
			{
				int mid = (left + right) / 2;
				if (obj[current] < obj[mid])
					right = mid;
				else //if (obj[mid] >= obj[current])
					left = mid + 1;
			}
			int targetPos = right;

			if (current != targetPos)
			{
				Object temp = obj[current];
				for (int j = current; j > targetPos; j--)
					obj[j] = obj[j - 1];
				obj[targetPos] = temp;
			}
		}
	}


}