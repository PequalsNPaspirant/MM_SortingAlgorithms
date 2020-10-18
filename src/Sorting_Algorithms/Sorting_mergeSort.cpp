#include <queue>

#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_mergeSort.h"

namespace mm {


	//=======================+============+
	//                       | Merge Sort |
	//=======================+============+
	//This is stable sort

	// MergeSort - TopDownMerge 1 - space complexity O(n)
	//=======================================================================================

	void TopDownMerge1(DataSet& firstSet, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end, DataSet& secondSet)
	{
		size_t counterFirstSet = firstSetStart;
		size_t counterSecondSet = secondSetStart;
		for (size_t k = firstSetStart; k <= end; k++)
		{
			bool firstSetOver = counterFirstSet > secondSetStart - 1;
			bool secondSetOver = counterSecondSet > end;
			//if (secondSetOver || (!firstSetOver && secondSet[CounterFirstSet] < secondSet[CounterSecondSet])) //This condition loses stability
			if (secondSetOver || (!firstSetOver && !(secondSet[counterSecondSet] < secondSet[counterFirstSet]))) //equivalent to secondSet[CounterFirstSet] <= secondSet[CounterSecondSet]
				firstSet[k] = secondSet[counterFirstSet++];
			else
				firstSet[k] = secondSet[counterSecondSet++];
		}
	}

	void TopDownSplit1(DataSet& firstSet, int start, int end, DataSet& secondSet)
	{
		if (start == end)
			return;

		int firstSetEnd = std::trunc((start + end) / 2.0);
		TopDownSplit1(secondSet, start, firstSetEnd, firstSet);
		int secondSetStart = firstSetEnd + 1;
		TopDownSplit1(secondSet, secondSetStart, end, firstSet);

		TopDownMerge1(firstSet, start, secondSetStart, end, secondSet);
	}

	void MergeSortTopDown1(DataSet& obj)
	{
		int size = obj.getSize();
		DataSet copy(obj.getCopy());
		TopDownSplit1(obj, 0, size - 1, copy);
	}

	// MergeSort - TopDownMerge 2 - space complexity O(n/2)
	//We can avoid toggling of arrays here, so algorithm is cleaner
	//=======================================================================================

	void TopDownMerge2(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//No need to check smaller size set because both sets are of same size
		//Create a copy of first set
		DataSet copy(obj.getCopy(firstSetStart, secondSetStart - 1));

		size_t CounterFirstSet = 0;
		size_t CounterSecondSet = secondSetStart;
		for (size_t k = firstSetStart; k <= end; k++)
		{
			bool firstSetOver = CounterFirstSet >= copy.getSize();
			bool secondSetOver = CounterSecondSet > end;
			if (firstSetOver)
				break;
			if (!secondSetOver && obj[CounterSecondSet] < copy[CounterFirstSet]) //This condition DOES NOT lose stability
				obj[k] = obj[CounterSecondSet++];
			else
				obj[k] = copy[CounterFirstSet++];
		}
	}

	void TopDownSplit2(DataSet& obj, int start, int end)
	{
		if (start == end)
			return;

		int firstSetEnd = std::trunc((start + end) / 2.0);
		TopDownSplit2(obj, start, firstSetEnd);
		int secondSetStart = firstSetEnd + 1;
		TopDownSplit2(obj, secondSetStart, end);

		TopDownMerge2(obj, start, secondSetStart, end);
	}

	void MergeSortTopDown2(DataSet& obj)
	{
		int size = obj.getSize();
		TopDownSplit2(obj, 0, size - 1);
	}

	// MergeSort - TopDownMerge 3 - space complexity O(n/2)
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge3(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//No need to check smaller size set because both sets are ALMOST of same size. 
		//(In case of odd number of elements in set, two set can differ in size by one)
		//Create a copy of first set
		DataSet copy(obj.getCopy(firstSetStart, secondSetStart - 1));

		size_t counterFirstSet = 0;
		size_t counterSecondSet = secondSetStart;
		for (size_t k = firstSetStart; k <= end; k++)
		{
			bool firstSetOver = counterFirstSet >= copy.getSize();
			bool secondSetOver = counterSecondSet > end;
			if (firstSetOver)
				break;
			if (!secondSetOver && obj[counterSecondSet] < copy[counterFirstSet]) //This condition DOES NOT lose stability
			{
				if (k != counterSecondSet)
					obj[k] = obj[counterSecondSet];
				counterSecondSet++;
			}
			else
			{
				if (k != (counterFirstSet + firstSetStart))
					obj[k] = copy[counterFirstSet];
				counterFirstSet++;
			}
		}
	}

	void TopDownSplit3(DataSet& obj, int start, int end)
	{
		if (start == end)
			return;

		int firstSetEnd = std::trunc((start + end) / 2.0);
		TopDownSplit3(obj, start, firstSetEnd);
		int secondSetStart = firstSetEnd + 1;
		TopDownSplit3(obj, secondSetStart, end);

		TopDownMerge3(obj, start, secondSetStart, end);
	}

	void MergeSortTopDown3(DataSet& obj)
	{
		int size = obj.getSize();
		TopDownSplit3(obj, 0, size - 1);
	}

	// MergeSort - TopDownMerge 4 - Average space complexity LESS THAN O(n/2). MAX space complexity O(n/2).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge4(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//No need to check smaller size set because both sets are ALMOST of same size. 
		//(In case of odd number of elements in set, two set can differ in size by one)
		//Create a queue to keep the objects tempororily aside
		std::queue<Object> qObj;

		size_t counterSecondSet = secondSetStart;
		for (size_t k = firstSetStart; k <= end; k++)
		{
			bool firstSetOver = k > secondSetStart - 1;
			bool secondSetOver = counterSecondSet > end;
			if (firstSetOver && qObj.empty())
				break;
			if (!secondSetOver
				&& ((qObj.empty() && obj[counterSecondSet] < obj[k])
					|| (!qObj.empty() && obj[counterSecondSet] < qObj.front()))
				) //This condition DOES NOT lose stability
			{
				//backup object of first set into queue
				if (!firstSetOver)
					qObj.push(obj[k]);
				obj[k] = obj[counterSecondSet++];
			}
			else
			{
				if (!qObj.empty())
				{
					//backup object of first set into queue
					if (!firstSetOver)
						qObj.push(obj[k]);
					obj[k] = qObj.front();
					qObj.pop();
				}
			}
		}
	}

	void TopDownSplit4(DataSet& obj, int start, int end)
	{
		if (start == end)
			return;

		int firstSetEnd = std::trunc((start + end) / 2.0);
		TopDownSplit4(obj, start, firstSetEnd);
		int secondSetStart = firstSetEnd + 1;
		TopDownSplit4(obj, secondSetStart, end);

		TopDownMerge4(obj, start, secondSetStart, end);
	}

	void MergeSortTopDown4(DataSet& obj)
	{
		int size = obj.getSize();
		TopDownSplit4(obj, 0, size - 1);
	}

	// MergeSort - TopDownMerge 5 - Space complexity O(1).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge5(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//No need to check smaller size set because both sets are ALMOST of same size. 
		//(In case of odd number of elements in set, two set can differ in size by one)

		int findRangeStart = firstSetStart;
		for (size_t k = secondSetStart; k <= end; k++)
		{
			int findRangeEnd = k - 1;
			int position;
			if (!(obj[k] < obj[findRangeEnd])) //i.e. obj[findRangeEnd] <= obj[k]
				break;
			else if (obj[k] < obj[findRangeStart])
				position = findRangeStart;
			else
			{
				int start = findRangeStart;
				int end = findRangeEnd;
				while (end - start > 1)
				{
					int mid = (start + end) / 2;
					if (obj[k] < obj[mid])
						end = mid;
					else
						start = mid;
				}
				position = end;
			}

			Object temp = obj[k];
			for (int i = k; i > position; i--)
				obj[i] = obj[i - 1];
			obj[position] = temp;

			findRangeStart = position + 1;
		}
	}

	void TopDownSplit5(DataSet& obj, int start, int end)
	{
		if (start == end)
			return;

		int firstSetEnd = std::trunc((start + end) / 2.0);
		TopDownSplit5(obj, start, firstSetEnd);
		int secondSetStart = firstSetEnd + 1;
		TopDownSplit5(obj, secondSetStart, end);

		TopDownMerge5(obj, start, secondSetStart, end);
	}

	void MergeSortTopDown5(DataSet& obj)
	{
		int size = obj.getSize();
		TopDownSplit5(obj, 0, size - 1);
	}

	// MergeSort - TopDownMerge 6 - Space complexity O(1).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge6(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//No need to check smaller size set because both sets are ALMOST of same size. 
		//(In case of odd number of elements in set, two set can differ in size by one)

		int findRangeEnd = end;
		for (size_t k = secondSetStart - 1; k >= firstSetStart; k--)
		{
			int findRangeStart = k + 1;
			int position;
			if (!(obj[findRangeStart] < obj[k])) //i.e. obj[k] <= obj[findRangeEnd]
				break;
			else if (obj[findRangeEnd] < obj[k])
				position = findRangeEnd;
			else
			{
				int start = findRangeStart;
				int end = findRangeEnd;
				while (end - start > 1)
				{
					int mid = (start + end) / 2;

					//if (obj[k] < obj[mid])
					//	end = mid;
					//else
					//	start = mid;
					//Note the change in condition. Above condition produces unstable sort.
					if (obj[mid] < obj[k])
						start = mid;
					else
						end = mid;
				}
				position = start;
			}

			Object temp = obj[k];
			for (int i = k; i < position; i++)
				obj[i] = obj[i + 1];
			obj[position] = temp;

			findRangeEnd = position - 1;
		}
	}

	void TopDownSplit6(DataSet& obj, int start, int end)
	{
		if (start == end)
			return;

		int firstSetEnd = std::trunc((start + end) / 2.0);
		TopDownSplit6(obj, start, firstSetEnd);
		int secondSetStart = firstSetEnd + 1;
		TopDownSplit6(obj, secondSetStart, end);

		TopDownMerge6(obj, start, secondSetStart, end);
	}

	void MergeSortTopDown6(DataSet& obj)
	{
		int size = obj.getSize();
		TopDownSplit6(obj, 0, size - 1);
	}

	// MergeSort - TopDownMerge 7 - Space complexity O(1).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void TopDownMerge7(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//No need to check smaller size set because both sets are ALMOST of same size. 
		//(In case of odd number of elements in set, two set can differ in size by one)

		int firstSetSize = secondSetStart - firstSetStart;
		int secondSetSize = end - secondSetStart + 1;
		if (firstSetSize < secondSetSize)
		{
			int findRangeEnd = end;
			for (size_t k = secondSetStart - 1; k >= firstSetStart; k--)
			{
				int findRangeStart = k + 1;
				int position;
				if (!(obj[findRangeStart] < obj[k])) //i.e. obj[k] <= obj[findRangeEnd]
					break;
				else if (obj[findRangeEnd] < obj[k])
					position = findRangeEnd;
				else
				{
					int start = findRangeStart;
					int end = findRangeEnd;
					while (end - start > 1)
					{
						int mid = (start + end) / 2;

						//if (obj[k] < obj[mid])
						//	end = mid;
						//else
						//	start = mid;
						//Note the change in condition. Above condition produces unstable sort.
						if (obj[mid] < obj[k])
							start = mid;
						else
							end = mid;
					}
					position = start;
				}

				Object temp = obj[k];
				for (int i = k; i < position; i++)
					obj[i] = obj[i + 1];
				obj[position] = temp;

				findRangeEnd = position - 1;
			}
		}
		else
		{
			int findRangeStart = firstSetStart;
			for (size_t k = secondSetStart; k <= end; k++)
			{
				int findRangeEnd = k - 1;
				int position;
				if (!(obj[k] < obj[findRangeEnd])) //i.e. obj[findRangeEnd] <= obj[k]
					break;
				else if (obj[k] < obj[findRangeStart])
					position = findRangeStart;
				else
				{
					int start = findRangeStart;
					int end = findRangeEnd;
					while (end - start > 1)
					{
						int mid = (start + end) / 2;
						if (obj[k] < obj[mid])
							end = mid;
						else
							start = mid;
					}
					position = end;
				}

				Object temp = obj[k];
				for (int i = k; i > position; i--)
					obj[i] = obj[i - 1];
				obj[position] = temp;

				findRangeStart = position + 1;
			}
		}
	}

	void TopDownSplit7(DataSet& obj, int start, int end)
	{
		if (start == end)
			return;

		int firstSetEnd = std::trunc((start + end) / 2.0);
		TopDownSplit7(obj, start, firstSetEnd);
		int secondSetStart = firstSetEnd + 1;
		TopDownSplit7(obj, secondSetStart, end);

		TopDownMerge7(obj, start, secondSetStart, end);
	}

	void MergeSortTopDown7(DataSet& obj)
	{
		int size = obj.getSize();
		TopDownSplit7(obj, 0, size - 1);
	}


	// MergeSort - BottomUpMerge 1
	//=======================================================================================

	void BottomUpMerge1(DataSet& firstSet, const unsigned int start, const unsigned int middle, const unsigned int end, DataSet& secondSet)
	{
		//This is same as TopDownMerge
		TopDownMerge1(firstSet, start, middle, end, secondSet);
	}
	void BottomUpSplit1(DataSet& obj, int size, DataSet& copy)
	{
		/*
		size	No of Iterations
		1		0
		2		1
		3		2
		4		2
		5		3
		6		3
		7		3
		8		3
		9		4
		*/
		bool noToggle = int(ceil(log2(size))) % 2 != 0;
		for (int sizeOfSet = 1; sizeOfSet < size; sizeOfSet *= 2)
		{
			for (int firstSetStart = 0; firstSetStart < size; firstSetStart += (2 * sizeOfSet))
			{
				int secondSetStart = min(firstSetStart + sizeOfSet, size - 1);
				int end = min(secondSetStart + sizeOfSet - 1, size - 1);
				//Do not do merging again on last set if
				//		1. it contains only one element
				//		2. at end there is just one set left from previous iteration i.e. no second set present for merging 
				//Need to toggle array here, so can not add above optimization #2
				if (firstSetStart == end /*|| (end - firstSetStart + 1) <= sizeOfSet*/)
					continue;
				if (noToggle)
					BottomUpMerge1(obj, firstSetStart, secondSetStart, end, copy);
				else
					BottomUpMerge1(copy, firstSetStart, secondSetStart, end, obj);
			}
			noToggle = noToggle == false;
		}
	}

	void MergeSortBottomUp1(DataSet& obj)
	{
		int size = obj.getSize();
		DataSet copy(obj.getCopy());
		BottomUpSplit1(obj, size, copy);
	}

	// MergeSort - BottomUpMerge 2 - space complexity O(n/2)
	//=======================================================================================

	void BottomUpMerge2(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//NEED to check smaller size set because both sets are NOT of same size. Second set will be smaller in this case. 
		//(First set can never be smaller, but lets implement generic algo to handle both cases)
		int firstSetSize = secondSetStart - firstSetStart;
		int secondSetSize = end - secondSetStart + 1;
		if (firstSetSize < secondSetSize)
		{
			//Create a copy of first set
			DataSet copy(obj.getCopy(firstSetStart, secondSetStart - 1));
			size_t counterFirstSet = 0;
			size_t counterSecondSet = secondSetStart;
			for (size_t k = firstSetStart; k <= end; k++)
			{
				bool firstSetOver = counterFirstSet >= copy.getSize();
				bool secondSetOver = counterSecondSet > end;
				if (firstSetOver)
					break;
				if (!secondSetOver && obj[counterSecondSet] < copy[counterFirstSet]) //This condition DOES NOT lose stability
					obj[k] = obj[counterSecondSet++];
				else
					obj[k] = copy[counterFirstSet++];
			}
		}
		else
		{
			//Create a copy of second set
			DataSet copy(obj.getCopy(secondSetStart, end));
			//Need to begin from end
			size_t counterFirstSet = secondSetStart - 1;
			size_t counterSecondSet = copy.getSize() - 1;
			for (size_t k = end; k >= firstSetStart; k--)
			{
				bool firstSetOver = counterFirstSet < firstSetStart;
				bool secondSetOver = counterSecondSet < 0;
				if (secondSetOver)
					break;
				if (!firstSetOver && copy[counterSecondSet] < obj[counterFirstSet]) //This condition DOES NOT lose stability
					obj[k] = obj[counterFirstSet--];
				else
					obj[k] = copy[counterSecondSet--];
			}
		}
	}
	void BottomUpSplit2(DataSet& obj, int size)
	{
		for (int sizeOfSet = 1; sizeOfSet < size; sizeOfSet *= 2)
		{
			for (int firstSetStart = 0; firstSetStart < size; firstSetStart += (2 * sizeOfSet))
			{
				int secondSetStart = min(firstSetStart + sizeOfSet, size - 1);
				int end = min(secondSetStart + sizeOfSet - 1, size - 1);
				//Do not do merging again on last set if
				//		1. it contains only one element
				//		2. at end there is just one set left from previous iteration i.e. no second set present for merging
				if (firstSetStart == end || (end - firstSetStart + 1) <= sizeOfSet)
					continue;
				BottomUpMerge2(obj, firstSetStart, secondSetStart, end);
			}
		}
	}

	void MergeSortBottomUp2(DataSet& obj)
	{
		int size = obj.getSize();
		BottomUpSplit2(obj, size);
	}


	// MergeSort - BottomUpMerge 3 - space complexity O(n/2)
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void BottomUpMerge3(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//NEED to check smaller size set because both sets are NOT of same size. Second set will be smaller in this case. 
		//(First set can never be smaller, but lets implement generic algo to handle both cases)
		int firstSetSize = secondSetStart - firstSetStart;
		int secondSetSize = end - secondSetStart + 1;
		if (firstSetSize < secondSetSize)
		{
			//Create a copy of first set
			DataSet copy(obj.getCopy(firstSetStart, secondSetStart - 1));
			size_t counterFirstSet = 0;
			size_t counterSecondSet = secondSetStart;
			for (size_t k = firstSetStart; k <= end; k++)
			{
				bool firstSetOver = counterFirstSet >= copy.getSize();
				bool secondSetOver = counterSecondSet > end;
				if (firstSetOver)
					break;
				if (!secondSetOver && obj[counterSecondSet] < copy[counterFirstSet]) //This condition DOES NOT lose stability
				{
					if (k != counterSecondSet)
						obj[k] = obj[counterSecondSet];
					counterSecondSet++;
				}
				else
				{
					if (k != (counterFirstSet + firstSetStart))
						obj[k] = copy[counterFirstSet];
					counterFirstSet++;
				}
			}
		}
		else
		{
			//Create a copy of second set
			DataSet copy(obj.getCopy(secondSetStart, end));
			//Need to begin from end
			size_t counterFirstSet = secondSetStart - 1;
			size_t counterSecondSet = copy.getSize() - 1;
			for (size_t k = end; k >= firstSetStart; k--)
			{
				bool firstSetOver = counterFirstSet < firstSetStart;
				bool secondSetOver = counterSecondSet < 0;
				if (secondSetOver)
					break;
				if (!firstSetOver && copy[counterSecondSet] < obj[counterFirstSet]) //This condition DOES NOT lose stability
				{
					if (k != counterFirstSet)
						obj[k] = obj[counterFirstSet];
					counterFirstSet--;
				}
				else
				{
					if (k != (counterSecondSet + secondSetStart))
						obj[k] = copy[counterSecondSet];
					counterSecondSet--;
				}
			}
		}
	}
	void BottomUpSplit3(DataSet& obj, int size)
	{
		for (int sizeOfSet = 1; sizeOfSet < size; sizeOfSet *= 2)
		{
			for (int firstSetStart = 0; firstSetStart < size; firstSetStart += (2 * sizeOfSet))
			{
				int secondSetStart = min(firstSetStart + sizeOfSet, size - 1);
				int end = min(secondSetStart + sizeOfSet - 1, size - 1);
				//Do not do merging again on last set if
				//		1. it contains only one element
				//		2. at end there is just one set left from previous iteration i.e. no second set present for merging
				if (firstSetStart == end || (end - firstSetStart + 1) <= sizeOfSet)
					continue;
				BottomUpMerge3(obj, firstSetStart, secondSetStart, end);
			}
		}
	}

	void MergeSortBottomUp3(DataSet& obj)
	{
		int size = obj.getSize();
		BottomUpSplit3(obj, size);
	}

	// MergeSort - BottomUpMerge 4 - Average space complexity LESS THAN O(n/2). MAX space complexity O(n/2).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void BottomUpMerge4(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		//NEED to check smaller size set because both sets are NOT of same size. Second set will be smaller in this case. 
		//(First set can never be smaller, but lets implement generic algo to handle both cases)
		//Create a queue to keep the objects tempororily aside
		std::queue<Object> qObj;

		size_t firstSetSize = secondSetStart - firstSetStart;
		size_t secondSetSize = end - secondSetStart + 1;
		if (firstSetSize < secondSetSize)
		{
			size_t counterSecondSet = secondSetStart;
			for (size_t k = firstSetStart; k <= end; k++)
			{
				bool firstSetOver = k > secondSetStart - 1;
				bool secondSetOver = counterSecondSet > end;
				if (firstSetOver && qObj.empty())
					break;
				if (!secondSetOver &&
					qObj.empty()
					&& (obj[counterSecondSet] < obj[k]
						|| (!qObj.empty() && obj[counterSecondSet] < qObj.front()))
					) //This condition DOES NOT lose stability
				{
					//backup object of first set into queue
					if (!firstSetOver)
						qObj.push(obj[k]);
					obj[k] = obj[counterSecondSet++];
				}
				else
				{
					if (!qObj.empty())
					{
						//backup object of first set into queue
						if (!firstSetOver)
							qObj.push(obj[k]);
						obj[k] = qObj.front();
						qObj.pop();
					}
				}
			}
		}
		else
		{
			//Need to begin from end
			size_t counterFirstSet = secondSetStart - 1;
			for (size_t k = end; k >= firstSetStart; k--)
			{
				bool firstSetOver = counterFirstSet < firstSetStart;
				bool secondSetOver = k < secondSetStart;
				if (secondSetOver && qObj.empty())
					break;
				if (!firstSetOver
					&& ((qObj.empty() && obj[k] < obj[counterFirstSet])
						|| (!qObj.empty() && qObj.front() < obj[counterFirstSet]))
					) //This condition DOES NOT lose stability
				{
					//backup object of first set into queue
					if (!secondSetOver)
						qObj.push(obj[k]);
					obj[k] = obj[counterFirstSet--];
				}
				else
				{
					if (!qObj.empty())
					{
						//backup object of first set into queue
						if (!secondSetOver)
							qObj.push(obj[k]);
						obj[k] = qObj.front();
						qObj.pop();
					}
				}
			}
		}
	}
	void BottomUpSplit4(DataSet& obj, int size)
	{
		for (int sizeOfSet = 1; sizeOfSet < size; sizeOfSet *= 2)
		{
			for (int firstSetStart = 0; firstSetStart < size; firstSetStart += (2 * sizeOfSet))
			{
				int secondSetStart = min(firstSetStart + sizeOfSet, size - 1);
				int end = min(secondSetStart + sizeOfSet - 1, size - 1);
				//Do not do merging again on last set if
				//		1. it contains only one element
				//		2. at end there is just one set left from previous iteration i.e. no second set present for merging
				if (firstSetStart == end || (end - firstSetStart + 1) <= sizeOfSet)
					continue;
				BottomUpMerge4(obj, firstSetStart, secondSetStart, end);
			}
		}
	}

	void MergeSortBottomUp4(DataSet& obj)
	{
		int size = obj.getSize();
		BottomUpSplit4(obj, size);
	}


	// MergeSort - BottomUpMerge 5 - Space complexity O(1).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void BottomUpMerge5(DataSet& obj, const unsigned int firstSetStart, const unsigned int secondSetStart, const unsigned int end)
	{
		TopDownMerge7(obj, firstSetStart, secondSetStart, end);
	}
	void BottomUpSplit5(DataSet& obj, int size)
	{
		for (int sizeOfSet = 1; sizeOfSet < size; sizeOfSet *= 2)
		{
			for (int firstSetStart = 0; firstSetStart < size; firstSetStart += (2 * sizeOfSet))
			{
				int secondSetStart = min(firstSetStart + sizeOfSet, size - 1);
				int end = min(secondSetStart + sizeOfSet - 1, size - 1);
				//Do not do merging again on last set if
				//		1. it contains only one element
				//		2. at end there is just one set left from previous iteration i.e. no second set present for merging
				if (firstSetStart == end || (end - firstSetStart + 1) <= sizeOfSet)
					continue;
				BottomUpMerge5(obj, firstSetStart, secondSetStart, end);
			}
		}
	}

	void MergeSortBottomUp5(DataSet& obj)
	{
		int size = obj.getSize();
		BottomUpSplit5(obj, size);
	}


	// MergeSort - NaturalMerge_noIterators - space complexity O(n)
	//=======================================================================================

	void NaturalMerge_noIterators(DataSet& firstSet, int firstSetStart, int secondSetStart, int end, DataSet& secondSet)
	{
		//This is same as TopDownMerge
		TopDownMerge1(firstSet, firstSetStart, secondSetStart, end, secondSet);
	}
	void NaturalMergeSortSplit_noIterators(DataSet& obj, int size, DataSet& copy)
	{
		vector<int> runBoundaries;
		runBoundaries.push_back(0);
		for (int i = 1; i < size; i++)
			if (obj[i] < obj[i - 1]) //equivalent to obj[i - 1] > obj[i]
				runBoundaries.push_back(i);
		bool noToggle = int(ceil(log2(runBoundaries.size()))) % 2 != 0;
		while (runBoundaries.size() > 1)
		{
			for (size_t i = 0; i < runBoundaries.size();)
			{
				int firstSetStart = runBoundaries[i];
				int secondSetStart = i + 1 < runBoundaries.size() ? runBoundaries[i + 1] : size - 1;
				int end = i + 2 < runBoundaries.size() ? runBoundaries[i + 2] - 1 : size - 1;
				if (noToggle)
					NaturalMerge_noIterators(obj, firstSetStart, secondSetStart, end, copy);
				else
					NaturalMerge_noIterators(copy, firstSetStart, secondSetStart, end, obj);

				if (i + 1 < runBoundaries.size())
				{
					runBoundaries.erase(runBoundaries.begin() + i + 1);
					i++;
				}
				else
					i += 2;
			}
			noToggle = noToggle == false;
		}
	}

	void NaturalMergeSort_noIterators(DataSet& obj)
	{
		int size = obj.getSize();
		DataSet copy(obj.getCopy());
		NaturalMergeSortSplit_noIterators(obj, size, copy);
	}

	// MergeSort - NaturalMerge 1
	//This is better approach than above as it uses vector iterators - space complexity O(n)
	//=======================================================================================

	void NaturalMerge1(DataSet& firstSet, int firstSetStart, int secondSetStart, int end, DataSet& secondSet)
	{
		//This is same as TopDownMerge
		TopDownMerge1(firstSet, firstSetStart, secondSetStart, end, secondSet);
	}
	void NaturalMergeSortSplit1(DataSet& obj, int size, DataSet& copy)
	{
		vector<int> runBoundaries;
		runBoundaries.push_back(0);
		for (int i = 1; i < size; i++)
			if (obj[i] < obj[i - 1]) //equivalent to obj[i - 1] > obj[i]
				runBoundaries.push_back(i);
		bool noToggle = int(ceil(log2(runBoundaries.size()))) % 2 != 0;
		while (runBoundaries.size() > 1)
		{
			for (auto itFirstSetStart = runBoundaries.begin(); itFirstSetStart != runBoundaries.end();)
			{
				int firstSetStart = *itFirstSetStart;

				auto itSecondSetStart = itFirstSetStart + 1;
				int secondSetStart;
				if (itSecondSetStart != runBoundaries.end())
				{
					secondSetStart = *itSecondSetStart;
					runBoundaries.erase(itSecondSetStart);
				}
				else
					secondSetStart = size - 1;

				int end = (++itFirstSetStart != runBoundaries.end()) ? *itFirstSetStart - 1 : size - 1;

				if (noToggle)
					NaturalMerge1(obj, firstSetStart, secondSetStart, end, copy);
				else
					NaturalMerge1(copy, firstSetStart, secondSetStart, end, obj);
			}
			noToggle = noToggle == false;
		}
	}

	void NaturalMergeSort1(DataSet& obj)
	{
		int size = obj.getSize();
		DataSet copy(obj.getCopy());
		NaturalMergeSortSplit1(obj, size, copy);
	}

	// MergeSort - NaturalMerge 2 - space complexity O(n/2)
	//=======================================================================================

	void NaturalMerge2(DataSet& obj, int firstSetStart, int secondSetStart, int end)
	{
		//This is same as BottomUpMerge2
		BottomUpMerge2(obj, firstSetStart, secondSetStart, end);
	}
	void NaturalMergeSortSplit2(DataSet& obj, int size)
	{
		vector<int> runBoundaries;
		runBoundaries.push_back(0);
		for (int i = 1; i < size; i++)
			if (obj[i] < obj[i - 1]) //equivalent to obj[i - 1] > obj[i]
				runBoundaries.push_back(i);

		while (runBoundaries.size() > 1)
		{
			for (auto itFirstSetStart = runBoundaries.begin(); itFirstSetStart != runBoundaries.end();)
			{
				int firstSetStart = *itFirstSetStart;

				auto itSecondSetStart = itFirstSetStart + 1;
				int secondSetStart;
				if (itSecondSetStart != runBoundaries.end())
				{
					secondSetStart = *itSecondSetStart;
					runBoundaries.erase(itSecondSetStart);
				}
				else
					secondSetStart = size - 1;

				int end = (++itFirstSetStart != runBoundaries.end()) ? *itFirstSetStart - 1 : size - 1;

				NaturalMerge2(obj, firstSetStart, secondSetStart, end);
			}
		}
	}

	void NaturalMergeSort2(DataSet& obj)
	{
		int size = obj.getSize();
		NaturalMergeSortSplit2(obj, size);
	}

	// MergeSort - NaturalMerge 3 - space complexity O(n/2)
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void NaturalMerge3(DataSet& obj, int firstSetStart, int secondSetStart, int end)
	{
		//This is same as BottomUpMerge2
		BottomUpMerge3(obj, firstSetStart, secondSetStart, end);
	}
	void NaturalMergeSortSplit3(DataSet& obj, int size)
	{
		vector<int> runBoundaries;
		runBoundaries.push_back(0);
		for (int i = 1; i < size; i++)
			if (obj[i] < obj[i - 1]) //equivalent to obj[i - 1] > obj[i]
				runBoundaries.push_back(i);

		while (runBoundaries.size() > 1)
		{
			for (auto itFirstSetStart = runBoundaries.begin(); itFirstSetStart != runBoundaries.end();)
			{
				int firstSetStart = *itFirstSetStart;

				auto itSecondSetStart = itFirstSetStart + 1;
				int secondSetStart;
				if (itSecondSetStart != runBoundaries.end())
				{
					secondSetStart = *itSecondSetStart;
					runBoundaries.erase(itSecondSetStart);
				}
				else
					secondSetStart = size - 1;

				int end = (++itFirstSetStart != runBoundaries.end()) ? *itFirstSetStart - 1 : size - 1;

				NaturalMerge3(obj, firstSetStart, secondSetStart, end);
			}
		}
	}

	void NaturalMergeSort3(DataSet& obj)
	{
		int size = obj.getSize();
		NaturalMergeSortSplit3(obj, size);
	}


	// MergeSort - NaturalMerge 4 - Average space complexity LESS THAN O(n/2). MAX space complexity O(n/2).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void NaturalMerge4(DataSet& obj, int firstSetStart, int secondSetStart, int end)
	{
		//This is same as BottomUpMerge2
		BottomUpMerge4(obj, firstSetStart, secondSetStart, end);
	}
	void NaturalMergeSortSplit4(DataSet& obj, int size)
	{
		vector<int> runBoundaries;
		runBoundaries.push_back(0);
		for (int i = 1; i < size; i++)
			if (obj[i] < obj[i - 1]) //equivalent to obj[i - 1] > obj[i]
				runBoundaries.push_back(i);

		while (runBoundaries.size() > 1)
		{
			for (auto itFirstSetStart = runBoundaries.begin(); itFirstSetStart != runBoundaries.end(); )
			{
				int firstSetStart = *itFirstSetStart;

				auto itSecondSetStart = itFirstSetStart + 1;
				int secondSetStart;
				if (itSecondSetStart != runBoundaries.end())
				{
					secondSetStart = *itSecondSetStart;
					runBoundaries.erase(itSecondSetStart);
				}
				else
					secondSetStart = size - 1;

				int end = (++itFirstSetStart != runBoundaries.end()) ? *itFirstSetStart - 1 : size - 1;

				NaturalMerge4(obj, firstSetStart, secondSetStart, end);
			}
		}
	}

	void NaturalMergeSort4(DataSet& obj)
	{
		int size = obj.getSize();
		NaturalMergeSortSplit4(obj, size);
	}

	// MergeSort - NaturalMerge 4 - Average space complexity LESS THAN O(n/2). MAX space complexity O(n/2).
	//Further optimization - avoid assignments if the objects are same
	//=======================================================================================

	void NaturalMerge5(DataSet& obj, int firstSetStart, int secondSetStart, int end)
	{
		//This is same as BottomUpMerge2
		TopDownMerge7(obj, firstSetStart, secondSetStart, end);
	}
	void NaturalMergeSortSplit5(DataSet& obj, int size)
	{
		vector<int> runBoundaries;
		runBoundaries.push_back(0);
		for (int i = 1; i < size; i++)
			if (obj[i] < obj[i - 1]) //equivalent to obj[i - 1] > obj[i]
				runBoundaries.push_back(i);

		while (runBoundaries.size() > 1)
		{
			for (auto itFirstSetStart = runBoundaries.begin(); itFirstSetStart != runBoundaries.end(); )
			{
				int firstSetStart = *itFirstSetStart;

				auto itSecondSetStart = itFirstSetStart + 1;
				int secondSetStart;
				if (itSecondSetStart != runBoundaries.end())
				{
					secondSetStart = *itSecondSetStart;
					runBoundaries.erase(itSecondSetStart);
				}
				else
					secondSetStart = size - 1;

				int end = (++itFirstSetStart != runBoundaries.end()) ? *itFirstSetStart - 1 : size - 1;

				NaturalMerge5(obj, firstSetStart, secondSetStart, end);
			}
		}
	}

	void NaturalMergeSort5(DataSet& obj)
	{
		int size = obj.getSize();
		NaturalMergeSortSplit5(obj, size);
	}

	/*
	DONE:
	All above 3 solutions for n/2 space complexity. Copy smaller size sorted partition and start from front or back.
	Use queue while merging to reduce space complexity further.Choose smaller sorted section to add into queue.
	With O(1) space complexity - use selection sort like technique to slide elements. Choose smaller sorted section to move.

	TODO:
	try to avoid vector for NaturalMergeSort - Looks difficult
	*/


	//=======================+==================+
	//                       | Block Merge Sort |
	//=======================+==================+

}