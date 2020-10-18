#include <algorithm>    // std::random_shuffle

#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_STL_Sort.h"

namespace mm {


	//=======================+===========+
	//                       | std::sort |
	//=======================+===========+

	void StlSort_1(DataSet& obj)
	{
		int size = obj.getSize();
		Object* start = &obj[0];
		Object* pastEnd = start + size;
		std::sort(start, pastEnd);
	}

	void StlStableSort_1(DataSet& obj)
	{
		int size = obj.getSize();
		Object* start = &obj[0];
		Object* pastEnd = start + size;
		std::stable_sort(start, pastEnd);
	}

	void StlHeapSort_1(DataSet& obj)
	{
		int size = obj.getSize();
		Object* start = &obj[0];
		Object* pastEnd = start + size;
		std::make_heap(start, pastEnd);
		std::sort_heap(start, pastEnd);
	}



	//=======================+==========+
	//                       | Tim Sort |
	//=======================+==========+

	//=======================+==========+
	//                       | Comb Sort |
	//=======================+==========+

	//=======================+==========+
	//                       | Bitonic Sort |
	//=======================+==========+

	//=======================+==========+
	//                       | Cocktail Shaker Sort |
	//=======================+==========+

	//=======================+==========+
	//                       | Gnome Sort |
	//=======================+==========+

	//=======================+==========+
	//                       | Cycle Sort |
	//=======================+==========+

	//=======================+==========+
	//                       | Odd-event Sort |
	//=======================+==========+

	//=======================+==========+
	//                       | Spaghetti Sort |
	//=======================+==========+

	//=======================+==========+
	//                       | Batcher's Sort |
	//=======================+==========+


	// Tim Sort - Trial Version 1
	//=======================================================================================



	//External Sorting - http://www.geeksforgeeks.org/external-sorting/



}