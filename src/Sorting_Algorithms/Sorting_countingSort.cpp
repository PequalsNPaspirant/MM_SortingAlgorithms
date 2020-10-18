#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_countingSort.h"

namespace mm {


	//=======================+===============+
	//                       | Counting Sort |
	//=======================+===============+
	/*
	Time Complexity: O(n+k) where n is the number of elements in input array and k is the range of input.
	Auxiliary Space: O(n+k)

	Points to be noted:
	1. Counting sort is efficient if the range of input data is not significantly greater than the number of objects to be sorted. Consider the situation where the input sequence is between range 1 to 10K and the data is 10, 5, 10K, 5K.
	2. It is not a comparison based sorting. It running time complexity is O(n) with space proportional to the range of data.
	3. It is often used as a sub-routine to another sorting algorithm like radix sort.
	4. Counting sort uses a partial hashing to count the occurrence of the data object in O(1).
	5. Counting sort can be extended to work for negative inputs also.

	Exercise:
	1. Modify above code to sort the input data in the range from M to N.
	2. Modify above code to sort negative input data.
	3. Is counting sort stable and online?
	4. Thoughts on parallelizing the counting sort algorithm.
	*/

	int CountingSort_1_calculateKey(const Object& element, int min)
	{
		return element.getVal() - min;
	}

	void CountingSort_1(DataSet& obj)
	{
		int size = obj.getSize();
		int min = obj[0].getVal();
		int max = min;
		for (int i = 0; i < size; i++)
		{
			int current = obj[i].getVal();
			if (min > current)
				min = current;
			else if (max < current)
				max = current;
		}
		//Its single repeated number set
		if (min == max) return;

		// count digits
		int keyCount = max - min + 1;
		MyAssert::myRunTimeAssert(keyCount < 1024, "Count too large");
		std::vector<int> count(keyCount, 0);

		for (int i = 0; i < size; i++)
		{
			int key = CountingSort_1_calculateKey(obj[i], min); // Key calculating function
			count[key]++;
		}

		// position of this digit in output[]
		int lastCount = count[0];
		count[0] = 0;
		for (int i = 1; i < keyCount; i++)
		{
			int currentCountBackup = count[i];
			count[i] = count[i - 1] + lastCount;
			lastCount = currentCountBackup;
		}

		// Build the array
		DataSet copy(obj.getCopy());
		for (int i = 0; i < size; i++)
		{
			int key = copy[i].getVal() - min;
			obj[count[key]++] = copy[i];
		}
	}

}