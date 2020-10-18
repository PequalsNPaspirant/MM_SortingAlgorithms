#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

	//=======================+============+
	//                       | Shell Sort |
	//=======================+============+

	// Shell Sort - common functions
	//=======================================================================================

	void InsertionSort_t1_modifiedToResuseForShellSort(DataSet& obj, const vector<int>& gapSequence);

	//This algo is more efficient than above binary search in case of shell sort, since in shell sort
	//the original array is subdivided and the insertion sort is performed over a shorter length array (at indices 0, 0 + gap, 0 + 2*gap, ...etc)
	//So binary search over previous array is not required. Binary search is useful when the element is to be inserted in the large sorted array 
	void InsertionSort_t2_modifiedToResuseForShellSort(DataSet& obj, const vector<int>& gapSequence);

	// Shell Sort 1 - fibonacci series as gap sequence
	//=======================================================================================

	void ShellSort_t1(DataSet& obj);

	void ShellSort_t2(DataSet& obj);

	// Shell Sort 1 - gap sequence - 1, 2, 4, 8, ..., 2^n
	//=======================================================================================

	void ShellSort_t3(DataSet& obj);

	void ShellSort_t4(DataSet& obj);

	// Shell Sort 1 - gap sequence - n/2, n/4, n/8, ..., 1
	//=======================================================================================

	void ShellSort_t5(DataSet& obj);

	void ShellSort_t6(DataSet& obj);

}