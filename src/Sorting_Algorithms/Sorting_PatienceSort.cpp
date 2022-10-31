#include <algorithm>    // std::random_shuffle

#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_STL_Sort.h"

namespace mm {

	//TODO: implement the definition
	void PatienceSort(DataSet& obj)
	{
		std::vector<int> input;

		//sort all elements into buckets
		std::vector< std::vector<int> > buckets;
		for (int i = 0; i < input.size(); ++i)
		{
			bool addedCurrElement = false;
			for (int j = 0; j < buckets.size(); ++j)
			{
				if (buckets[j].empty() || buckets[j].back() < input[i])
				{
					buckets[j].push_back(input[i]);
					addedCurrElement = true;
					break;
				}
			}

			if (!addedCurrElement)
			{
				buckets.push_back(std::vector<int>{});
				buckets.back().push_back(input[i]);
			}
		}

		//Merge all elements from bucket to retVal
		auto merge = [](std::vector<int>& retVal, std::vector<int>& bucket) {

		};

		//Each bucket it sorted. Merge all buckets.
		std::vector<int> retVal;
		for (int j = 0; j < buckets.size(); ++j)
		{
			merge(retVal, buckets[j]);
		}
	}

}