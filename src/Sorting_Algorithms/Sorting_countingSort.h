#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

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

	int CountingSort_1_calculateKey(const Object& element, int min);

	void CountingSort_1(DataSet& obj);

}