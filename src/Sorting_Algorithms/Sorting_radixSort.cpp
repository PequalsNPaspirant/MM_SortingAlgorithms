#include <queue>
#include <numeric> //For std::partial_sum

#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_radixSort.h"

namespace mm {


	//=======================+============+
	//                       | Radix Sort |
	//=======================+============+

	// ---------------------- LSD -----------------------------------------------------------
	/*
	If w is width (number of digits in a NUMBER or number of letter in STRING), n are total object to be sorted,
	then the time complexity is O(w * n).
		Note:	Here the time complexity os radix sort is not in terms of comparisons. There is no comparison happens in radix sort.
				The w * n is equal to the number of times the elements of collection are accessed.
	The best comparison sort can sort objects in O(n * log2 n)
	So, radix sort is better than comparison sort only if
		w < log2 n
		But w = logb(max object)
	base for above equation is b
	i.e. to do radix sort more effectively than comparison sort =>
		logb(max object) < log2 n
	Since base, n and max object are positive real numbers, if we raise b to the power equal to LHS & RHS, then
		b ^ logb(max object) < b ^ log2 n
	As we know b ^ logb(X) = X
		max object < b ^ (log2 n)
		pow(max object, 1/(log2 n)) < b
		b > pow(max object, 1/(log2 n))

	Thus, choose a base of system such that it is more than pow(max object, 1/(log2 n))

	Example:
		When n = 100, and max object is 500, then
		log2(100) = 6.6439
		1 / log2(100) = 1 / 6.6439 = 0.1505
		pow(500, 0.1505) = 2.5482
		Thus base should be more than 2.5482
	Tally:
	When base = 2.5482
		w = logb(max object)
		w = log2.548(500)
		w = 6.6439
		min radix sort time complexity = O(w * n) = O(6.6439 * 100) = O(664.39)
		Optimum comparison sort time complexity = O(100 * log2(100)) = O(100 * 6.6439) = O(664.39)

	The time complexity of radix sort can approach O(n) when w approaches 1
	Lets repsent it as
		w --> 1
		logb(max object) --> 1
	This can happen in 2 situation
	First situation
		max object can be zero
	Second situation
		b --> max object

	Moral of story is
		Choose the base as close as max object

	This is same as doing counting sort of objects over range from 1 to max object, each object represents unique digit/place in NUMBER SYSTEM REPRESENTATION
	w will be 1 in this case, so there is no need to do second iteration, as second digit will not be present in this SYSTEM with base = max number
	*/

	// Radix Sort LSD - Trial Version 1
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void CountSort_t1(DataSet& obj, int base, int LSDPosition)
	{
		int size = obj.getSize();
		int currentPositionVal = static_cast<int>(pow(base, LSDPosition));
		std::vector<int> count(base, 0);
		// Store count of occurrences in count[]
		for (int i = 0; i < size; i++)
		{
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			count[currentDigit]++;
		}

		// Change count[i] so that count[i] now contains actual
		//  position of this digit in output[]
		for (int i = 1; i < base; i++)
			count[i] += count[i - 1];

		// Build the output array
		DataSet copy(obj.getCopy());
		for (int i = size - 1; i >= 0; i--)
		{
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			copy[count[currentDigit] - 1] = obj[i];
			count[currentDigit]--;
		}

		// Copy the output array to arr[], so that arr[] now
		// contains sorted numbers according to current digit
		for (int i = 0; i < size; i++)
			obj[i] = copy[i];

	}

	void RadixSortLSD_t1(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		if (max == 100)
		{
			int breakpoint = 0; ++breakpoint;
		}

		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
		{
			CountSort_t1(obj, base, LSDPosition);
		}
	}

	// Radix Sort LSD - Trial Version 2
	//It is same as above, except it uses std::partial_sum()
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void CountSort_t2(DataSet& obj, int base, int LSDPosition)
	{
		int size = obj.getSize();
		int currentPositionVal = static_cast<int>(pow(base, LSDPosition));
		std::vector<int> count(base, 0);
		// Store count of occurrences in count[]
		for (int i = 0; i < size; i++)
		{
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			count[currentDigit]++;
		}

		// Change count[i] so that count[i] now contains actual
		//  position of this digit in output[]
		//for (int i = 1; i < base; i++)
		//	count[i] += count[i - 1];
		std::partial_sum(count.begin(), count.end(), count.begin());

		// Build the output array
		DataSet copy(obj.getCopy());
		for (int i = size - 1; i >= 0; i--)
		{
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			copy[count[currentDigit] - 1] = obj[i];
			count[currentDigit]--;
		}

		// Copy the output array to arr[], so that arr[] now
		// contains sorted numbers according to current digit
		for (int i = 0; i < size; i++)
			obj[i] = copy[i];

	}

	void RadixSortLSD_t2(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
		{
			CountSort_t2(obj, base, LSDPosition);
		}
	}

	// This is best version of LSD
	// Radix Sort LSD - Version 1
	//It is same as Trial Version 2, except it avoid copying the temp array back into original array, rather it alternatively uses each array as temp array
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void CountSort_1(DataSet& input, int base, int LSDPosition, DataSet& output)
	{
		int size = input.getSize();
		int currentPositionVal = static_cast<int>(pow(base, LSDPosition));
		std::vector<int> count(base, 0);
		// Store count of occurrences in count[]
		for (int i = 0; i < size; i++)
		{
			int currentDigit = (input[i].getVal() / currentPositionVal) % base;
			count[currentDigit]++;
		}

		// Change count[i] so that count[i] now contains actual
		//  position of this digit in output[]
		std::partial_sum(count.begin(), count.end(), count.begin());

		// Build the output array
		for (int i = size - 1; i >= 0; i--)
		{
			int currentDigit = (input[i].getVal() / currentPositionVal) % base;
			output[--count[currentDigit]] = input[i];
		}
	}

	void RadixSortLSD_1(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		DataSet copy(obj.getCopy());
		bool toggle = (maxDigits % 2 == 0);
		for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
		{
			if (toggle)
				CountSort_1(obj, base, LSDPosition, copy);
			else
				CountSort_1(copy, base, LSDPosition, obj);
			toggle = !toggle;
		}
	}

	// Radix Sort LSD - Trial Version 3
	// It is same as Version 1, except it does not use std::partial_sum() and 
	// it stores the start position of each object having particular digit at LSDPosition. This exactly same as what is done in Counting Sort
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void CountSort_t3(DataSet& input, int base, int LSDPosition, DataSet& output)
	{
		int size = input.getSize();
		int currentPositionVal = static_cast<int>(pow(base, LSDPosition));
		std::vector<int> count(base, 0);
		// Store count of occurrences in count[]
		for (int i = 0; i < size; i++)
		{
			int currentDigit = (input[i].getVal() / currentPositionVal) % base;
			count[currentDigit]++;
		}

		// Change count[i] so that count[i] now contains actual start
		// position of this digit in output[]
		int lastCount = count[0];
		count[0] = 0;
		for (int i = 1; i < base; i++)
		{
			int currentCountBackup = count[i];
			count[i] = count[i - 1] + lastCount;
			lastCount = currentCountBackup;
		}

		// Build the output array
		for (int i = 0; i < size; i++)
		{
			int currentDigit = (input[i].getVal() / currentPositionVal) % base;
			output[count[currentDigit]++] = input[i];
		}
	}

	void RadixSortLSD_t3(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		DataSet copy(obj.getCopy());
		bool toggle = (maxDigits % 2 == 0);
		for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
		{
			if (toggle)
				CountSort_t3(obj, base, LSDPosition, copy);
			else
				CountSort_t3(copy, base, LSDPosition, obj);
			toggle = !toggle;
		}
	}

	// Radix Sort LSD - Trial Version 3 - Stable in-place LSD radix sort
	// It is same as MSD Version 1. It does not use O(n) space, it does swapping in-place
	// THIS IS NOT POSSIBLE AND IT DOES NOT WORK as the inner swapping loop produces unstable order of objects and LSD needs stable ordering
	//=======================================================================================

	void RadixSortLSD_t4_doesNotWork(DataSet& obj, int base, int LSDPosition)
	{
		int currentPositionVal = static_cast<int>(pow(base, LSDPosition));

		// count digits
		int size = obj.getSize();
		std::vector<int> count(base, 0);

		for (int i = 0; i < size; ++i)
		{
			int currentDigit = obj[i].getVal() / currentPositionVal % base;
			count[currentDigit]++;
		}

		// inclusive prefix sum
		vector<int> bucket(base, 0);
		std::partial_sum(count.begin(), count.end(), bucket.begin());

		// reorder items in-place by walking cycles
#ifdef DEBUG
		int countLoop = 0;
#endif

		for (int i = 0; i < size; )
		{
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			int position = --bucket[currentDigit];
			while ((position) > i)
			{
#ifdef DEBUG
				++countLoop;
#endif
				obj[i].swap(obj[position]);
				currentDigit = (obj[i].getVal() / currentPositionVal) % base;
				position = --bucket[currentDigit];
			}

#ifdef DEBUG
			++countLoop;
#endif

			i += count[currentDigit];
		}

#ifdef DEBUG
		if (countLoop > (hi - lo))
			cout << "\n\n---------------------RadixSortMSD_t2 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif
	}

	void RadixSortLSD_t4_doesNotWork(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
		{
			RadixSortLSD_t4_doesNotWork(obj, base, LSDPosition);
		}
	}

	// Radix Sort LSD - Trial Version 3
	// It is same as Version 1, except it uses queue instead of temp array
	// This is not more efficient, but very simple to implement
	//=======================================================================================

	void RadixSortLSD_t4(DataSet& obj, int base, int LSDPosition)
	{
		int size = obj.getSize();
		int currentPositionVal = static_cast<int>(pow(base, LSDPosition));

		std::queue<Object>* buckets = new std::queue<Object>[base];
		// Store count of occurrences in count[]
		for (int i = 0; i < size; i++)
		{
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			buckets[currentDigit].push(obj[i]);
		}

		int counter = 0;
		for (int i = 0; i < base; i++)
		{
			while (!buckets[i].empty())
			{
				obj[counter++] = buckets[i].front();
				buckets[i].pop();
			}
		}

		MyAssert::myRunTimeAssert(counter == size, "Size mismatch");

		delete[] buckets;
	}

	void RadixSortLSD_t4(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
		{
			RadixSortLSD_t4(obj, base, LSDPosition);
		}
	}

	//==================================== MSD ===========================================================================================

	// Radix Sort MSD - Trial Version 1
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void RadixSortMSD_t1(DataSet& obj, int base, int lo, int hi, int MSDPosition)
	{
		int currentPositionVal = static_cast<int>(pow(base, MSDPosition));

		// count digits
		std::vector<int> count(base, 0);

		for (int i = lo; i <= hi; ++i)
		{
			int currentDigit = obj[i].getVal() / currentPositionVal % base;
			count[currentDigit]++;
		}

		// inclusive prefix sum
		vector<int> bucket(base, 0);
		std::partial_sum(count.begin(), count.end(), bucket.begin());

		// reorder items in-place by walking cycles
#ifdef DEBUG
		int countLoop = 0;
#endif

		for (int i = 0, j; i <= (hi - lo); )
		{
			int currentDigit = (obj[lo + i].getVal() / currentPositionVal) % base;
			while ((j = --bucket[currentDigit]) > i)
			{
#ifdef DEBUG
				++countLoop;
#endif
				obj[lo + i].swap(obj[lo + j]);
				currentDigit = (obj[lo + i].getVal() / currentPositionVal) % base;
			}

#ifdef DEBUG
			++countLoop;
#endif

			i += count[currentDigit];
		}

#ifdef DEBUG
		if (countLoop > (hi - lo))
			cout << "\n\n---------------------RadixSortMSD_t1 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif

		// no more depth to sort?
		if (MSDPosition == 0) return;

		// recurse on buckets
		int position = lo;
		for (int i = 0; i < base; ++i)
		{
			if (count[i] > 1)
				RadixSortMSD_t1(obj, base, position, position + count[i] - 1, MSDPosition - 1);
			position += count[i];
		}
	}

	void RadixSortMSD_t1(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		RadixSortMSD_t1(obj, base, 0, size - 1, maxDigits - 1);
	}


	// Radix Sort MSD - Trial Version 2
	// It is same as version 1, except the loop is from lo to hi
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void RadixSortMSD_t2(DataSet& obj, int base, int lo, int hi, int MSDPosition)
	{
		int currentPositionVal = static_cast<int>(pow(base, MSDPosition));

		// count digits
		std::vector<int> count(base, 0);

		for (int i = lo; i <= hi; ++i)
		{
			int currentDigit = obj[i].getVal() / currentPositionVal % base;
			count[currentDigit]++;
		}

		// inclusive prefix sum
		vector<int> bucket(base, 0);
		std::partial_sum(count.begin(), count.end(), bucket.begin());

		std::vector<int> countTemp(count);

#ifdef DEBUG
		int countLoop = 0;
#endif

		for (int i = lo; i <= hi;)
		{
#ifdef DEBUG
			++countLoop;
#endif

			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			int position = --bucket[currentDigit] + lo;
			if (--countTemp[currentDigit] >= 0 && i != position)
				obj[position].swap(obj[i]);
			else
				i += count[currentDigit];
		}

#ifdef DEBUG
		if (countLoop > (hi - lo))
			cout << "\n\n---------------------RadixSortMSD_t3 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif

		// no more depth to sort?
		if (MSDPosition == 0) return;

		// recurse on buckets
		int position = lo;
		for (int i = 0; i < base; ++i)
		{
			if (count[i] > 1)
				RadixSortMSD_t2(obj, base, position, position + count[i] - 1, MSDPosition - 1);
			position += count[i];
		}
	}

	void RadixSortMSD_t2(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		RadixSortMSD_t2(obj, base, 0, size - 1, maxDigits - 1);
	}

	// Radix Sort MSD - Trial Version 3
	// This is NOT Stable sort
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void RadixSortMSD_t3(DataSet& obj, int base, int lo, int hi, int MSDPosition)
	{
		int currentPositionVal = static_cast<int>(pow(base, MSDPosition));

		// count digits
		std::vector<int> count(base, 0);

		for (int i = lo; i <= hi; ++i)
		{
			int currentDigit = obj[i].getVal() / currentPositionVal % base;
			count[currentDigit]++;
		}

		// inclusive prefix sum
		vector<int> bucket(base, 0);
		std::partial_sum(count.begin(), count.end(), bucket.begin());

		std::vector<int> countTemp(count);

#ifdef DEBUG
		int countLoop = 0;
#endif

		for (int i = hi; i >= lo;)
		{
#ifdef DEBUG
			++countLoop;
#endif
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			int position = --bucket[currentDigit] + lo;
			if (--countTemp[currentDigit] >= 0 && i != position)
				obj[position].swap(obj[i]);
			else
				--i;
		}

#ifdef DEBUG
		if (countLoop > (hi - lo))
			cout << "\n\n---------------------RadixSortMSD_t4 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif

		// no more depth to sort?
		if (MSDPosition == 0) return;

		// recurse on buckets
		int position = lo;
		for (int i = 0; i < base; ++i)
		{
			if (count[i] > 1)
				RadixSortMSD_t3(obj, base, position, position + count[i] - 1, MSDPosition - 1);
			position += count[i];
		}
	}

	void RadixSortMSD_t3(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		RadixSortMSD_t3(obj, base, 0, size - 1, maxDigits - 1);
	}

	// This is the best version
	// Radix Sort MSD - Version 1
	// It is same as Trial Version 1, except it uses loop from lo to hi inseat of i = 0 to i < (hi - lo)
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void RadixSortMSD_1(DataSet& obj, int base, int lo, int hi, int MSDPosition)
	{
		int currentPositionVal = static_cast<int>(pow(base, MSDPosition));

		// count digits
		std::vector<int> count(base, 0);

		for (int i = lo; i <= hi; ++i)
		{
			int currentDigit = obj[i].getVal() / currentPositionVal % base;
			count[currentDigit]++;
		}

		// inclusive prefix sum
		vector<int> bucket(base, 0);
		std::partial_sum(count.begin(), count.end(), bucket.begin());

		// reorder items in-place by walking cycles
#ifdef DEBUG
		int countLoop = 0;
#endif

		for (int i = lo; i <= hi; )
		{
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			int position = --bucket[currentDigit];
			while ((lo + position) > i)
			{
#ifdef DEBUG
				++countLoop;
#endif
				obj[i].swap(obj[lo + position]);
				currentDigit = (obj[i].getVal() / currentPositionVal) % base;
				position = --bucket[currentDigit];
			}

#ifdef DEBUG
			++countLoop;
#endif

			i += count[currentDigit];
		}

#ifdef DEBUG
		if (countLoop > (hi - lo))
			cout << "\n\n---------------------RadixSortMSD_t2 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif

		// no more depth to sort?
		if (MSDPosition == 0) return;

		// recurse on buckets
		int position = lo;
		for (int i = 0; i < base; ++i)
		{
			if (count[i] > 1)
				RadixSortMSD_1(obj, base, position, position + count[i] - 1, MSDPosition - 1);
			position += count[i];
		}
	}

	void RadixSortMSD_1(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		RadixSortMSD_1(obj, base, 0, size - 1, maxDigits - 1);
	}

	// Radix Sort MSD - Trial Version 4
	// stable MSD, with max O(n) extra space. It uses O(n) only for first iteration
	// It is same as Version 1, except it uses extra space to sort each bucket
	//=======================================================================================

	void RadixSortMSD_t4(DataSet& obj, int base, int lo, int hi, int MSDPosition)
	{
		int currentPositionVal = static_cast<int>(pow(base, MSDPosition));

		// count digits
		std::vector<int> count(base, 0);

		for (int i = lo; i <= hi; ++i)
		{
			int currentDigit = obj[i].getVal() / currentPositionVal % base;
			count[currentDigit]++;
		}

		// inclusive prefix sum
		vector<int> bucket(base, 0);
		std::partial_sum(count.begin(), count.end(), bucket.begin());

		DataSet copy("Copy", hi - lo + 1);
		for (int i = lo; i <= hi; i++)
			copy[i - lo] = obj[i];

		for (int i = hi; i >= lo; i--)
		{
			int currentDigit = (copy[i - lo].getVal() / currentPositionVal) % base;
			int position = --bucket[currentDigit];
			obj[lo + position] = copy[i - lo];
		}

		// no more depth to sort?
		if (MSDPosition == 0) return;

		// recurse on buckets
		int position = lo;
		for (int i = 0; i < base; ++i)
		{
			if (count[i] > 1)
				RadixSortMSD_t4(obj, base, position, position + count[i] - 1, MSDPosition - 1);
			position += count[i];
		}
	}

	void RadixSortMSD_t4(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		RadixSortMSD_t4(obj, base, 0, size - 1, maxDigits - 1);
	}

	// Radix Sort MSD - Trial Version 5
	// It is same as LSD Trial Version 3. It uses queue for MSD.
	// This is not more efficient, but very simple to implement
	//=======================================================================================

	void RadixSortMSD_t5(DataSet& obj, int base, int lo, int hi, int MSDPosition)
	{
		//int size = obj.getSize();
		int currentPositionVal = static_cast<int>(pow(base, MSDPosition));

		std::queue<Object>* buckets = new std::queue<Object>[base];
		// Store count of occurrences in count[]
		for (int i = lo; i <= hi; i++)
		{
			int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			buckets[currentDigit].push(obj[i]);
		}

		// count digits
		std::vector<int> count(base, 0);
		int counter = lo;
		for (int i = 0; i < base; i++)
		{
			//Store bucket count before emptying it
			count[i] = static_cast<int>(buckets[i].size());
			while (!buckets[i].empty())
			{
				obj[counter++] = buckets[i].front();
				buckets[i].pop();
			}
		}

		MyAssert::myRunTimeAssert(counter == hi + 1, "Size mismatch");

		delete[] buckets;

		// no more depth to sort?
		if (MSDPosition == 0) return;

		// recurse on buckets
		int position = lo;
		for (int i = 0; i < base; ++i)
		{
			if (count[i] > 1)
				RadixSortMSD_t5(obj, base, position, position + count[i] - 1, MSDPosition - 1);
			position += count[i];
		}
	}

	void RadixSortMSD_t5(DataSet& obj)
	{
		int size = obj.getSize();
		const unsigned int base = 10;
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (Object(max) < obj[i])
				max = obj[i].getVal();
		}
		const unsigned int maxDigits = static_cast<unsigned int>(ceil(log(max + 1) / log(base)));
		RadixSortMSD_t5(obj, base, 0, size - 1, maxDigits - 1);
	}


}