#include "Sorting_dataStructure/Sorting_dataStructure.h"
#include "Sorting_Algorithms/Sorting_heapSort.h"

namespace mm {


	//=======================+============+
	//                       | Heap Sort |
	//=======================+============+

	//Common Helper Functions
	//------------------------------------------------------------------------------------

	int LeftChild(int index) {
		return ((index << 1) + 1);
	}

	int RightChild(int index) {
		return ((index << 1) + 2);
	}

	int Parent(int index) {
		return ((index - 1) >> 1);
	}

	int getLeftChildIndex(int index) {
		return (index * 2 + 1);
	}

	int getRightChildIndex(int index) {
		return (index * 2 + 2);
	}

	//floor rounds towards negative infinity, while integer division rounds towards zero (truncates)
	// floor((2 - 1) / 2.0) = floor(0.5) = 0
	// (2 - 1) / 2 = 1 / 2 = 0   ( .5 is truncated from actual result 0.5. In fact, integer division does not calculate anything after decimal point)
	// (2 + 1) / 2 - 1 = 3 / 2 - 1 = 1 - 1 = 0

	int getParentIndex(int index) {
		return floor((index - 1) / 2.0); // returns -1 for iIndex = 0
	}

	int getParentIndex2(int index) {
		if (index > 0)
			return ((index - 1) / 2); // returns 0 for iIndex = 0
		else
			return -1;
	}

	int getParentIndex3(int index) {
		return ((index + 1) / 2 - 1);
	}

	int getParentIndex4(int index) {
		return ((index + (index % 2)) / 2 - 1);
	}

	int getLevel(int index) //level starts from zero
	{
		return floor(log(index + 1));
	}

	// sift up Functions
	//------------------------------------------------------------------------------------

	//This is equivalent to adding new element at the end of a valid heap
	//Used for heapify top-down		- Yes
	//Used for heapify bottom-up	- No
	//Used for extract Max			- No

	void siftUp1(DataSet& obj, int childIndex)
	{
		while (true)
		{
			int parentIndex = getParentIndex(childIndex);

			if (parentIndex > -1 && obj[parentIndex] < obj[childIndex])
				obj[parentIndex].swap(obj[childIndex]);
			else
				break;

			childIndex = parentIndex;
		}
	}

	//This is equivalent to replacing the top element of a valid heap. So new top element needs to be places at appropriate position
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftUp2(DataSet& obj, const int heapSize, const int index)
	{
		Object temp = obj[index];

		int parent = index;
		int child = getLeftChildIndex(parent);
		while (child < heapSize)
		{
			if (child < heapSize - 1)
				if (obj[child] < obj[child + 1])
					child++;
			obj[parent] = obj[child];
			parent = child;
			child = getLeftChildIndex(parent);
		}

		child = parent;
		parent = getParentIndex(child);
		while (parent >= index)
		{
			if (obj[parent] < temp)
			{
				obj[child] = obj[parent];
				child = parent;
				parent = getParentIndex(child);
			}
			else break;
		}
		obj[child] = temp;
	}

	//This is optimized version of siftUp2(). Do binary search in SECOND while loop along the path the root element can descend. So the element can be positioned in O(log log n)
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftUp3(DataSet& obj, const int heapSize, const int index)
	{
		Object temp = obj[index];

		int parent = index;
		int child = getLeftChildIndex(parent);
		while (child < heapSize)
		{
			if (child < heapSize - 1)
				if (obj[child] < obj[child + 1])
					child++;
			obj[parent] = obj[child];
			parent = child;
			child = getLeftChildIndex(parent);
		}

		obj[parent] = temp;

		int start = index;
		int end = getParentIndex(parent);
		int startLevel = getLevel(start);
		int endLevel = getLevel(end);

		if (!(obj[end] < temp)) //i.e. obj[end] >= temp
		{
			return;
		}
		else if (temp < obj[start])
		{
			end = start;
		}
		else
		{
			while (endLevel - startLevel > 1)
			{
				int midLevel = (startLevel + endLevel) / 2;
				int mid = end;
				for (int i = endLevel; i > midLevel; i--)
					mid = getParentIndex(mid);

				if (temp < obj[mid])
				{
					end = mid;
					endLevel = getLevel(mid);
				}
				else
				{
					start = mid;
					startLevel = getLevel(mid);
				}
			}
		}

		child = parent;
		parent = getParentIndex(child);
		while (parent >= end)
		{
			obj[child] = obj[parent];
			child = parent;
			parent = getParentIndex(child);
		}
		obj[end] = temp;
	}

	//This is optimized version of siftUp3(). Return if the top element is already at right position.
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftUp4(DataSet& obj, const int heapSize, const int index)
	{
		Object temp = obj[index];

		int parent = index;
		int child = getLeftChildIndex(parent);
		while (child < heapSize)
		{
			if (child < heapSize - 1)
				if (obj[child] < obj[child + 1])
					child++;
			if (parent == index && !(obj[parent] < obj[child])) //i.e. obj[parent] >= obj[child]
				return;
			obj[parent] = obj[child];
			parent = child;
			child = getLeftChildIndex(parent);
		}

		obj[parent] = temp;

		int start = index;
		int end = getParentIndex(parent);
		int startLevel = getLevel(start);
		int endLevel = getLevel(end);

		if (!(obj[end] < temp)) //i.e. obj[end] >= temp
		{
			return;
		}
		//else if (temp < obj[start])
		//{
		//	end = start;
		//}
		else
		{
			while (endLevel - startLevel > 1)
			{
				int midLevel = (startLevel + endLevel) / 2;
				int mid = end;
				for (int i = endLevel; i > midLevel; i--)
					mid = getParentIndex(mid);

				if (temp < obj[mid])
				{
					end = mid;
					endLevel = getLevel(mid);
				}
				else
				{
					start = mid;
					startLevel = getLevel(mid);
				}
			}
		}

		child = parent;
		parent = getParentIndex(child);
		while (parent >= end)
		{
			obj[child] = obj[parent];
			child = parent;
			parent = getParentIndex(child);
		}
		obj[end] = temp;
	}

	//This is optimized version of siftUp4(). Return if the top element is already at right position. But do binary search more efficiently.
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftUp5(DataSet& obj, const int heapSize, const int index)
	{
		//////////////////////////////////TODO: implement efficient binary search
		Object temp = obj[index];

		int parent = index;
		int child = getLeftChildIndex(parent);
		while (child < heapSize)
		{
			if (child < heapSize - 1)
				if (obj[child] < obj[child + 1])
					child++;
			if (parent == index && !(obj[parent] < obj[child])) //i.e. obj[parent] >= obj[child]
				return;
			obj[parent] = obj[child];
			parent = child;
			child = getLeftChildIndex(parent);
		}

		obj[parent] = temp;

		int start = index;
		int end = getParentIndex(parent);
		int startLevel = getLevel(start);
		int endLevel = getLevel(end);

		if (!(obj[end] < temp)) //i.e. obj[end] >= temp
		{
			return;
		}

		while (startLevel < endLevel)
		{
			int midLevel = (startLevel + endLevel) / 2;
			int mid = end;
			for (int i = endLevel; i > midLevel; i--)
				mid = getParentIndex(mid);

			if (temp < obj[mid])
			{
				end = mid;
				endLevel = getLevel(mid);
			}
			else
			{
				start = mid + 1;
				startLevel = getLevel(mid + 1);
			}
		}

		child = parent;
		parent = getParentIndex(child);
		while (parent >= end)
		{
			obj[child] = obj[parent];
			child = parent;
			parent = getParentIndex(child);
		}
		obj[end] = temp;
	}


	//This is optimized version of siftUp2(). Do binary search in FIRST while loop along the path the root element can descend. 
	//So the element can be positioned in O(log log n). Second while loop may not be needed. This may give same performace as siftDown3().
	//In fact it is same as siftDown3() because the first loop descends down, so it is sift-down.
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftDown3(DataSet& obj, const int heapSize, const int index);
	void siftUp6(DataSet& obj, const int heapSize, const int index)
	{
		siftDown3(obj, heapSize, index);
	}

	// sift down Functions
	//------------------------------------------------------------------------------------

	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftDown1_usingRecursion(DataSet& obj, int heapSize, int subTreeRootIndex)
	{
		int largest = subTreeRootIndex;  // Initialize largest as root
		int leftChildIndex = LeftChild(subTreeRootIndex);  // left = 2*i + 1
		int rightChildIndex = RightChild(subTreeRootIndex);  // right = 2*i + 2

															 // If left child is larger than root
		if (leftChildIndex < heapSize && obj[largest] < obj[leftChildIndex])
			largest = leftChildIndex;

		// If right child is larger than largest so far
		if (rightChildIndex < heapSize && obj[largest] < obj[rightChildIndex])
			largest = rightChildIndex;

		// If root is largest, return 
		if (largest == subTreeRootIndex)
			return;
		else
		{
			obj[subTreeRootIndex].swap(obj[largest]);

			// Recursively heapify the affected sub-tree
			siftDown1_usingRecursion(obj, heapSize, largest);
		}
	}
	void siftDown1_withoutRecursion(DataSet& obj, int heapSize, int subTreeRootIndex)
	{
		while (subTreeRootIndex < heapSize)
		{
			int largest = subTreeRootIndex;
			int leftChildIndex = getLeftChildIndex(subTreeRootIndex);
			int rightChildIndex = getRightChildIndex(subTreeRootIndex);

			// If left child is larger than root
			if (leftChildIndex < heapSize && obj[largest] < obj[leftChildIndex])
				largest = leftChildIndex;

			// If right child is larger than largest so far
			if (rightChildIndex < heapSize && obj[largest] < obj[rightChildIndex])
				largest = rightChildIndex;

			// If root is largest, return 
			if (largest == subTreeRootIndex)
				break;
			else
			{
				obj[subTreeRootIndex].swap(obj[largest]);
				subTreeRootIndex = largest;
			}
		}
	}

	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- No
	//Used for extract Max			- Yes
	int leafSearch(DataSet& obj, int index)
	{
		int retVal = -1;
		size_t leftChildIndex = getLeftChildIndex(index);
		size_t rightChildIndex = getRightChildIndex(index); //OR rightChildIndex = leftChildIndex + 1
		if (leftChildIndex < obj.getSize())
		{
			retVal = leftChildIndex;
			if (rightChildIndex < obj.getSize())
			{
				if (obj[leftChildIndex] < obj[rightChildIndex])
					retVal = rightChildIndex;
				else
					retVal = leftChildIndex;
			}
		}
		return retVal;
	}
	void siftDown2(DataSet& obj, int heapSize, int index)
	{
		int biggestChild = leafSearch(obj, index);
		while (biggestChild != -1 && biggestChild > heapSize)
		{
			//Object temp = obj[index];
			obj[index] = obj[biggestChild];
			index = biggestChild;
			biggestChild = leafSearch(obj, index);
		}
	}

	//This is optimized version of siftDown1_withoutRecursion(). Do binary search along the path the root element can descend. So the element can be positioned in O(log log n)
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftDown3(DataSet& obj, int heapSize, int index)
	{
		int child = getLeftChildIndex(index);
		int start = -1;
		int parent = index;
		while (child < heapSize)
		{
			if (child < heapSize - 1)
				if (obj[child] < obj[child + 1])
					child++;
			if (start == -1)
				start = child;
			parent = child;
			child = getLeftChildIndex(parent);
		}

		int end = parent;
		int startLevel = getLevel(start);
		int endLevel = getLevel(end);

		if (!(obj[index] < obj[start])) //i.e. obj[index] >= obj[start]
		{
			return;
		}
		else if (obj[index] < obj[end])
		{
			start = end;
		}
		else
		{
			while (endLevel - startLevel > 1)
			{
				int midLevel = (startLevel + endLevel) / 2;
				int mid = end;
				for (int i = endLevel; i > midLevel; i--)
					mid = getParentIndex(mid);

				if (obj[mid] < obj[index])
				{
					start = mid;
					startLevel = getLevel(mid);
				}
				else
				{
					end = mid;
					endLevel = getLevel(mid);
				}
			}
		}

		parent = getParentIndex(start);
		Object temp = obj[start];
		while (parent >= index)
		{
			obj[parent].swap(temp);
			parent = getParentIndex(parent);
		}
		obj[start] = temp;
	}

	//This is optimized version of siftDown3(). Return if the top element is already at right position.
	//Used for heapify top-down		- No
	//Used for heapify bottom-up	- Yes
	//Used for extract Max			- Yes
	void siftDown4(DataSet& obj, int heapSize, int index)
	{
		int child = getLeftChildIndex(index);
		int start = -1;
		int parent = index;
		while (child < heapSize)
		{
			if (child < heapSize - 1)
				if (obj[child] < obj[child + 1])
					child++;
			if (start == -1)
			{
				start = child;
				if (!(obj[index] < obj[start])) //i.e. obj[index] >= obj[start]
				{
					return;
				}
			}
			parent = child;
			child = getLeftChildIndex(parent);
		}

		int end = parent;
		int startLevel = getLevel(start);
		int endLevel = getLevel(end);

		//if (!(obj[index] < obj[start])) //i.e. obj[index] >= obj[start]
		//{
		//	return;
		//}
		//else 
		if (obj[index] < obj[end])
		{
			start = end;
		}
		else
		{
			while (endLevel - startLevel > 1)
			{
				int midLevel = (startLevel + endLevel) / 2;
				int mid = end;
				for (int i = endLevel; i > midLevel; i--)
					mid = getParentIndex(mid);

				if (obj[mid] < obj[index])
				{
					start = mid;
					startLevel = getLevel(mid);
				}
				else
				{
					end = mid;
					endLevel = getLevel(mid);
				}
			}
		}

		parent = getParentIndex(start);
		Object temp = obj[start];
		while (parent >= index)
		{
			obj[parent].swap(temp);
			parent = getParentIndex(parent);
		}
		obj[start] = temp;
	}


	// heapify top-down Functions
	//------------------------------------------------------------------------------------

	void heapify_TopDown1(DataSet& obj)
	{
		// Build heap (rearrange array)
		int size = obj.getSize();
		for (int childIndex = 1; childIndex < size; childIndex++)
			siftUp1(obj, childIndex);
	}

	// heapify bottom-up Functions
	//------------------------------------------------------------------------------------

	void heapify_BottomUp1_usingRecursion(DataSet& obj)
	{
		// Build heap (rearrange array)
		int size = obj.getSize();
		int parentIndex = Parent(size - 1); //size / 2 - 1
		for (int subTreeRootIndex = parentIndex; subTreeRootIndex >= 0; subTreeRootIndex--)
			siftDown1_usingRecursion(obj, size, subTreeRootIndex);
	}

	void heapify_BottomUp1_withoutRecursion(DataSet& obj)
	{
		// Build heap (rearrange array)
		int size = obj.getSize();
		int parentIndex = getParentIndex(size - 1); //size / 2 - 1
		for (int subTreeRootIndex = parentIndex; subTreeRootIndex >= 0; subTreeRootIndex--)
			siftDown1_withoutRecursion(obj, size, subTreeRootIndex);
	}

	void heapify_BottomUp2(DataSet& obj)
	{
		int size = obj.getSize();
		int parentIndex = getParentIndex(size - 1);
		for (int subTreeRootIndex = parentIndex; subTreeRootIndex >= 0; subTreeRootIndex--)
			siftUp2(obj, size, subTreeRootIndex);
	}

	void heapify_BottomUp3(DataSet& obj)
	{
		int size = obj.getSize();
		int parentIndex = getParentIndex(size - 1);
		for (int subTreeRootIndex = parentIndex; subTreeRootIndex >= 0; subTreeRootIndex--)
			siftUp3(obj, size, subTreeRootIndex);
	}

	void heapify_BottomUp4(DataSet& obj)
	{
		int size = obj.getSize();
		int parentIndex = getParentIndex(size - 1);
		for (int subTreeRootIndex = parentIndex; subTreeRootIndex >= 0; subTreeRootIndex--)
			siftUp4(obj, size, subTreeRootIndex);
	}

	void heapify_BottomUp5(DataSet& obj)
	{
		int size = obj.getSize();
		int parentIndex = getParentIndex(size - 1);
		for (int subTreeRootIndex = parentIndex; subTreeRootIndex >= 0; subTreeRootIndex--)
			siftDown3(obj, size, subTreeRootIndex);
	}

	void heapify_BottomUp6(DataSet& obj)
	{
		int size = obj.getSize();
		int parentIndex = getParentIndex(size - 1);
		for (int subTreeRootIndex = parentIndex; subTreeRootIndex >= 0; subTreeRootIndex--)
			siftDown4(obj, size, subTreeRootIndex);
	}

	// Extract max Functions
	//------------------------------------------------------------------------------------

	void extractMax1_usingRecursion(DataSet& obj)
	{
		// One by one extract an element from heap
		int size = obj.getSize();
		for (int heapSize = size - 1; heapSize >= 0; heapSize--)
		{
			// Move current root to end
			obj[0].swap(obj[heapSize]);

			// call max heapify on the reduced heap
			siftDown1_usingRecursion(obj, heapSize, 0);
		}
	}

	void extractMax1_withoutRecursion(DataSet& obj)
	{
		// One by one extract an element from heap
		int size = obj.getSize();
		for (int heapSize = size - 1; heapSize >= 0; heapSize--)
		{
			// Move current root to end
			obj[0].swap(obj[heapSize]);

			// call max heapify on the reduced heap
			siftDown1_withoutRecursion(obj, heapSize, 0);
		}
	}

	//This is most optimized function as it avoids swaps
	void extractMax2(DataSet& obj)
	{
		// One by one extract an element from heap
		int size = obj.getSize();
		for (int heapSize = size - 1; heapSize > 0; heapSize--)
		{
			// Move current root to end
			Object temp = obj[0];

			// call max heapify on the reduced heap
			siftDown2(obj, heapSize, 0);

			obj[heapSize] = temp;
		}
	}

	void extractMax3(DataSet& obj)
	{
		// One by one extract an element from heap
		int size = obj.getSize();
		for (int heapSize = size - 1; heapSize > 0; heapSize--)
		{
			obj[heapSize].swap(obj[0]);
			siftUp2(obj, heapSize, 0);
		}
	}

	void extractMax4(DataSet& obj)
	{
		// One by one extract an element from heap
		int size = obj.getSize();
		for (int heapSize = size - 1; heapSize > 0; heapSize--)
		{
			obj[heapSize].swap(obj[0]);
			siftUp3(obj, heapSize, 0);
		}
	}

	// HeapSort
	//=======================================================================================

	//This is NOT stable sort
	void HeapSortInPlace1(DataSet& obj)
	{
		heapify_TopDown1(obj);
		extractMax1_withoutRecursion(obj);
	}

	//This is stable sort
	void HeapSortInPlace2(DataSet& obj)
	{
		heapify_TopDown1(obj);
		extractMax2(obj);
	}

	//This is NOT stable sort
	void HeapSortInPlace3(DataSet& obj)
	{
		heapify_TopDown1(obj);
		extractMax3(obj);
	}

	//This is NOT stable sort
	void HeapSortInPlace4(DataSet& obj)
	{
		heapify_BottomUp1_usingRecursion(obj);
		extractMax1_usingRecursion(obj);
	}

	//This is NOT stable sort
	void HeapSortInPlace5(DataSet& obj)
	{
		heapify_BottomUp1_withoutRecursion(obj);
		extractMax1_withoutRecursion(obj);
	}

	//This is stable sort
	void HeapSortInPlace6(DataSet& obj)
	{
		heapify_BottomUp1_withoutRecursion(obj);
		extractMax2(obj);
	}

	//This is NOT stable sort
	void HeapSortInPlace7(DataSet& obj)
	{
		heapify_BottomUp1_withoutRecursion(obj);
		extractMax3(obj);
	}

	//This is NOT stable sort
	void HeapSortInPlace8(DataSet& obj)
	{
		heapify_BottomUp2(obj);
		extractMax1_withoutRecursion(obj);
	}

	//This is stable sort
	void HeapSortInPlace9(DataSet& obj)
	{
		heapify_BottomUp2(obj);
		extractMax2(obj);
	}

	//This is NOT stable sort
	void HeapSortInPlace10(DataSet& obj)
	{
		heapify_BottomUp2(obj);
		extractMax3(obj);
	}

	//This is stable sort
	void HeapSortInPlace11(DataSet& obj)
	{
		heapify_BottomUp3(obj);
		extractMax2(obj);
	}

	//This is stable sort
	void HeapSortInPlace12(DataSet& obj)
	{
		heapify_BottomUp4(obj);
		extractMax2(obj);
	}

	//This is stable sort
	void HeapSortInPlace13(DataSet& obj)
	{
		heapify_BottomUp5(obj);
		extractMax2(obj);
	}

	//This is stable sort
	void HeapSortInPlace14(DataSet& obj)
	{
		heapify_BottomUp6(obj);
		extractMax2(obj);
	}

}