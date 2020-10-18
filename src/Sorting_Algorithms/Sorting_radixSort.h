#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

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

	void CountSort_t1(DataSet& obj, int base, int LSDPosition);

	void RadixSortLSD_t1(DataSet& obj);

	// Radix Sort LSD - Trial Version 2
	//It is same as above, except it uses std::partial_sum()
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void CountSort_t2(DataSet& obj, int base, int LSDPosition);

	void RadixSortLSD_t2(DataSet& obj);

	// This is best version of LSD
	// Radix Sort LSD - Version 1
	//It is same as Trial Version 2, except it avoid copying the temp array back into original array, rather it alternatively uses each array as temp array
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void CountSort_1(DataSet& input, int base, int LSDPosition, DataSet& output);

	void RadixSortLSD_1(DataSet& obj);

	// Radix Sort LSD - Trial Version 3
	// It is same as Version 1, except it does not use std::partial_sum() and 
	// it stores the start position of each object having particular digit at LSDPosition. This exactly same as what is done in Counting Sort
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void CountSort_t3(DataSet& input, int base, int LSDPosition, DataSet& output);

	void RadixSortLSD_t3(DataSet& obj);

	// Radix Sort LSD - Trial Version 3 - Stable in-place LSD radix sort
	// It is same as MSD Version 1. It does not use O(n) space, it does swapping in-place
	// THIS IS NOT POSSIBLE AND IT DOES NOT WORK as the inner swapping loop produces unstable order of objects and LSD needs stable ordering
	//=======================================================================================

	void RadixSortLSD_t4_doesNotWork(DataSet& obj, int base, int LSDPosition);
	void RadixSortLSD_t4_doesNotWork(DataSet& obj);

	// Radix Sort LSD - Trial Version 3
	// It is same as Version 1, except it uses queue instead of temp array
	// This is not more efficient, but very simple to implement
	//=======================================================================================

	void RadixSortLSD_t4(DataSet& obj, int base, int LSDPosition);

	void RadixSortLSD_t4(DataSet& obj);

	//==================================== MSD ===========================================================================================

	// Radix Sort MSD - Trial Version 1
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void RadixSortMSD_t1(DataSet& obj, int base, int lo, int hi, int MSDPosition);

	void RadixSortMSD_t1(DataSet& obj);


	// Radix Sort MSD - Trial Version 2
	// It is same as version 1, except the loop is from lo to hi
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void RadixSortMSD_t2(DataSet& obj, int base, int lo, int hi, int MSDPosition);

	void RadixSortMSD_t2(DataSet& obj);

	// Radix Sort MSD - Trial Version 3
	// This is NOT Stable sort
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void RadixSortMSD_t3(DataSet& obj, int base, int lo, int hi, int MSDPosition);

	void RadixSortMSD_t3(DataSet& obj);

	// This is the best version
	// Radix Sort MSD - Version 1
	// It is same as Trial Version 1, except it uses loop from lo to hi inseat of i = 0 to i < (hi - lo)
	// counting sort, least significant digit(LSD) first, out - of - place redistribute
	//=======================================================================================

	void RadixSortMSD_1(DataSet& obj, int base, int lo, int hi, int MSDPosition);

	void RadixSortMSD_1(DataSet& obj);

	// Radix Sort MSD - Trial Version 4
	// stable MSD, with max O(n) extra space. It uses O(n) only for first iteration
	// It is same as Version 1, except it uses extra space to sort each bucket
	//=======================================================================================

	void RadixSortMSD_t4(DataSet& obj, int base, int lo, int hi, int MSDPosition);

	void RadixSortMSD_t4(DataSet& obj);

	// Radix Sort MSD - Trial Version 5
	// It is same as LSD Trial Version 3. It uses queue for MSD.
	// This is not more efficient, but very simple to implement
	//=======================================================================================

	void RadixSortMSD_t5(DataSet& obj, int base, int lo, int hi, int MSDPosition);

	void RadixSortMSD_t5(DataSet& obj);

}