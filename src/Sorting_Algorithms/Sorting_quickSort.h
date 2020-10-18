#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

	//=======================+===============+
	//                       | Quick Sort LR |
	//=======================+===============+

	// Quick Sort LR - Trial Version 1
	// Single pivot - End element as pivot
	// This algorithm uses LEFT and RIGHT pointers and swaps them if found on wrong side of pivot
	//=======================================================================================

	void QuickSortLR_t1(DataSet& obj, int startIndex, int endIndex);

	//NOT Stable sort
	void QuickSortLR_t1(DataSet& obj);

	// Quick Sort LR - Trial Version 2
	// Single pivot - End element as pivot
	// This algorithm uses LEFT and RIGHT pointers and swaps them if found on wrong side of pivot
	//=======================================================================================

	void QuickSortLR_t2(DataSet& obj, int startIndex, int endIndex);

	//NOT Stable sort
	void QuickSortLR_t2(DataSet& obj);

	// Quick Sort LR - Trial Version 3 - TCO of Trial Version 2
	// Single pivot - End element as pivot
	// This is same as above except, Tail Call Optimization (TCO) is done for longer range
	//=======================================================================================

	void QuickSortLR_t3TCO(DataSet& obj, int startIndex, int endIndex);

	//NOT Stable sort
	//Tail recursive call optimization
	void QuickSortLR_t3TCO(DataSet& obj);


	//=======================+===============+
	//                       | Quick Sort LL |
	//=======================+===============+

	// Quick Sort LL - Trial Version 1
	// Single pivot - End element as pivot
	// This algorithm uses two LEFT pointers, but not the RIGHT pointer
	//=======================================================================================

	void QuickSortLL_t1(DataSet& obj, int startIndex, int endIndex);

	//NOT Stable sort
	void QuickSortLL_t1(DataSet& obj);

	// Quick Sort LL - Trial Version 2
	// Single pivot - End element as pivot
	// This algorithm uses two LEFT pointers, but not the RIGHT pointer
	// This is same as above except, tail call optimization is done for longer range
	//=======================================================================================

	void QuickSortLL_t2TCO(DataSet& obj, int startIndex, int endIndex);

	//NOT Stable sort
	//Tail recursive call optimization
	void QuickSortLL_t2TCO(DataSet& obj);

	//=======================+==========================================+
	//                       | 3 Way Quick Sort  OR  Ternary Quick Sort |
	//=======================+==========================================+

	// Quick Sort 3 Way - Trial Version 1
	//=======================================================================================

	// NOT Stable sort
	// Single pivot - End element as pivot
	// Divides array into 3 parts, < Pivot, == Pivot and > Pivot
	void makeUnstable3WayPartitionLR_1(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall);

	void QuickSort3WayLR_1(DataSet& obj, int startIndex, int endIndex);

	void QuickSort3WayLR_1(DataSet& obj);

	// Quick Sort 3 Way - 2
	//=======================================================================================

	// NOT Stable sort
	// This uses Dutch National Flag Algorithm
	void makeUnstable3WayPartitionLR_2(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall);

	void QuickSort3WayLR_t2(DataSet& obj, int startIndex, int endIndex);

	void QuickSort3WayLR_t2(DataSet& obj);

	// Quick Sort 3 Way - 3
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartitionLR_3(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall);

	void QuickSort3WayLR_t3(DataSet& obj, int startIndex, int endIndex);

	void QuickSort3WayLR_t3(DataSet& obj);

	// Quick Sort 3 Way - 4
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartitionLR_3Simplified(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall);

	void QuickSort3WayLR_t4(DataSet& obj, int startIndex, int endIndex);

	void QuickSort3WayLR_t4(DataSet& obj);

	// Quick Sort 3 Way - 5
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartitionLR_3Simplified2(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall);

	void QuickSort3WayLR_t5(DataSet& obj, int startIndex, int endIndex);

	void QuickSort3WayLR_t5(DataSet& obj);

	// Quick Sort 3 Way - 6
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartitionLR_3Simplified3(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall);

	void QuickSort3WayLR_t6(DataSet& obj, int startIndex, int endIndex);

	void QuickSort3WayLR_t6(DataSet& obj);

	// Quick Sort 3 Way - 7
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartition4(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall);

	void QuickSort3WayLR_t7(DataSet& obj, int startIndex, int endIndex);

	void QuickSort3WayLR_t7(DataSet& obj);




	//=======================+=======================+
	//                       | Dual Pivot Quick Sort |
	//=======================+=======================+

	// Quick Sort Dual Pivot - 1
	//=======================================================================================

	// NOT Stable sort
	// Dual Pivot - uses Leftmost and Rightmost elements as pivots
	void makeUnstableDualPivotPartition_1(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall);
	void QuickSortDualPivot_1(DataSet& obj, int startIndex, int endIndex);

	void QuickSortDualPivot_1(DataSet& obj);

	//=======================+========================+
	//                       | Multi Pivot Quick Sort |
	//=======================+========================+

	// Multi Pivot Quick Sort - 1
	//=======================================================================================

	void QuickSortMultiPivot_2Pivots(DataSet& obj);

	//NOT Stable sort
	void makeUnstableMultiPivotPartition1(DataSet& obj, int startIndex, int endIndex, vector<int>& walls, int numberOfPivots);

	void QuickSortMultiPivot(DataSet& obj, int startIndex, int endIndex, int numberOfPivots);

	void QuickSortMultiPivot(DataSet& obj, const int numberOfPivots);

	void QuickSortMultiPivot_1Pivots(DataSet& obj);

	void QuickSortMultiPivot_2Pivots(DataSet& obj);

	void QuickSortMultiPivot_3Pivots(DataSet& obj);

	void QuickSortMultiPivot_4Pivots(DataSet& obj);

	void QuickSortMultiPivot_5Pivots(DataSet& obj);

	void QuickSortMultiPivot_6Pivots(DataSet& obj);


	// Multi Pivot Quick Sort - 2 - reuse existing dual pivot algorithm
	//=======================================================================================

	//If we call dual pivot algorithm for the extreme end pivot pairs sequencially, it is as good as using dual pivot algorithm. So no need to try this.


	//=======================+======================================+
	//                       | R-Quick Sort OR Iterative Quick Sort |
	//=======================+======================================+

	int makeUnstablePartition(DataSet& obj, int startIndex, int endIndex);
	void QuickSortIterative(DataSet& obj);

}