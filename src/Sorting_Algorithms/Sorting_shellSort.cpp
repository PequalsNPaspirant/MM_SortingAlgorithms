#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_shellSort.h"

namespace mm {


	//=======================+============+
	//                       | Shell Sort |
	//=======================+============+

	// Shell Sort - common functions
	//=======================================================================================

	void InsertionSort_t1_modifiedToResuseForShellSort(DataSet& obj, const vector<int>& gapSequence)
	{
		int size = obj.getSize();
		if (size == 1) return;
		int gapSeqSize = static_cast<int>(gapSequence.size());
		MyAssert::myRunTimeAssert(gapSequence[0] == 1, "Gap sequence must start with 1");
		for (int gapIndex = gapSeqSize - 1; gapIndex >= 0; --gapIndex)
		{
			int gap = gapSequence[gapIndex];

			for (int current = gap; current < size; ++current)
			{
				int left = current % gap;
				int right = current;

				while (left <= (right - gap))
				{
					int totalGaps = (right - left) / gap;
					int mid = left + (totalGaps / 2 * gap);
					if (obj[current] < obj[mid])
						right = mid;
					else //if (obj[mid] >= obj[current])
						left = mid + gap;
				}
				int targetPos = right;

				if (current != targetPos)
				{
					Object temp = obj[current];
					for (int j = current; j > targetPos; j -= gap)
						obj[j] = obj[j - gap];
					obj[targetPos] = temp;
				}
			}
		}
	}

	//This algo is more efficient than above binary search in case of shell sort, since in shell sort
	//the original array is subdivided and the insertion sort is performed over a shorter length array (at indices 0, 0 + gap, 0 + 2*gap, ...etc)
	//So binary search over previous array is not required. Binary search is useful when the element is to be inserted in the large sorted array 
	void InsertionSort_t2_modifiedToResuseForShellSort(DataSet& obj, const vector<int>& gapSequence)
	{
		int size = obj.getSize();
		if (size == 1) return;
		int gapSeqSize = static_cast<int>(gapSequence.size());
		MyAssert::myRunTimeAssert(gapSequence[0] == 1, "Gap sequence must start with 1");
		for (int gapIndex = gapSeqSize - 1; gapIndex >= 0; --gapIndex)
		{
			int gap = gapSequence[gapIndex];
			for (int current = gap; current < size; ++current)
			{
				Object temp = obj[current];
				int j;
				for (j = current; j >= gap && temp < obj[j - gap]; j -= gap)
					obj[j] = obj[j - gap];

				obj[j] = temp;
			}
		}
	}

	// Shell Sort 1 - fibonacci series as gap sequence
	//=======================================================================================

	void ShellSort_t1(DataSet& obj)
	{
		int size = obj.getSize();
		vector<int> gapSequence;

		//Create fibonacci series as gap sequence
		gapSequence.push_back(1);
		gapSequence.push_back(2);
		for (int i = 1; gapSequence[i] < size;)
		{
			++i;
			gapSequence.push_back(gapSequence[i - 1] + gapSequence[i - 2]);
		}

		InsertionSort_t1_modifiedToResuseForShellSort(obj, gapSequence);
	}

	void ShellSort_t2(DataSet& obj)
	{
		int size = obj.getSize();
		vector<int> gapSequence;

		//Create fibonacci series as gap sequence
		gapSequence.push_back(1);
		gapSequence.push_back(2);
		for (int i = 1; gapSequence[i] < size;)
		{
			++i;
			gapSequence.push_back(gapSequence[i - 1] + gapSequence[i - 2]);
		}

		InsertionSort_t2_modifiedToResuseForShellSort(obj, gapSequence);
	}

	// Shell Sort 1 - gap sequence - 1, 2, 4, 8, ..., 2^n
	//=======================================================================================

	void ShellSort_t3(DataSet& obj)
	{
		int size = obj.getSize();
		vector<int> gapSequence;

		//Create fibonacci series as gap sequence
		gapSequence.push_back(1);
		for (int i = 0; gapSequence[i] < size;)
		{
			++i;
			gapSequence.push_back(2 * gapSequence[i - 1]);
		}

		InsertionSort_t1_modifiedToResuseForShellSort(obj, gapSequence);
	}

	void ShellSort_t4(DataSet& obj)
	{
		int size = obj.getSize();
		vector<int> gapSequence;

		//Create fibonacci series as gap sequence
		gapSequence.push_back(1);
		for (int i = 0; gapSequence[i] < size;)
		{
			++i;
			gapSequence.push_back(2 * gapSequence[i - 1]);
		}

		InsertionSort_t2_modifiedToResuseForShellSort(obj, gapSequence);
	}

	// Shell Sort 1 - gap sequence - n/2, n/4, n/8, ..., 1
	//=======================================================================================

	void ShellSort_t5(DataSet& obj)
	{
		int size = obj.getSize();
		vector<int> gapSequence;

		//Create fibonacci series as gap sequence
		for (int currentGap = size / 2; currentGap > 0; currentGap /= 2)
		{
			gapSequence.push_back(currentGap);
		}

		std::reverse(gapSequence.begin(), gapSequence.end());

		InsertionSort_t1_modifiedToResuseForShellSort(obj, gapSequence);
	}

	void ShellSort_t6(DataSet& obj)
	{
		int size = obj.getSize();
		vector<int> gapSequence;

		//Create fibonacci series as gap sequence
		for (int currentGap = size / 2; currentGap > 0; currentGap /= 2)
		{
			gapSequence.push_back(currentGap);
		}

		std::reverse(gapSequence.begin(), gapSequence.end());

		InsertionSort_t2_modifiedToResuseForShellSort(obj, gapSequence);
	}


}