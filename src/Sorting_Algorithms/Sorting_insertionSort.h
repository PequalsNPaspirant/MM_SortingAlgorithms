#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

	//=======================+================+
	//                       | Insertion Sort |
	//=======================+================+

	// Insertion Sort - Trial Version 1
	//=======================================================================================

	//Stable sort
	void InsertionSort_t1(DataSet& obj);

	// Insertion Sort - Trial Version 2
	//=======================================================================================

	//Stable sort
	//This is slightly faster than above
	void InsertionSort_t2(DataSet& obj);

	// Insertion Sort - Trial Version 3
	//=======================================================================================

	//Stable sort
	//This is slightly faster than above. Some silly effort to save initial assignment temp = obj[i];
	void InsertionSort_t3(DataSet& obj);

	// Insertion Sort - Trial Version 4
	//=======================================================================================

	//Stable sort
	//Different implementation. Go on comparing adjusant elements. Iterate backwards when conflict is found. 
	void InsertionSort_t4(DataSet& obj);

	// Insertion Sort - Trial Version 5
	//=======================================================================================

	//Stable sort
	//Binary insertion sort
	//Do binary search to reduce comparisons.
	void InsertionSort_t5(DataSet& obj);

	// Insertion Sort - 1
	//=======================================================================================

	//Stable sort
	//Binary insertion sort
	//Do binary search more effectively than above algo.
	void InsertionSort_1(DataSet& obj);

}