#include <numeric> //For std::partial_sum

#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_bucketSort.h"

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

	int GenericBucketSort_1_calculateKey(const Object& element, int min, int max, int bucketCount)
	{
		double bucketWidth = double(max - min) / (bucketCount - 1); //min and max can be any number. This sort can be used for any kind of object
		return static_cast<int>(floor((element.getVal() - min) / bucketWidth));
	}

	void GenericBucketSort_1(DataSet& obj, int lo, int hi)
	{
		//Handle end conditions
		if (hi <= lo) return;
		if (hi - lo == 1)
		{
			if (obj[hi] < obj[lo])
				obj[hi].swap(obj[lo]);
			return;
		}

		int size = hi - lo + 1;
		int min = obj[lo].getVal();
		int max = min;
		for (int i = lo; i <= hi; i++)
		{
			int current = obj[i].getVal();
			if (min > current)
				min = current;
			else if (max < current)
				max = current;
		}
		//Its single repeated number set
		if (min == max) return;

		// count bucket size
		int bucketCount = size;
		std::vector<int> buckets(bucketCount, 0);

		for (int i = lo; i <= hi; i++)
		{
			int key = GenericBucketSort_1_calculateKey(obj[i], min, max, bucketCount); // Key calculating function
			buckets[key]++;
		}

		//Rest of the process can be carried out in many ways
		//Using the same logic used for "bucket-sort-subalgorithm" in radix sort above
		// inclusive prefix sum
		vector<int> bucketCumulative(bucketCount, 0);
		std::partial_sum(buckets.begin(), buckets.end(), bucketCumulative.begin());

		// reorder items in-place by walking cycles
		for (int i = lo; i <= hi; )
		{
			int key = GenericBucketSort_1_calculateKey(obj[i], min, max, bucketCount);
			int position = --bucketCumulative[key];
			while ((lo + position) > i)
			{
				obj[i].swap(obj[lo + position]);
				key = GenericBucketSort_1_calculateKey(obj[i], min, max, bucketCount);
				position = --bucketCumulative[key];
			}
			i += buckets[key];
		}

		// recurse on buckets
		int position = lo;
		for (int i = 0; i < bucketCount; ++i)
		{
			if (buckets[i] > 1)
				GenericBucketSort_1(obj, position, position + buckets[i] - 1);
			position += buckets[i];
		}
	}

	void GenericBucketSort_1(DataSet& obj)
	{
		int size = obj.getSize();
		GenericBucketSort_1(obj, 0, size - 1);
	}

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