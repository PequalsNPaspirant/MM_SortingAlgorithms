#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_quickSort.h"

namespace mm {


	//=======================+===============+
	//                       | Quick Sort LR |
	//=======================+===============+

	// Quick Sort LR - Trial Version 1
	// Single pivot - End element as pivot
	// This algorithm uses LEFT and RIGHT pointers and swaps them if found on wrong side of pivot
	//=======================================================================================

	void QuickSortLR_t1(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int start = startIndex;
		int end = endIndex;
		const Object pivot = obj[endIndex];

		while (start <= end)
		{
			//while (start <= end && obj[start] <= obj[pivot])
			while (obj[start] < pivot) //Above condition is replaced by this to reduce number of comparisons
				start++;
			while (pivot < obj[end])
				end--;

			if (start <= end)
			{
				obj[start].swap(obj[end]);
				start++;
				end--;
			}
		}

		QuickSortLR_t1(obj, startIndex, end);
		QuickSortLR_t1(obj, start, endIndex);
	}

	//NOT Stable sort
	void QuickSortLR_t1(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSortLR_t1(obj, 0, size - 1);
	}

	// Quick Sort LR - Trial Version 2
	// Single pivot - End element as pivot
	// This algorithm uses LEFT and RIGHT pointers and swaps them if found on wrong side of pivot
	//=======================================================================================

	void QuickSortLR_t2(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int start = startIndex;
		int end = endIndex - 1;
		const int pivot = endIndex;

		int partitionIndex = pivot;
		while (true)
		{
			//while (start <= end && obj[start] <= obj[pivot])
			while (start <= end && !(obj[pivot] < obj[start])) //Above condition is replaced by this to reduce number of comparisons
				start++;
			while (start <= end && obj[pivot] < obj[end])
				partitionIndex = end--;

			if (start < end)
			{
				obj[start].swap(obj[end]);
				start++;
				partitionIndex = end--;
			}
			else
				break;
		}

		if (partitionIndex != pivot)
			obj[partitionIndex].swap(obj[pivot]);

		QuickSortLR_t2(obj, startIndex, partitionIndex - 1);
		QuickSortLR_t2(obj, partitionIndex + 1, endIndex);
	}

	//NOT Stable sort
	void QuickSortLR_t2(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSortLR_t2(obj, 0, size - 1);
	}

	// Quick Sort LR - Trial Version 3 - TCO of Trial Version 2
	// Single pivot - End element as pivot
	// This is same as above except, Tail Call Optimization (TCO) is done for longer range
	//=======================================================================================

	void QuickSortLR_t3TCO(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int start = startIndex;
		int end = endIndex - 1;
		const int pivot = endIndex;

		int partitionIndex = pivot;
		while (true)
		{
			//while (start <= end && obj[start] <= obj[pivot])
			while (start <= end && !(obj[pivot] < obj[start])) //Above condition is replaced by this to reduce number of comparisons
				start++;
			while (start <= end && obj[pivot] < obj[end])
				partitionIndex = end--;

			if (start < end)
			{
				obj[start].swap(obj[end]);
				start++;
				partitionIndex = end--;
			}
			else
				break;
		}

		if (partitionIndex != pivot)
			obj[partitionIndex].swap(obj[pivot]);

		//To ensure that recursive call takes max O(log n) space, recurse over shorter range
		int lengthFirstRange = partitionIndex - startIndex;
		int lengthSecondRange = endIndex - partitionIndex;

		int shortRangeStart, shortRangeEnd, LongRangeStart, LongRangeEnd;
		if (lengthFirstRange < lengthSecondRange)
		{
			shortRangeStart = startIndex;
			shortRangeEnd = partitionIndex - 1;
			LongRangeStart = partitionIndex + 1;
			LongRangeEnd = endIndex;
		}
		else
		{
			LongRangeStart = startIndex;
			LongRangeEnd = partitionIndex - 1;
			shortRangeStart = partitionIndex + 1;
			shortRangeEnd = endIndex;
		}

		QuickSortLR_t3TCO(obj, shortRangeStart, shortRangeEnd);
		//This call will be used for tail recursion optimization, so use it for longer range
		QuickSortLR_t3TCO(obj, LongRangeStart, LongRangeEnd);
	}

	//NOT Stable sort
	//Tail recursive call optimization
	void QuickSortLR_t3TCO(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSortLR_t3TCO(obj, 0, size - 1);
	}


	//=======================+===============+
	//                       | Quick Sort LL |
	//=======================+===============+

	// Quick Sort LL - Trial Version 1
	// Single pivot - End element as pivot
	// This algorithm uses two LEFT pointers, but not the RIGHT pointer
	//=======================================================================================

	void QuickSortLL_t1(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int partitionIndex = startIndex;
		int pivotIndex = endIndex;
		for (int i = startIndex; i < endIndex; i++)
		{
			//This is equivalent to dividing values in array in 2 groups such that all object 
			//smaller than a pivot are at left, and greater than or equal to pivot are at right
			if (obj[i] < obj[pivotIndex])  //endIndex is index of pivot
			{
				if (partitionIndex != i)
					obj[partitionIndex].swap(obj[i]);
				++partitionIndex;
			}
		}
		if (partitionIndex != pivotIndex)
			obj[partitionIndex].swap(obj[pivotIndex]);

		QuickSortLL_t1(obj, startIndex, partitionIndex - 1);
		QuickSortLL_t1(obj, partitionIndex + 1, endIndex);
	}

	//NOT Stable sort
	void QuickSortLL_t1(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSortLL_t1(obj, 0, size - 1);
	}

	// Quick Sort LL - Trial Version 2
	// Single pivot - End element as pivot
	// This algorithm uses two LEFT pointers, but not the RIGHT pointer
	// This is same as above except, tail call optimization is done for longer range
	//=======================================================================================

	void QuickSortLL_t2TCO(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int partitionIndex = startIndex;
		int pivotIndex = endIndex;
		for (int i = startIndex; i < endIndex; i++)
		{
			//This is equivalent to dividing values in array in 2 groups such that all object 
			//smaller than a pivot are at left, and greater than or equal to pivot are at right
			if (obj[i] < obj[pivotIndex])  //endIndex is index of pivot
			{
				if (partitionIndex != i)
					obj[partitionIndex].swap(obj[i]);
				++partitionIndex;
			}
		}
		if (partitionIndex != pivotIndex)
			obj[partitionIndex].swap(obj[pivotIndex]);

		//To ensure that recursive call takes max O(log n) space, recurse over shorter range
		int lengthFirstRange = partitionIndex - startIndex;
		int lengthSecondRange = endIndex - partitionIndex;

		int shortRangeStart, shortRangeEnd, LongRangeStart, LongRangeEnd;
		if (lengthFirstRange < lengthSecondRange)
		{
			shortRangeStart = startIndex;
			shortRangeEnd = partitionIndex - 1;
			LongRangeStart = partitionIndex + 1;
			LongRangeEnd = endIndex;
		}
		else
		{
			LongRangeStart = startIndex;
			LongRangeEnd = partitionIndex - 1;
			shortRangeStart = partitionIndex + 1;
			shortRangeEnd = endIndex;
		}

		QuickSortLL_t2TCO(obj, shortRangeStart, shortRangeEnd);
		//This call will be used for tail recursion optimization, so use it for longer range
		QuickSortLL_t2TCO(obj, LongRangeStart, LongRangeEnd);
	}

	//NOT Stable sort
	//Tail recursive call optimization
	void QuickSortLL_t2TCO(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSortLL_t2TCO(obj, 0, size - 1);
	}

	//=======================+==========================================+
	//                       | 3 Way Quick Sort  OR  Ternary Quick Sort |
	//=======================+==========================================+

	// Quick Sort 3 Way - Trial Version 1
	//=======================================================================================

	// NOT Stable sort
	// Single pivot - End element as pivot
	// Divides array into 3 parts, < Pivot, == Pivot and > Pivot
	void makeUnstable3WayPartitionLR_1(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall)
	{
		const int pivot = endIndex;
		leftWall = startIndex;
		rightWall = endIndex - 1;
		int current = leftWall;
		while (current <= rightWall)
		{
			if (obj[current] < obj[pivot])
			{
				if (leftWall != current)
					obj[leftWall].swap(obj[current]);
				++leftWall;
				++current;
			}
			else if (obj[pivot] < obj[current])
			{
				if (rightWall != current)
					obj[rightWall].swap(obj[current]);
				--rightWall;
			}
			else
				++current;
		}

		--leftWall;
		++rightWall;

		if (rightWall < pivot)
		{
			obj[pivot].swap(obj[rightWall]);
			++rightWall;
		}
	}

	void QuickSort3WayLR_1(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int leftWall, rightWall;
		makeUnstable3WayPartitionLR_1(obj, startIndex, endIndex, leftWall, rightWall);
		QuickSort3WayLR_1(obj, startIndex, leftWall);
		QuickSort3WayLR_1(obj, rightWall, endIndex);
	}

	void QuickSort3WayLR_1(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSort3WayLR_1(obj, 0, size - 1);
	}

	// Quick Sort 3 Way - 2
	//=======================================================================================

	// NOT Stable sort
	// This uses Dutch National Flag Algorithm
	void makeUnstable3WayPartitionLR_2(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall)
	{
		const Object pivotObj = obj[endIndex];
		leftWall = startIndex;
		rightWall = endIndex;
		int current = leftWall;
		while (current <= rightWall)
		{
			if (obj[current] < pivotObj)
			{
				if (leftWall != current)
					obj[leftWall].swap(obj[current]);
				++leftWall;
				++current;
			}
			else if (pivotObj < obj[current])
			{
				if (rightWall != current)
					obj[rightWall].swap(obj[current]);
				--rightWall;
			}
			else
				++current;
		}

		--leftWall;
		++rightWall;
	}

	void QuickSort3WayLR_t2(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int leftWall, rightWall;
		makeUnstable3WayPartitionLR_2(obj, startIndex, endIndex, leftWall, rightWall);
		QuickSort3WayLR_t2(obj, startIndex, leftWall);
		QuickSort3WayLR_t2(obj, rightWall, endIndex);
	}

	void QuickSort3WayLR_t2(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSort3WayLR_t2(obj, 0, size - 1);
	}

	// Quick Sort 3 Way - 3
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartitionLR_3(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall)
	{
		const Object pivotObj = obj[endIndex];
		leftWall = startIndex;
		rightWall = endIndex;
		int currentLeft = leftWall;
		int currentRight = rightWall;
		bool leftEndSmooth = true;
		bool rightEndSmooth = true;
		while (currentLeft <= rightWall || currentRight >= leftWall)
		{
			while (leftEndSmooth && (obj[leftWall] < pivotObj)) ++leftWall;
			while (rightEndSmooth && (pivotObj < obj[rightWall])) --rightWall;
			if (leftWall >= rightWall) break;

			if (currentLeft < leftWall) currentLeft = leftWall;
			if (currentRight > rightWall) currentRight = rightWall;

			bool leftBigger = (leftEndSmooth && (pivotObj < obj[leftWall]));
			bool rightSmaller = (rightEndSmooth && (obj[rightWall] < pivotObj));

			leftEndSmooth = false;
			rightEndSmooth = false;
			if (leftBigger && rightSmaller)
			{
				obj[leftWall].swap(obj[rightWall]);
				leftWall++;
				rightWall--;
				leftEndSmooth = true;
				rightEndSmooth = true;
			}
			else if (leftBigger)
			{
				const Object temp = obj[rightWall];
				obj[rightWall] = obj[leftWall];
				rightWall--;
				rightEndSmooth = true;
				bool found = false;
				while (currentRight > leftWall)
					if (obj[--currentRight] < pivotObj)
					{
						obj[leftWall] = obj[currentRight];
						obj[currentRight] = temp;
						leftWall++;
						leftEndSmooth = true;
						found = true;
						break;
					}
				if (!found)
					obj[leftWall] = temp;
			}
			else if (rightSmaller)
			{
				const Object temp = obj[leftWall];
				obj[leftWall] = obj[rightWall];
				leftWall++;
				leftEndSmooth = true;
				bool found = false;
				while (currentLeft < rightWall)
					if (pivotObj < obj[++currentLeft])
					{
						obj[rightWall] = obj[currentLeft];
						obj[currentLeft] = temp;
						rightWall--;
						rightEndSmooth = true;
						found = true;
						break;
					}
				if (!found)
					obj[rightWall] = temp;
			}
			else
			{
				bool found1 = false;
				bool found2 = false;
				while (currentRight > leftWall)
					if (obj[--currentRight] < pivotObj)
					{
						obj[currentRight].swap(obj[leftWall]);
						leftWall++;
						leftEndSmooth = true;
						found1 = true;
						break;
					}
				while (currentLeft < rightWall)
					if (pivotObj < obj[++currentLeft])
					{
						obj[currentLeft].swap(obj[rightWall]);
						rightWall--;
						rightEndSmooth = true;
						found2 = true;
						break;
					}
				if (!found1 && !found2)
					break;
			}
		}

		--leftWall;
		++rightWall;
	}

	void QuickSort3WayLR_t3(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int leftWall, rightWall;
		makeUnstable3WayPartitionLR_3(obj, startIndex, endIndex, leftWall, rightWall);
		QuickSort3WayLR_t3(obj, startIndex, leftWall);
		QuickSort3WayLR_t3(obj, rightWall, endIndex);
	}

	void QuickSort3WayLR_t3(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSort3WayLR_t3(obj, 0, size - 1);
	}

	// Quick Sort 3 Way - 4
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartitionLR_3Simplified(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall)
	{
		const Object pivotObj = obj[endIndex];
		leftWall = startIndex;
		rightWall = endIndex;
		int currentLeft = leftWall;
		int currentRight = rightWall;

		//Collect smaller elements at left
		while (true)
		{
			while (obj[leftWall] < pivotObj) ++leftWall;
			bool found = false;
			while (leftWall < currentRight)
			{
				if (obj[currentRight] < pivotObj)
				{
					obj[leftWall].swap(obj[currentRight]);
					++leftWall;
					--currentRight;
					found = true;
					break;
				}
				--currentRight;
			}
			if (!found)
				break;
		}

		//Collect larger elements at right
		currentLeft = leftWall;
		while (true)
		{
			while ((pivotObj < obj[rightWall])) --rightWall;
			bool found = false;
			while (currentLeft < rightWall)
			{
				if (pivotObj < obj[currentLeft])
				{
					obj[rightWall].swap(obj[currentLeft]);
					--rightWall;
					++currentLeft;
					found = true;
					break;
				}
				++currentLeft;
			}
			if (!found)
				break;
		}

		--leftWall;
		++rightWall;
	}

	void QuickSort3WayLR_t4(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int leftWall, rightWall;
		makeUnstable3WayPartitionLR_3Simplified(obj, startIndex, endIndex, leftWall, rightWall);
		QuickSort3WayLR_t4(obj, startIndex, leftWall);
		QuickSort3WayLR_t4(obj, rightWall, endIndex);
	}

	void QuickSort3WayLR_t4(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSort3WayLR_t4(obj, 0, size - 1);
	}

	// Quick Sort 3 Way - 5
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartitionLR_3Simplified2(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall)
	{
		const Object pivotObj = obj[endIndex];
		leftWall = startIndex;
		rightWall = endIndex;
		int currentLeft = leftWall;
		int currentRight = rightWall;

		//Collect larger elements at right
		while (true)
		{
			while (pivotObj < obj[rightWall]) --rightWall;
			bool found = false;
			while (currentLeft < rightWall)
			{
				if (pivotObj < obj[currentLeft])
				{
					obj[rightWall].swap(obj[currentLeft]);
					--rightWall;
					++currentLeft;
					found = true;
					break;
				}
				++currentLeft;
			}
			if (!found)
				break;
		}

		//Collect smaller elements at left
		currentRight = rightWall;
		while (true)
		{
			while (obj[leftWall] < pivotObj) ++leftWall;
			bool found = false;
			while (leftWall < currentRight)
			{
				if (obj[currentRight] < pivotObj)
				{
					obj[leftWall].swap(obj[currentRight]);
					++leftWall;
					--currentRight;
					found = true;
					break;
				}
				--currentRight;
			}
			if (!found)
				break;
		}

		--leftWall;
		++rightWall;
	}

	void QuickSort3WayLR_t5(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int leftWall, rightWall;
		makeUnstable3WayPartitionLR_3Simplified2(obj, startIndex, endIndex, leftWall, rightWall);
		QuickSort3WayLR_t5(obj, startIndex, leftWall);
		QuickSort3WayLR_t5(obj, rightWall, endIndex);
	}

	void QuickSort3WayLR_t5(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSort3WayLR_t5(obj, 0, size - 1);
	}


	// Quick Sort 3 Way - 6
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartitionLR_3Simplified3(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall)
	{
		const Object pivotObj = obj[endIndex];
		leftWall = startIndex;
		rightWall = endIndex;
		int currentLeft = leftWall;
		int currentRight = rightWall;

		while (true)
		{
			while (obj[leftWall] < pivotObj) ++leftWall;
			while (pivotObj < obj[rightWall]) --rightWall;

			if (leftWall >= rightWall) break;

			bool leftBigger = (pivotObj < obj[leftWall]);
			bool rightSmaller = (obj[rightWall] < pivotObj);

			if (leftBigger && rightSmaller)
			{
				obj[leftWall].swap(obj[rightWall]);
				leftWall++;
				rightWall--;
			}
			else if (leftBigger)
			{
				obj[leftWall].swap(obj[rightWall]);
				rightWall--;
			}
			else if (rightSmaller)
			{
				obj[leftWall].swap(obj[rightWall]);
				leftWall++;
			}
			else
			{
				if (currentRight > rightWall) currentRight = rightWall;
				bool found1 = false;
				while (leftWall < currentRight)
				{
					if (obj[currentRight] < pivotObj)
					{
						obj[leftWall].swap(obj[currentRight]);
						++leftWall;
						--currentRight;
						found1 = true;
						break;
					}
					--currentRight;
				}

				if (currentLeft < leftWall) currentLeft = leftWall;
				bool found2 = false;
				while (currentLeft < rightWall)
				{
					if (pivotObj < obj[currentLeft])
					{
						obj[rightWall].swap(obj[currentLeft]);
						--rightWall;
						++currentLeft;
						found2 = true;
						break;
					}
					++currentLeft;
				}

				if (!found1 && !found2)
					break;
			}
		}

		--leftWall;
		++rightWall;
	}

	void QuickSort3WayLR_t6(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int leftWall, rightWall;
		makeUnstable3WayPartitionLR_3Simplified3(obj, startIndex, endIndex, leftWall, rightWall);
		QuickSort3WayLR_t6(obj, startIndex, leftWall);
		QuickSort3WayLR_t6(obj, rightWall, endIndex);
	}

	void QuickSort3WayLR_t6(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSort3WayLR_t6(obj, 0, size - 1);
	}

	// Quick Sort 3 Way - 7
	//=======================================================================================

	// NOT Stable sort
	// This is slightly better version than above
	void makeUnstable3WayPartition4(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall)
	{
		//const Object pivotObj = obj[endIndex];
		const int pivotIndex = endIndex;
		leftWall = startIndex;
		rightWall = endIndex - 1;
		int currentLeft = leftWall;
		int currentRight = rightWall;
		bool leftEndSmooth = true;
		bool rightEndSmooth = true;
		while (currentLeft <= rightWall || currentRight >= leftWall)
		{
			while (leftEndSmooth && (obj[leftWall] < obj[pivotIndex])) ++leftWall;
			while (rightEndSmooth && rightWall >= 0 && (obj[pivotIndex] < obj[rightWall])) --rightWall;
			if (leftWall >= rightWall) break;

			if (currentLeft < leftWall) currentLeft = leftWall;
			if (currentRight > rightWall) currentRight = rightWall;

			bool leftBigger = (leftEndSmooth && (obj[pivotIndex] < obj[leftWall]));
			bool rightSmaller = (rightEndSmooth && (obj[rightWall] < obj[pivotIndex]));

			leftEndSmooth = false;
			rightEndSmooth = false;
			if (leftBigger && rightSmaller)
			{
				obj[leftWall].swap(obj[rightWall]);
				leftWall++;
				rightWall--;
				leftEndSmooth = true;
				rightEndSmooth = true;
			}
			else if (leftBigger)
			{
				const Object temp = obj[rightWall];
				obj[rightWall] = obj[leftWall];
				rightWall--;
				rightEndSmooth = true;
				bool found = false;
				while (currentRight > leftWall)
					if (obj[--currentRight] < obj[pivotIndex])
					{
						obj[leftWall] = obj[currentRight];
						obj[currentRight] = temp;
						leftWall++;
						leftEndSmooth = true;
						found = true;
						break;
					}
				if (!found)
					obj[leftWall] = temp;
			}
			else if (rightSmaller)
			{
				const Object temp = obj[leftWall];
				obj[leftWall] = obj[rightWall];
				leftWall++;
				leftEndSmooth = true;
				bool found = false;
				while (currentLeft < rightWall)
					if (obj[pivotIndex] < obj[++currentLeft])
					{
						obj[rightWall] = obj[currentLeft];
						obj[currentLeft] = temp;
						rightWall--;
						rightEndSmooth = true;
						found = true;
						break;
					}
				if (!found)
					obj[rightWall] = temp;
			}
			else
			{
				bool found1 = false;
				bool found2 = false;
				while (currentRight > leftWall)
					if (obj[--currentRight] < obj[pivotIndex])
					{
						obj[currentRight].swap(obj[leftWall]);
						leftWall++;
						leftEndSmooth = true;
						found1 = true;
						break;
					}
				while (currentLeft < rightWall)
					if (obj[pivotIndex] < obj[++currentLeft])
					{
						obj[currentLeft].swap(obj[rightWall]);
						rightWall--;
						rightEndSmooth = true;
						found2 = true;
						break;
					}
				if (!found1 && !found2)
					break;
			}
		}

		--leftWall;
		++rightWall;

		if (rightWall < pivotIndex)
		{
			obj[pivotIndex].swap(obj[rightWall]);
			++rightWall;
		}
	}

	void QuickSort3WayLR_t7(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int leftWall, rightWall;
		makeUnstable3WayPartition4(obj, startIndex, endIndex, leftWall, rightWall);
		QuickSort3WayLR_t7(obj, startIndex, leftWall);
		QuickSort3WayLR_t7(obj, rightWall, endIndex);
	}

	void QuickSort3WayLR_t7(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSort3WayLR_t7(obj, 0, size - 1);
	}





	//=======================+=======================+
	//                       | Dual Pivot Quick Sort |
	//=======================+=======================+

	// Quick Sort Dual Pivot - 1
	//=======================================================================================

	// NOT Stable sort
	// Dual Pivot - uses Leftmost and Rightmost elements as pivots
	void makeUnstableDualPivotPartition_1(DataSet& obj, int startIndex, int endIndex, int& leftWall, int& rightWall)
	{
		//const Object pivotObj = obj[endIndex];
		const int leftPivotIndex = startIndex;
		const int rightPivotIndex = endIndex;

		if (obj[rightPivotIndex] < obj[leftPivotIndex])
			obj[rightPivotIndex].swap(obj[leftPivotIndex]);

		leftWall = startIndex + 1;
		rightWall = endIndex - 1;

		for (int current = leftWall; current <= rightWall;)
		{
			if (obj[current] < obj[leftPivotIndex])
			{
				if (current != leftWall)
					obj[current].swap(obj[leftWall]);
				leftWall++;
				current++;
			}
			else if (obj[rightPivotIndex] < obj[current])
			{
				if (current != rightWall)
					obj[current].swap(obj[rightWall]);
				rightWall--;
			}
			else
				current++;
		}
		--leftWall;
		++rightWall;

		if (leftPivotIndex != leftWall)
			obj[leftPivotIndex].swap(obj[leftWall]);
		if (rightPivotIndex != rightWall)
			obj[rightPivotIndex].swap(obj[rightWall]);
	}

	void QuickSortDualPivot_1(DataSet& obj, int startIndex, int endIndex)
	{
		if (startIndex >= endIndex)
			return;

		int leftWall, rightWall;
		makeUnstableDualPivotPartition_1(obj, startIndex, endIndex, leftWall, rightWall);
		QuickSortDualPivot_1(obj, startIndex, leftWall - 1);
		QuickSortDualPivot_1(obj, leftWall + 1, rightWall - 1);
		QuickSortDualPivot_1(obj, rightWall + 1, endIndex);
	}

	void QuickSortDualPivot_1(DataSet& obj)
	{
		int size = obj.getSize();
		QuickSortDualPivot_1(obj, 0, size - 1);
	}


	//=======================+========================+
	//                       | Multi Pivot Quick Sort |
	//=======================+========================+

	// Multi Pivot Quick Sort - 1
	//=======================================================================================

	void QuickSortMultiPivot_2Pivots(DataSet& obj);

	//NOT Stable sort
	void makeUnstableMultiPivotPartition1(DataSet& obj, int startIndex, int endIndex, vector<int>& walls, int numberOfPivots)
	{
		vector<int> PivotIndices;
		//Choose appropriate number of pivotes. We will choose at least 2 pivots
		while (numberOfPivots > 0)
		{
			if ((endIndex - startIndex + 1) >= numberOfPivots)
			{
				PivotIndices.resize(numberOfPivots);
				//Set start and end index as first and last pivot
				PivotIndices[0] = startIndex;
				PivotIndices[numberOfPivots - 1] = endIndex;
				//Build middle pivots
				for (int i = 1; i < numberOfPivots - 1; i++)
					PivotIndices[i] = startIndex + (endIndex - startIndex) / (numberOfPivots - 1);
				break;
			}
			else
				numberOfPivots -= 1;
		}

		//Sort the pivots
		if (numberOfPivots == 1)
		{
			//Ignore
		}
		else if (numberOfPivots == 2)
		{
			if (obj[PivotIndices[1]] < obj[PivotIndices[0]])
				obj[PivotIndices[1]].swap(obj[PivotIndices[0]]);
		}
		else
		{
			DataSet set("Temp", static_cast<unsigned int>(PivotIndices.size()));
			for (unsigned int i = 0; i < PivotIndices.size(); i++)
				set[i] = obj[PivotIndices[i]];

			QuickSortMultiPivot_2Pivots(set);
			for (unsigned int i = 0; i < PivotIndices.size(); i++)
				obj[PivotIndices[i]] = set[i];
		}

		int numberOfWalls = numberOfPivots;
		if (numberOfPivots == 1) numberOfWalls = 2;
		walls.resize(numberOfWalls);
		int leftWall = startIndex;
		int rightWall = endIndex;
		int numberOfLoops = numberOfPivots / 2;
		if (numberOfPivots % 2 == 1)
			numberOfLoops++;
		for (int i = 0; i < numberOfLoops; i++)
		{
			//const int leftPivotIndex = PivotIndices[i];
			//const int rightPivotIndex = PivotIndices[numberOfPivots - i - 1];
			const Object leftPivotObj = obj[PivotIndices[i]];
			const Object rightPivotObj = obj[PivotIndices[numberOfPivots - i - 1]];

			for (int current = leftWall; current <= rightWall;)
			{
				if (obj[current] < leftPivotObj)
				{
					if (current != leftWall)
						obj[current].swap(obj[leftWall]);
					leftWall++;
					current++;
				}
				else if (rightPivotObj < obj[current])
				{
					if (current != rightWall)
						obj[current].swap(obj[rightWall]);
					rightWall--;
				}
				else
					current++;
			}

			if (leftWall > startIndex)
				--leftWall;
			if (rightWall < endIndex)
				++rightWall;
			walls[i] = leftWall;
			walls[numberOfWalls - i - 1] = rightWall;

			//if (leftPivotIndex != leftWall)
			//	obj[leftPivotIndex].swap(obj[leftWall]);
			//if (numberOfPivots > 1 && rightPivotIndex != rightWall)
			//	obj[rightPivotIndex].swap(obj[rightWall]);

			leftWall = leftWall + 1;
			rightWall = rightWall - 1;
		}
	}

	void QuickSortMultiPivot(DataSet& obj, int startIndex, int endIndex, int numberOfPivots)
	{
		if (startIndex >= endIndex)
			return;

		vector<int> walls;
		makeUnstableMultiPivotPartition1(obj, startIndex, endIndex, walls, numberOfPivots);

		int numberOfWalls = static_cast<int>(walls.size());

		int i = 0;
		for (; i < numberOfWalls / 2; i++)
		{
			QuickSortMultiPivot(obj, startIndex, walls[i], numberOfPivots);
			QuickSortMultiPivot(obj, walls[numberOfWalls - i - 1], endIndex, numberOfPivots);
			startIndex = walls[i] + 1;
			endIndex = walls[numberOfWalls - i - 1] - 1;
		}
		--i;
		QuickSortMultiPivot(obj, walls[i] + 1, walls[numberOfWalls - i - 1] - 1, numberOfPivots);
	}

	void QuickSortMultiPivot(DataSet& obj, const int numberOfPivots)
	{
		int size = obj.getSize();
		QuickSortMultiPivot(obj, 0, size - 1, numberOfPivots);
	}

	void QuickSortMultiPivot_1Pivots(DataSet& obj)
	{
		int numberOfPivots = 1;
		QuickSortMultiPivot(obj, numberOfPivots);
	}

	void QuickSortMultiPivot_2Pivots(DataSet& obj)
	{
		int numberOfPivots = 2;
		QuickSortMultiPivot(obj, numberOfPivots);
	}

	void QuickSortMultiPivot_3Pivots(DataSet& obj)
	{
		int numberOfPivots = 3;
		QuickSortMultiPivot(obj, numberOfPivots);
	}

	void QuickSortMultiPivot_4Pivots(DataSet& obj)
	{
		int numberOfPivots = 4;
		QuickSortMultiPivot(obj, numberOfPivots);
	}

	void QuickSortMultiPivot_5Pivots(DataSet& obj)
	{
		int numberOfPivots = 5;
		QuickSortMultiPivot(obj, numberOfPivots);
	}

	void QuickSortMultiPivot_6Pivots(DataSet& obj)
	{
		int numberOfPivots = 6;
		QuickSortMultiPivot(obj, numberOfPivots);
	}


	// Multi Pivot Quick Sort - 2 - reuse existing dual pivot algorithm
	//=======================================================================================

	//If we call dual pivot algorithm for the extreme end pivot pairs sequencially, it is as good as using dual pivot algorithm. So no need to try this.


	//=======================+======================================+
	//                       | R-Quick Sort OR Iterative Quick Sort |
	//=======================+======================================+

	int makeUnstablePartition(DataSet& obj, int startIndex, int endIndex)
	{
		int separatingWall = startIndex;
		int pivotIndex = endIndex;
		for (int i = startIndex; i < endIndex; i++)
		{
			//This is equivalent to dividing values in array in 2 groups such that all object 
			//smaller than a pivot are at left, and greater than or equal to pivot are at right
			if (obj[i] < obj[pivotIndex])  //endIndex is index of pivot
			{
				if (separatingWall != i)
					obj[separatingWall].swap(obj[i]);
				++separatingWall;
			}
		}
		if (separatingWall != pivotIndex)
			obj[separatingWall].swap(obj[pivotIndex]);
		return separatingWall;
	}

	void QuickSortIterative(DataSet& obj)
	{
		struct pairOfBounds
		{
			pairOfBounds(int l, int r)
				:left(l), right(r)
			{}
			int left, right;
		};

		int size = obj.getSize();
		//Use vector as stack
		vector<pairOfBounds> stack;
		stack.push_back(pairOfBounds(0, size - 1));

		while (!stack.empty())
		{
			pairOfBounds pair = stack.back();
			stack.pop_back();

			//Reuse any old partitioning method
			int partition = makeUnstablePartition(obj, pair.left, pair.right);
			if (pair.left < (partition - 1))
				stack.push_back(pairOfBounds(pair.left, partition - 1));
			if ((partition + 1) < pair.right)
				stack.push_back(pairOfBounds(partition + 1, pair.right));
		}
	}

}