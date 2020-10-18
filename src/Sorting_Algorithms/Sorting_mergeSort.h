#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

	//=======================+============+
	//                       | Merge Sort |
	//=======================+============+
	//This is stable sort

	// MergeSort - TopDownMerge 1 - space complexity O(n)
	//=======================================================================================

	void TopDownMerge1(DataSet& firstSet, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end, DataSet& secondSet);

	void TopDownSplit1(DataSet& firstSet, int start, int end, DataSet& secondSet);

	void MergeSortTopDown1(DataSet& obj);

	// MergeSort - TopDownMerge 2 - space complexity O(n/2)
	//We can avoid toggling of arrays here, so algorithm is cleaner
	//=======================================================================================

	void TopDownMerge2(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);

	void TopDownSplit2(DataSet& obj, int start, int end);

	void MergeSortTopDown2(DataSet& obj);

	// MergeSort - TopDownMerge 3 - space complexity O(n/2)
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge3(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);
	void TopDownSplit3(DataSet& obj, int start, int end);
	void MergeSortTopDown3(DataSet& obj);

	// MergeSort - TopDownMerge 4 - Average space complexity LESS THAN O(n/2). MAX space complexity O(n/2).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge4(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);

	void TopDownSplit4(DataSet& obj, int start, int end);
	void MergeSortTopDown4(DataSet& obj);

	// MergeSort - TopDownMerge 5 - Space complexity O(1).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge5(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);
	void TopDownSplit5(DataSet& obj, int start, int end);

	void MergeSortTopDown5(DataSet& obj);

	// MergeSort - TopDownMerge 6 - Space complexity O(1).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge6(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);

	void TopDownSplit6(DataSet& obj, int start, int end);

	void MergeSortTopDown6(DataSet& obj);

	// MergeSort - TopDownMerge 7 - Space complexity O(1).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge7(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);

	void TopDownSplit7(DataSet& obj, int start, int end);

	void MergeSortTopDown7(DataSet& obj);

	// MergeSort - BottomUpMerge 1
	//=======================================================================================

	void BottomUpMerge1(DataSet& firstSet, const unsigned int start, const unsigned int middle, const unsigned int end, DataSet& secondSet);
	void BottomUpSplit1(DataSet& obj, int size, DataSet& copy);
	void MergeSortBottomUp1(DataSet& obj);

	// MergeSort - BottomUpMerge 2 - space complexity O(n/2)
	//=======================================================================================

	void BottomUpMerge2(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);
	void BottomUpSplit2(DataSet& obj, int size);
	void MergeSortBottomUp2(DataSet& obj);


	// MergeSort - BottomUpMerge 3 - space complexity O(n/2)
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void BottomUpMerge3(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);
	void BottomUpSplit3(DataSet& obj, int size);

	void MergeSortBottomUp3(DataSet& obj);

	// MergeSort - BottomUpMerge 4 - Average space complexity LESS THAN O(n/2). MAX space complexity O(n/2).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void BottomUpMerge4(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);
	void BottomUpSplit4(DataSet& obj, int size);
	void MergeSortBottomUp4(DataSet& obj);


	// MergeSort - BottomUpMerge 5 - Space complexity O(1).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void BottomUpMerge5(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end);
	void BottomUpSplit5(DataSet& obj, int size);

	void MergeSortBottomUp5(DataSet& obj);


	// MergeSort - NaturalMerge_noIterators - space complexity O(n)
	//=======================================================================================

	void NaturalMerge_noIterators(DataSet& firstSet, int firstSetStart, int secondSetStart, int end, DataSet& secondSet);
	void NaturalMergeSortSplit_noIterators(DataSet& obj, int size, DataSet& copy);
	void NaturalMergeSort_noIterators(DataSet& obj);

	// MergeSort - NaturalMerge 1
	//This is better approach than above as it uses vector iterators - space complexity O(n)
	//=======================================================================================

	void NaturalMerge1(DataSet& firstSet, int firstSetStart, int secondSetStart, int end, DataSet& secondSet);
	void NaturalMergeSortSplit1(DataSet& obj, int size, DataSet& copy);

	void NaturalMergeSort1(DataSet& obj);

	// MergeSort - NaturalMerge 2 - space complexity O(n/2)
	//=======================================================================================

	void NaturalMerge2(DataSet& obj, int firstSetStart, int secondSetStart, int end);
	void NaturalMergeSortSplit2(DataSet& obj, int size);

	void NaturalMergeSort2(DataSet& obj);

	// MergeSort - NaturalMerge 3 - space complexity O(n/2)
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void NaturalMerge3(DataSet& obj, int firstSetStart, int secondSetStart, int end);
	void NaturalMergeSortSplit3(DataSet& obj, int size);

	void NaturalMergeSort3(DataSet& obj);


	// MergeSort - NaturalMerge 4 - Average space complexity LESS THAN O(n/2). MAX space complexity O(n/2).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void NaturalMerge4(DataSet& obj, int firstSetStart, int secondSetStart, int end);
	void NaturalMergeSortSplit4(DataSet& obj, int size);

	void NaturalMergeSort4(DataSet& obj);

	// MergeSort - NaturalMerge 4 - Average space complexity LESS THAN O(n/2). MAX space complexity O(n/2).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void NaturalMerge5(DataSet& obj, int firstSetStart, int secondSetStart, int end);
	void NaturalMergeSortSplit5(DataSet& obj, int size);

	void NaturalMergeSort5(DataSet& obj);

	/*
	DONE:
	All above 3 solutions for n/2 space complexity. Copy smaller size sorted partition and start from front or back.
	Use queue while merging to reduce space complexity further.Choose smaller sorted section to add into queue.
	With O(1) space complexity - use selection sort like technique to slide elements. Choose smaller sorted section to move.

	TODO:
	try to avoid vector for NaturalMergeSort - Looks difficult
	*/

}