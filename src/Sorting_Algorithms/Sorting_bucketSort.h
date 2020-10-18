#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

	//=======================+============+
	//                       | Bucket Sort / Bin Sort - Generic Bucket Sort |
	//=======================+============+
	/*
	https://en.wikipedia.org/wiki/Bucket_sort

	Keys are placed into each subarray/bucket using insertion sort so that they will be in sorted order in each bucket.

	Optimizations:
	A common optimization is to put the unsorted elements of the buckets back in the original array first,
	then run insertion sort over the complete array; because insertion sort's runtime is based on how far each element is from its final position,
	the number of comparisons remains relatively small, and the memory hierarchy is better exploited by storing the list contiguously in memory.
	*/

	int GenericBucketSort_1_calculateKey(const Object& element, int min, int max, int bucketCount);

	void GenericBucketSort_1(DataSet& obj, int lo, int hi);

	void GenericBucketSort_1(DataSet& obj);

	//=======================+============+
	//                       | Bucket Sort - Proxmap Sort |
	//=======================+============+
	/*
	The name is short for computing a "proximity map".
	*/


	//=======================+============+
	//                       | Bucket Sort - Histogram Sort |
	//=======================+============+


	//=======================+============+
	//                       | Bucket Sort - Postman's Sort |
	//=======================+============+


	//=======================+============+
	//                       | Bucket Sort - Shuffle Sort |
	//=======================+============+

}