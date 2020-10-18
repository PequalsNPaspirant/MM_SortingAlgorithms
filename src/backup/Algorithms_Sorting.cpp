//Goal:
//Try various sorting algorithms
//Implement performance measuring techniques to measure time, number of comparisons, number of swaps/assignments
//Use fixed size arrays of objects to avoid performance impact due to allocation and deallocation

//TODO:
// Done: Add a function to check whether it is stable sort or not
// Collect all statistics in vector and plot a graph

#include <iostream>
#include <vector>
#include <string>
#include <sstream> //for std::stringstream

#include <chrono> //C++11
//using HRClock = std::chrono::high_resolution_clock;
#include <iomanip> //for setw(n)
#include <locale>
#include <string>
//#include <iostream>
//#include <iosfwd>
//#include <fstream>
#include <sstream> //for std::stringstream
#include <fstream> //for file read/write

#include <algorithm>    // std::random_shuffle
#include <list>
#include <queue>
#include <tuple>
#include <iterator>
#include <numeric> //For std::partial_sum
#include <queue>
#include <cmath>
using namespace std;

#include "Assert/MyAssert.h"
#include "Timer/Timer.h"
#include "Algorithms_Sorting/Algorithms_Sorting.h"
#include "my_math_lib/Permutations.h"

namespace mm {

//Enable this to debug
//#define DEBUG


//--------------------------------------------------------------------------------------------
// Global Configurtion
bool displayOnScreen = true;
const string reportLocation = "C:\\@_Programming\\";

bool writeToTextFile = true;
const string textFileName = "sortingPerfReport.txt";

bool writeToCSVDataSetsOnRows = false;
const string csvFileName_DataSetsOnRows = "sortingPerfReport_DataSetsOnRows.csv";

bool writeToCSVSortingAlgosOnRows = false;
const string csvFileName_SortingAlgosOnRows = "sortingPerfReport_SortingAlgosOnRows.csv";

bool writeToCSVForGraph = true;
const string csvFileName_ForGraph = "sortingPerfReport_ForGraph.csv";

//--------------------------------------------------------------------------------------------

//==================== class SingletonCounters

void SingletonCounters::resetCounters()
{
	SingletonCounters::get().m_comparisons = 0;
	SingletonCounters::get().m_swaps = 0;
	SingletonCounters::get().m_assignments = 0;
	SingletonCounters::get().m_arrayAccess = 0;
}
void SingletonCounters::incrementComparisons()
{
	SingletonCounters::get().m_comparisons++;
}
void SingletonCounters::incrementSwaps()
{
	SingletonCounters::get().m_swaps++;
}
void SingletonCounters::incrementAssignments()
{
	SingletonCounters::get().m_assignments++;
}
void SingletonCounters::incrementArrayAccess()
{
	SingletonCounters::get().m_arrayAccess++;
}
int SingletonCounters::getComparisons()
{
	return SingletonCounters::get().m_comparisons;
}
int SingletonCounters::getSwaps()
{
	return SingletonCounters::get().m_swaps;
}
int SingletonCounters::getAssignments()
{
	return SingletonCounters::get().m_assignments;
}
int SingletonCounters::getArrayAccess()
{
	return SingletonCounters::get().m_arrayAccess;
}

SingletonCounters& SingletonCounters::get()
{
	static SingletonCounters ctr;
	return ctr;
}


//================class Object

Object::Object(int n /*= 0*/)
		:m_val(n), m_originalPosition(0)
	{}

Object::Object(const Object& rhs)
	:m_val(rhs.m_val),
	m_originalPosition(rhs.m_originalPosition)
{
	//Update the counter
	SingletonCounters::incrementAssignments();
}

const Object& Object::operator=(const Object& rhs)
{
	m_val = rhs.m_val;
	m_originalPosition = rhs.m_originalPosition;
	//Update the counter
	SingletonCounters::incrementAssignments();
	return *this;
}

//bool Object::operator>(const Object& rhs)
//{
//	//Update the counter
//	SingletonCounters::incrementComparisons();
//	return m_val > rhs.m_val;
//}

bool Object::operator<(const Object& rhs) const
{
	//Update the counter
	SingletonCounters::incrementComparisons();
	return m_val < rhs.m_val;
}

bool Object::operator==(const Object& rhs)
{
	//Update the counter
	SingletonCounters::incrementComparisons();
	return m_val == rhs.m_val;
}

bool Object::operator<=(const Object& rhs)
{
	return (*this < rhs) || (*this == rhs);
}

void Object::swap(Object& rhs)
{
	SingletonCounters::incrementSwaps();
	Object temp(rhs);
	rhs = (*this);
	*this = temp;
}

//Object::operator int()
//{
//	return m_val;
//}

int Object::getVal() const
{
	return m_val;
}

void Object::setVal(int val)
{
	m_val = val;
}

unsigned int Object::getOriginalPosition() const
{
	return m_originalPosition;
}

void Object::setOriginalPosition(unsigned int pos)
{
	m_originalPosition = pos;
}


//===============class DataSet

DataSet::DataSet(string name, const unsigned int size /*= 0*/)
	:m_dataSetName(name), m_data(nullptr), m_size(size)
{
	if (size > 0)
	{
		m_data = new Object[m_size];
		setOriginalPositions();
	}
}

DataSet::DataSet(string name, initializer_list<int> list)
	:m_dataSetName(name), m_data(nullptr), m_size(list.size())
{
	if (m_size > 0)
	{
		m_data = new Object[m_size];
		setOriginalPositions();
	}

	const int* begining = list.begin();
	for (size_t i = 0; i < m_size; i++)
	{
		m_data[i] = *begining;
		begining++;
	}
}

DataSet::DataSet(string name, vector<int> vec)
	:m_dataSetName(name), m_data(nullptr), m_size(vec.size())
{
	if (m_size > 0)
	{
		m_data = new Object[m_size];
		setOriginalPositions();
	}

	for (size_t i = 0; i < m_size; i++)
		m_data[i] = vec[i];
}

DataSet::~DataSet()
{
	delete[] m_data;
}

//Transfer ownership
DataSet::DataSet(const DataSet& obj)
{
	m_dataSetName = obj.m_dataSetName;
	m_size = obj.m_size;
	m_data = obj.m_data;

	DataSet& nonConstObj = const_cast<DataSet&>(obj);
	nonConstObj.m_size = 0;
	nonConstObj.m_data = nullptr;
	nonConstObj.m_dataSetName.clear();
}

//Transfer ownership
DataSet DataSet::operator=(const DataSet& obj)
{
	if (m_size > 0)
	{
		delete[] m_data;
	}

	m_dataSetName = obj.m_dataSetName;
	m_size = obj.m_size;
	m_data = obj.m_data;

	DataSet& nonConstObj = const_cast<DataSet&>(obj);
	nonConstObj.m_size = 0;
	nonConstObj.m_data = nullptr;
	nonConstObj.m_dataSetName.clear();

	return *this;
}

DataSet DataSet::getCopy()
{
	DataSet copy(m_dataSetName);
	copy.m_size = m_size;
	copy.m_data = new Object[m_size];
	for (size_t i = 0; i < m_size; i++)
		copy.m_data[i] = m_data[i];

	return copy;
}

DataSet DataSet::getCopy(int start, int end)
{
	DataSet copy(m_dataSetName);
	copy.m_size = end - start + 1;
	copy.m_data = new Object[m_size];
	int index = 0;
	for (int i = start; i <= end; i++)
		copy.m_data[index++] = m_data[i];

	return copy;
}

void DataSet::setSize(const unsigned int size)
{
	if (m_size == 0)
	{
		m_size = size;
		m_data = new Object[m_size];
		setOriginalPositions();
	}
	else
		MyAssert::myRunTimeAssert(false, "Size is already set");
}
const unsigned int DataSet::getSize() const { return m_size; }

Object& DataSet::operator[](const unsigned int index)
{
	SingletonCounters::incrementArrayAccess();
	MyAssert::myRunTimeAssert(index < m_size, "Size overflow");
	return m_data[index];
}

const Object& DataSet::operator[](const unsigned int index) const
{
	SingletonCounters::incrementArrayAccess();
	MyAssert::myRunTimeAssert(index < m_size, "Size overflow");
	return m_data[index];
}

const string& DataSet::getName() const
{
	return m_dataSetName;
}

void DataSet::printSet() const
{
	getBuffer(cout);
}

string DataSet::getSetString() const
{
	std::stringstream buffer;
	getBuffer(buffer);
	return buffer.str();
}

void DataSet::getBuffer(std::ostream& base) const
{
	base << "\n\n" << m_dataSetName << " (size = " << m_size << "). Data: ";
	for (size_t i = 0; i < m_size; i++)
		base << m_data[i].getVal() << ((i < m_size - 1) ? ", " : "");
}

string DataSet::getSetStringForCSV() const
{
	string retVal(m_dataSetName);
	retVal += ",\"";
	for (size_t i = 0; i < m_size; i++)
		retVal += (to_string(m_data[i].getVal()) + ((i < m_size) ? ", " : ""));
	retVal += "\"";
	return retVal;
}

void DataSet::setOriginalPositions()
{
	for (size_t i = 0; i < m_size; i++)
		m_data[i].setOriginalPosition(i);
}


//=============================================================================================================
//	Sortign Algorithms - START

//=======================+=============+
//                       | Bubble Sort |
//=======================+=============+

// Bubble Sort - trial version 1
//=======================================================================================

//Stable sort
void bubbleSort_t1(DataSet& obj)
{
	int size = obj.getSize();
	for (int countOfElementsToBeSorted = size; countOfElementsToBeSorted > 0; countOfElementsToBeSorted--)
	{
		bool nothingSwappedInLastIteration = true;
		for (int j = 1; j < countOfElementsToBeSorted; j++)
		{
			if (obj[j] < obj[j - 1])
			{
				obj[j - 1].swap(obj[j]);
				nothingSwappedInLastIteration = false;
			}
		}
		if (nothingSwappedInLastIteration)
			break;
	}
}

// Bubble Sort - 1
//=======================================================================================

//Stable sort
//Optimizes the next iteration. Keeps track of last swap happened in last iteration. No comparison required after this position.
void bubbleSort_1(DataSet& obj)
{
	int size = obj.getSize();
	int newSize = size;
	while (newSize > 0)
	{
		int sizeAfterThisIteration = 0;
		for (int j = 1; j < newSize; j++)
		{
			if (obj[j] < obj[j - 1])
			{
				obj[j - 1].swap(obj[j]);
				sizeAfterThisIteration = j;
			}
		}
		newSize = sizeAfterThisIteration;
	}
}



//=======================+================+
//                       | Selection Sort |
//=======================+================+

// Selection Sort - Trial Version 1
//=======================================================================================

//NOT Stable sort
void SelectionSort_t1(DataSet& obj)
{
	int size = obj.getSize();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (obj[j] < obj[i])
				obj[i].swap(obj[j]);
		}
	}
}

// Selection Sort - 1
//=======================================================================================

//NOT Stable sort
void SelectionSort_1(DataSet& obj)
{
	int size = obj.getSize();
	for (int i = 0; i < size - 1; i++)
	{
		int iMin = i;
		for (int j = i + 1; j < size; j++)
		{
			if (obj[j] < obj[iMin])
				iMin = j;
		}
		if (i != iMin)
			obj[i].swap(obj[iMin]);
	}
}

//=======================+================+
//                       | Insertion Sort |
//=======================+================+

// Insertion Sort - Trial Version 1
//=======================================================================================

//Stable sort
void InsertionSort_t1(DataSet& obj)
{
	int size = obj.getSize();
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (obj[j] < obj[j - 1])
				obj[j].swap(obj[j - 1]);
			else
				break;
		}
	}
}

// Insertion Sort - Trial Version 2
//=======================================================================================

//Stable sort
//This is slightly faster than above
void InsertionSort_t2(DataSet& obj)
{
	int size = obj.getSize();
	for (int i = 1; i < size; i++)
	{
		Object temp = obj[i];
		int j;
		for (j = i; j > 0; j--)
		{
			if (temp < obj[j - 1])
				obj[j] = (obj[j - 1]);
			else
				break;
		}
		if (i != j)
			obj[j] = temp;
	}
}

// Insertion Sort - Trial Version 3
//=======================================================================================

//Stable sort
//This is slightly faster than above. Some silly effort to save initial assignment temp = obj[i];
void InsertionSort_t3(DataSet& obj)
{
	int size = obj.getSize();
	for (int i = 1; i < size; i++)
	{
		if (obj[i] < obj[i - 1])
		{
			Object temp = obj[i];
			obj[i] = obj[i - 1];
			int j;
			for (j = i - 1; j > 0; j--)
			{
				if (temp < obj[j - 1])
					obj[j] = (obj[j - 1]);
				else
					break;
			}
			if (i != j)
				obj[j] = temp;
		}
	}
}

// Insertion Sort - Trial Version 4
//=======================================================================================

//Stable sort
//Different implementation. Go on comparing adjusant elements. Iterate backwards when conflict is found. 
void InsertionSort_t4(DataSet& obj)
{
	int size = obj.getSize();
	int newSize = size;
	for (int i = 1; i < newSize; i++)
	{
		if (obj[i] < obj[i - 1])
		{
			obj[i].swap(obj[i - 1]);
			for (int j = i - 1; j > 0 && obj[j] < obj[j - 1]; j--)
				obj[j].swap(obj[j - 1]);
		}
	}
}

// Insertion Sort - Trial Version 5
//=======================================================================================

//Stable sort
//Binary insertion sort
//Do binary search to reduce comparisons.
void InsertionSort_t5(DataSet& obj)
{
	int size = obj.getSize();
	for (int current = 1; current < size; current++)
	{
		int left = 0;
		int right = current - 1;
		int targetPos = current;

		if (!(obj[current] < obj[right]))  // OR if (obj[right] <= obj[current])
		{
			continue;
		}
		else if (obj[current] < obj[left])
		{
			targetPos = left;
		}
		else
		{
			while ((right - left) > 1)
			{
				int mid = (left + right) / 2;
				if (obj[current] < obj[mid])
					right = mid;
				else //if (obj[mid] <= obj[current])
					left = mid;
			}
			targetPos = right;
		}

		if (current != targetPos)
		{
			Object temp = obj[current];
			for (int j = current; j > targetPos; j--)
				obj[j] = obj[j - 1];
			obj[targetPos] = temp;
		}
	}
}

// Insertion Sort - 1
//=======================================================================================

//Stable sort
//Binary insertion sort
//Do binary search more effectively than above algo.
void InsertionSort_1(DataSet& obj)
{
	int size = obj.getSize();
	for (int current = 1; current < size; current++)
	{
		int left = 0;
		int right = current;

		while (left < right)
		{
			int mid = (left + right) / 2;
			if (obj[current] < obj[mid])
				right = mid;
			else //if (obj[mid] >= obj[current])
				left = mid + 1;
		}
		int targetPos = right;

		if (current != targetPos)
		{
			Object temp = obj[current];
			for (int j = current; j > targetPos; j--)
				obj[j] = obj[j - 1];
			obj[targetPos] = temp;
		}
	}
}

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

		if(currentLeft < leftWall) currentLeft = leftWall;
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
	
	if(obj[rightPivotIndex] < obj[leftPivotIndex])
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

	if(leftPivotIndex != leftWall)
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
				PivotIndices[i] = startIndex + (endIndex - startIndex) / ( numberOfPivots - 1);
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
		DataSet set("Temp", PivotIndices.size());
		for (size_t i = 0; i < PivotIndices.size(); i++)
			set[i] = obj[PivotIndices[i]];

		QuickSortMultiPivot_2Pivots(set);
		for (size_t i = 0; i < PivotIndices.size(); i++)
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
		const Object leftPivotObj = obj[ PivotIndices[i] ];
		const Object rightPivotObj = obj[ PivotIndices[numberOfPivots - i - 1] ];
		
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

	int numberOfWalls = walls.size();

	int i = 0;
	for (; i < numberOfWalls/2; i++)
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
		if(pair.left < (partition - 1))
			stack.push_back(pairOfBounds(pair.left, partition - 1));
		if ((partition + 1) < pair.right)
			stack.push_back(pairOfBounds(partition + 1, pair.right));
	}
}

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
				if(!firstSetOver)
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
		for(int firstSetStart = 0; firstSetStart < size; firstSetStart += (2 * sizeOfSet))
		{
			int secondSetStart = min(firstSetStart + sizeOfSet, size - 1);
			int end = min(secondSetStart + sizeOfSet - 1, size - 1);
			//Do not do merging again on last set if
			//		1. it contains only one element
			//		2. at end there is just one set left from previous iteration i.e. no second set present for merging 
			//Need to toggle array here, so can not add above optimization #2
			if (firstSetStart == end /*|| (end - firstSetStart + 1) <= sizeOfSet*/)
				continue;
			if(noToggle)
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
				if(k != counterSecondSet)
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
	while(runBoundaries.size() > 1)
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

//=======================+============+
//                       | Radix Sort |
//=======================+============+

// ---------------------- LSD -----------------------------------------------------------
/*
If w is width (number of digits in a NUMBER or number of letter in STRING), n are total object to be sorted,
then the time complexity is O(w * n). 
	Note:	Here the time complexity os radix sort is not in terms of comparisons. There is no comparison happens in radix sort.
			The w * n is equal to the number of times the elements of collection are accessed.
The best comparison sort can sort objects in O(n * log2 n)
So, radix sort is better than comparison sort only if 
	w < log2 n
	But w = logb(max object)
base for above equation is b
i.e. to do radix sort more effectively than comparison sort => 
	logb(max object) < log2 n
Since base, n and max object are positive real numbers, if we raise b to the power equal to LHS & RHS, then
	b ^ logb(max object) < b ^ log2 n
As we know b ^ logb(X) = X
	max object < b ^ (log2 n)
	pow(max object, 1/(log2 n)) < b
	b > pow(max object, 1/(log2 n))

Thus, choose a base of system such that it is more than pow(max object, 1/(log2 n))

Example:
	When n = 100, and max object is 500, then
	log2(100) = 6.6439
	1 / log2(100) = 1 / 6.6439 = 0.1505
	pow(500, 0.1505) = 2.5482
	Thus base should be more than 2.5482
Tally:
When base = 2.5482
	w = logb(max object)
	w = log2.548(500)
	w = 6.6439
	min radix sort time complexity = O(w * n) = O(6.6439 * 100) = O(664.39)
	Optimum comparison sort time complexity = O(100 * log2(100)) = O(100 * 6.6439) = O(664.39)

The time complexity of radix sort can approach O(n) when w approaches 1
Lets repsent it as 
	w --> 1
	logb(max object) --> 1
This can happen in 2 situation
First situation
	max object can be zero
Second situation
	b --> max object

Moral of story is
	Choose the base as close as max object

This is same as doing counting sort of objects over range from 1 to max object, each object represents unique digit/place in NUMBER SYSTEM REPRESENTATION
w will be 1 in this case, so there is no need to do second iteration, as second digit will not be present in this SYSTEM with base = max number
*/

// Radix Sort LSD - Trial Version 1
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void CountSort_t1(DataSet& obj, int base, int LSDPosition)
{
	int size = obj.getSize();
	int currentPositionVal = pow(base, LSDPosition);		
	std::vector<int> count(base, 0);
	// Store count of occurrences in count[]
	for (int i = 0; i < size; i++)
	{
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		count[currentDigit]++;
	}

	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	for (int i = 1; i < base; i++)
		count[i] += count[i - 1];

	// Build the output array
	DataSet copy(obj.getCopy());
	for (int i = size - 1; i >= 0; i--)
	{
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		copy[count[currentDigit] - 1] = obj[i];
		count[currentDigit]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (int i = 0; i < size; i++)
		obj[i] = copy[i];

}

void RadixSortLSD_t1(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	if (max == 100)
	{
		int breakpoint = 0; ++breakpoint;
	}

	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
	{
		CountSort_t1(obj, base, LSDPosition);
	}
}

// Radix Sort LSD - Trial Version 2
//It is same as above, except it uses std::partial_sum()
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void CountSort_t2(DataSet& obj, int base, int LSDPosition)
{
	int size = obj.getSize();
	int currentPositionVal = pow(base, LSDPosition);
	std::vector<int> count(base, 0);
	// Store count of occurrences in count[]
	for (int i = 0; i < size; i++)
	{
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		count[currentDigit]++;
	}

	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	//for (int i = 1; i < base; i++)
	//	count[i] += count[i - 1];
	std::partial_sum(count.begin(), count.end(), count.begin());

	// Build the output array
	DataSet copy(obj.getCopy());
	for (int i = size - 1; i >= 0; i--)
	{
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		copy[count[currentDigit] - 1] = obj[i];
		count[currentDigit]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (int i = 0; i < size; i++)
		obj[i] = copy[i];

}

void RadixSortLSD_t2(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
	{
		CountSort_t2(obj, base, LSDPosition);
	}
}

// This is best version of LSD
// Radix Sort LSD - Version 1
//It is same as Trial Version 2, except it avoid copying the temp array back into original array, rather it alternatively uses each array as temp array
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void CountSort_1(DataSet& input, int base, int LSDPosition, DataSet& output)
{
	int size = input.getSize();
	int currentPositionVal = pow(base, LSDPosition);
	std::vector<int> count(base, 0);
	// Store count of occurrences in count[]
	for (int i = 0; i < size; i++)
	{
		int currentDigit = (input[i].getVal() / currentPositionVal) % base;
		count[currentDigit]++;
	}

	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	std::partial_sum(count.begin(), count.end(), count.begin());

	// Build the output array
	for (int i = size - 1; i >= 0; i--)
	{
		int currentDigit = (input[i].getVal() / currentPositionVal) % base;
		output[ --count[currentDigit] ] = input[i];
	}
}

void RadixSortLSD_1(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	DataSet copy(obj.getCopy());
	bool toggle = (maxDigits % 2 == 0);
	for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
	{
		if(toggle)
			CountSort_1(obj, base, LSDPosition, copy);
		else
			CountSort_1(copy, base, LSDPosition, obj);
		toggle = !toggle;
	}
}

// Radix Sort LSD - Trial Version 3
// It is same as Version 1, except it does not use std::partial_sum() and 
// it stores the start position of each object having particular digit at LSDPosition. This exactly same as what is done in Counting Sort
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void CountSort_t3(DataSet& input, int base, int LSDPosition, DataSet& output)
{
	int size = input.getSize();
	int currentPositionVal = pow(base, LSDPosition);
	std::vector<int> count(base, 0);
	// Store count of occurrences in count[]
	for (int i = 0; i < size; i++)
	{
		int currentDigit = (input[i].getVal() / currentPositionVal) % base;
		count[currentDigit]++;
	}

	// Change count[i] so that count[i] now contains actual start
	// position of this digit in output[]
	int lastCount = count[0];
	count[0] = 0;
	for (int i = 1; i < base; i++)
	{
		int currentCountBackup = count[i];
		count[i] = count[i - 1] + lastCount;
		lastCount = currentCountBackup;
	}

	// Build the output array
	for (int i = 0; i < size; i++)
	{
		int currentDigit = (input[i].getVal() / currentPositionVal) % base;
		output[ count[currentDigit]++ ] = input[i];
	}
}

void RadixSortLSD_t3(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	DataSet copy(obj.getCopy());
	bool toggle = (maxDigits % 2 == 0);
	for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
	{
		if (toggle)
			CountSort_t3(obj, base, LSDPosition, copy);
		else
			CountSort_t3(copy, base, LSDPosition, obj);
		toggle = !toggle;
	}
}

// Radix Sort LSD - Trial Version 3 - Stable in-place LSD radix sort
// It is same as MSD Version 1. It does not use O(n) space, it does swapping in-place
// THIS IS NOT POSSIBLE AND IT DOES NOT WORK as the inner swapping loop produces unstable order of objects and LSD needs stable ordering
//=======================================================================================

void RadixSortLSD_t4_doesNotWork(DataSet& obj, int base, int LSDPosition)
{
	int currentPositionVal = pow(base, LSDPosition);

	// count digits
	int size = obj.getSize();
	std::vector<int> count(base, 0);

	for (int i = 0; i < size; ++i)
	{
		int currentDigit = obj[i].getVal() / currentPositionVal % base;
		count[currentDigit]++;
	}

	// inclusive prefix sum
	vector<int> bucket(base, 0);
	std::partial_sum(count.begin(), count.end(), bucket.begin());

	// reorder items in-place by walking cycles
#ifdef DEBUG
	int countLoop = 0;
#endif

	for (int i = 0; i < size; )
	{
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		int position = --bucket[currentDigit];
		while ((position) > i)
		{
#ifdef DEBUG
			++countLoop;
#endif
			obj[i].swap(obj[position]);
			currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			position = --bucket[currentDigit];
		}

#ifdef DEBUG
		++countLoop;
#endif

		i += count[currentDigit];
	}

#ifdef DEBUG
	if (countLoop > (hi - lo))
		cout << "\n\n---------------------RadixSortMSD_t2 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif
}

void RadixSortLSD_t4_doesNotWork(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
	{
		RadixSortLSD_t4_doesNotWork(obj, base, LSDPosition);
	}
}

// Radix Sort LSD - Trial Version 3
// It is same as Version 1, except it uses queue instead of temp array
// This is not more efficient, but very simple to implement
//=======================================================================================

void RadixSortLSD_t4(DataSet& obj, int base, int LSDPosition)
{
	int size = obj.getSize();
	int currentPositionVal = pow(base, LSDPosition);

	std::queue<Object>* buckets = new std::queue<Object>[base];
	// Store count of occurrences in count[]
	for (int i = 0; i < size; i++)
	{
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		buckets[currentDigit].push(obj[i]);
	}

	int counter = 0;
	for (int i = 0; i < base; i++)
	{
		while (!buckets[i].empty())
		{
			obj[counter++] = buckets[i].front();
			buckets[i].pop();
		}
	}

	MyAssert::myRunTimeAssert(counter == size, "Size mismatch");

	delete[] buckets;
}

void RadixSortLSD_t4(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	for (unsigned int LSDPosition = 0; LSDPosition < maxDigits; ++LSDPosition)
	{
		RadixSortLSD_t4(obj, base, LSDPosition);
	}
}

//==================================== MSD ===========================================================================================

// Radix Sort MSD - Trial Version 1
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void RadixSortMSD_t1(DataSet& obj, int base, int lo, int hi, int MSDPosition)
{
	int currentPositionVal = pow(base, MSDPosition);

	// count digits
	std::vector<int> count(base, 0);

	for (int i = lo; i <= hi; ++i)
	{
		int currentDigit = obj[i].getVal() / currentPositionVal % base;
		count[currentDigit]++;
	}

	// inclusive prefix sum
	vector<int> bucket(base, 0);
	std::partial_sum(count.begin(), count.end(), bucket.begin());

	// reorder items in-place by walking cycles
#ifdef DEBUG
	int countLoop = 0;
#endif

	for (int i = 0, j; i <= (hi - lo); )
	{
		int currentDigit = (obj[lo + i].getVal() / currentPositionVal) % base;
		while ((j = --bucket[currentDigit]) > i)
		{
#ifdef DEBUG
			++countLoop;
#endif
			obj[lo + i].swap(obj[lo + j]);
			currentDigit = (obj[lo + i].getVal() / currentPositionVal) % base;
		}

#ifdef DEBUG
		++countLoop;
#endif

		i += count[currentDigit];
	}

#ifdef DEBUG
	if (countLoop > (hi - lo))
		cout << "\n\n---------------------RadixSortMSD_t1 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif

	// no more depth to sort?
	if (MSDPosition == 0) return;

	// recurse on buckets
	int position = lo;
	for (int i = 0; i < base; ++i)
	{
		if (count[i] > 1)
			RadixSortMSD_t1(obj, base, position, position + count[i] - 1, MSDPosition - 1);
		position += count[i];
	}
}

void RadixSortMSD_t1(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	RadixSortMSD_t1(obj, base, 0, size - 1, maxDigits - 1);
}


// Radix Sort MSD - Trial Version 2
// It is same as version 1, except the loop is from lo to hi
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void RadixSortMSD_t2(DataSet& obj, int base, int lo, int hi, int MSDPosition)
{
	int currentPositionVal = pow(base, MSDPosition);

	// count digits
	std::vector<int> count(base, 0);

	for (int i = lo; i <= hi; ++i)
	{
		int currentDigit = obj[i].getVal() / currentPositionVal % base;
		count[currentDigit]++;
	}

	// inclusive prefix sum
	vector<int> bucket(base, 0);
	std::partial_sum(count.begin(), count.end(), bucket.begin());

	std::vector<int> countTemp(count);

#ifdef DEBUG
	int countLoop = 0;
#endif

	for (int i = lo; i <= hi;)
	{
#ifdef DEBUG
		++countLoop;
#endif

		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		int position = --bucket[currentDigit] + lo;
		if (--countTemp[currentDigit] >= 0 && i != position)
			obj[position].swap(obj[i]);
		else
			i += count[currentDigit];
	}

#ifdef DEBUG
	if (countLoop > (hi - lo))
		cout << "\n\n---------------------RadixSortMSD_t3 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif

	// no more depth to sort?
	if (MSDPosition == 0) return;

	// recurse on buckets
	int position = lo;
	for (int i = 0; i < base; ++i)
	{
		if (count[i] > 1)
			RadixSortMSD_t2(obj, base, position, position + count[i] - 1, MSDPosition - 1);
		position += count[i];
	}
}

void RadixSortMSD_t2(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	RadixSortMSD_t2(obj, base, 0, size - 1, maxDigits - 1);
}

// Radix Sort MSD - Trial Version 3
// This is NOT Stable sort
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void RadixSortMSD_t3(DataSet& obj, int base, int lo, int hi, int MSDPosition)
{
	int currentPositionVal = pow(base, MSDPosition);

	// count digits
	std::vector<int> count(base, 0);

	for (int i = lo; i <= hi; ++i)
	{
		int currentDigit = obj[i].getVal() / currentPositionVal % base;
		count[currentDigit]++;
	}

	// inclusive prefix sum
	vector<int> bucket(base, 0);
	std::partial_sum(count.begin(), count.end(), bucket.begin());

	std::vector<int> countTemp(count);

#ifdef DEBUG
	int countLoop = 0;
#endif

	for (int i = hi; i >= lo;)
	{
#ifdef DEBUG
		++countLoop;
#endif
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		int position = --bucket[currentDigit] + lo;
		if (--countTemp[currentDigit] >= 0 && i != position)
			obj[position].swap(obj[i]);
		else
			--i;
	}

#ifdef DEBUG
	if (countLoop > (hi - lo))
		cout << "\n\n---------------------RadixSortMSD_t4 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif

	// no more depth to sort?
	if (MSDPosition == 0) return;

	// recurse on buckets
	int position = lo;
	for (int i = 0; i < base; ++i)
	{
		if (count[i] > 1)
			RadixSortMSD_t3(obj, base, position, position + count[i] - 1, MSDPosition - 1);
		position += count[i];
	}
}

void RadixSortMSD_t3(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	RadixSortMSD_t3(obj, base, 0, size - 1, maxDigits - 1);
}

// This is the best version
// Radix Sort MSD - Version 1
// It is same as Trial Version 1, except it uses loop from lo to hi inseat of i = 0 to i < (hi - lo)
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void RadixSortMSD_1(DataSet& obj, int base, int lo, int hi, int MSDPosition)
{
	int currentPositionVal = pow(base, MSDPosition);

	// count digits
	std::vector<int> count(base, 0);

	for (int i = lo; i <= hi; ++i)
	{
		int currentDigit = obj[i].getVal() / currentPositionVal % base;
		count[currentDigit]++;
	}

	// inclusive prefix sum
	vector<int> bucket(base, 0);
	std::partial_sum(count.begin(), count.end(), bucket.begin());

	// reorder items in-place by walking cycles
#ifdef DEBUG
	int countLoop = 0;
#endif

	for (int i = lo; i <= hi; )
	{
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		int position = --bucket[currentDigit];
		while ((lo + position) > i)
		{
#ifdef DEBUG
			++countLoop;
#endif
			obj[i].swap(obj[lo + position]);
			currentDigit = (obj[i].getVal() / currentPositionVal) % base;
			position = --bucket[currentDigit];
		}

#ifdef DEBUG
		++countLoop;
#endif

		i += count[currentDigit];
	}

#ifdef DEBUG
	if (countLoop > (hi - lo))
		cout << "\n\n---------------------RadixSortMSD_t2 inefficient loop. count = " << countLoop << " (hi - lo) = " << (hi - lo) << "\n";
#endif

	// no more depth to sort?
	if (MSDPosition == 0) return;

	// recurse on buckets
	int position = lo;
	for (int i = 0; i < base; ++i)
	{
		if (count[i] > 1)
			RadixSortMSD_1(obj, base, position, position + count[i] - 1, MSDPosition - 1);
		position += count[i];
	}
}

void RadixSortMSD_1(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	RadixSortMSD_1(obj, base, 0, size - 1, maxDigits - 1);
}

// Radix Sort MSD - Trial Version 4
// stable MSD, with max O(n) extra space. It uses O(n) only for first iteration
// It is same as Version 1, except it uses extra space to sort each bucket
//=======================================================================================

void RadixSortMSD_t4(DataSet& obj, int base, int lo, int hi, int MSDPosition)
{
	int currentPositionVal = pow(base, MSDPosition);

	// count digits
	std::vector<int> count(base, 0);

	for (int i = lo; i <= hi; ++i)
	{
		int currentDigit = obj[i].getVal() / currentPositionVal % base;
		count[currentDigit]++;
	}

	// inclusive prefix sum
	vector<int> bucket(base, 0);
	std::partial_sum(count.begin(), count.end(), bucket.begin());

	DataSet copy("Copy", hi - lo + 1);
	for (int i = lo; i <= hi; i++)
		copy[i - lo] = obj[i];

	for (int i = hi; i >= lo; i--)
	{
		int currentDigit = (copy[i - lo].getVal() / currentPositionVal) % base;
		int position = --bucket[currentDigit];
		obj[lo + position] = copy[i - lo];
	}

	// no more depth to sort?
	if (MSDPosition == 0) return;

	// recurse on buckets
	int position = lo;
	for (int i = 0; i < base; ++i)
	{
		if (count[i] > 1)
			RadixSortMSD_t4(obj, base, position, position + count[i] - 1, MSDPosition - 1);
		position += count[i];
	}
}

void RadixSortMSD_t4(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	RadixSortMSD_t4(obj, base, 0, size - 1, maxDigits - 1);
}

// Radix Sort MSD - Trial Version 5
// It is same as LSD Trial Version 3. It uses queue for MSD.
// This is not more efficient, but very simple to implement
//=======================================================================================

void RadixSortMSD_t5(DataSet& obj, int base, int lo, int hi, int MSDPosition)
{
	//int size = obj.getSize();
	int currentPositionVal = pow(base, MSDPosition);

	std::queue<Object>* buckets = new std::queue<Object>[base];
	// Store count of occurrences in count[]
	for (int i = lo; i <= hi; i++)
	{
		int currentDigit = (obj[i].getVal() / currentPositionVal) % base;
		buckets[currentDigit].push(obj[i]);
	}

	// count digits
	std::vector<int> count(base, 0);
	int counter = lo;
	for (int i = 0; i < base; i++)
	{
		//Store bucket count before emptying it
		count[i] = buckets[i].size();
		while (!buckets[i].empty())
		{
			obj[counter++] = buckets[i].front();
			buckets[i].pop();
		}
	}

	MyAssert::myRunTimeAssert(counter == hi + 1, "Size mismatch");

	delete[] buckets;

	// no more depth to sort?
	if (MSDPosition == 0) return;

	// recurse on buckets
	int position = lo;
	for (int i = 0; i < base; ++i)
	{
		if (count[i] > 1)
			RadixSortMSD_t5(obj, base, position, position + count[i] - 1, MSDPosition - 1);
		position += count[i];
	}
}

void RadixSortMSD_t5(DataSet& obj)
{
	int size = obj.getSize();
	const unsigned int base = 10;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (Object(max) < obj[i])
			max = obj[i].getVal();
	}
	const unsigned int maxDigits = ceil(log(max + 1) / log(base));
	RadixSortMSD_t5(obj, base, 0, size - 1, maxDigits - 1);
}


//=======================+===============+
//                       | Counting Sort |
//=======================+===============+
/*
Time Complexity: O(n+k) where n is the number of elements in input array and k is the range of input.
Auxiliary Space: O(n+k)

Points to be noted:
1. Counting sort is efficient if the range of input data is not significantly greater than the number of objects to be sorted. Consider the situation where the input sequence is between range 1 to 10K and the data is 10, 5, 10K, 5K.
2. It is not a comparison based sorting. It running time complexity is O(n) with space proportional to the range of data.
3. It is often used as a sub-routine to another sorting algorithm like radix sort.
4. Counting sort uses a partial hashing to count the occurrence of the data object in O(1).
5. Counting sort can be extended to work for negative inputs also.

Exercise:
1. Modify above code to sort the input data in the range from M to N.
2. Modify above code to sort negative input data.
3. Is counting sort stable and online?
4. Thoughts on parallelizing the counting sort algorithm.
*/

int CountingSort_1_calculateKey(const Object& element, int min)
{
	return element.getVal() - min;
}

void CountingSort_1(DataSet& obj)
{
	int size = obj.getSize();
	int min = obj[0].getVal();
	int max = min;
	for (int i = 0; i < size; i++)
	{
		int current = obj[i].getVal();
		if (min > current)
			min = current;
		else if (max < current)
			max = current;
	}
	//Its single repeated number set
	if (min == max) return;

	// count digits
	int keyCount = max - min + 1;
	MyAssert::myRunTimeAssert(keyCount < 1024, "Count too large");
	std::vector<int> count(keyCount, 0);

	for (int i = 0; i < size; i++)
	{
		int key = CountingSort_1_calculateKey(obj[i], min); // Key calculating function
		count[key]++;
	}

	// position of this digit in output[]
	int lastCount = count[0];
	count[0] = 0;
	for (int i = 1; i < keyCount; i++)
	{
		int currentCountBackup = count[i];
		count[i] = count[i - 1] + lastCount;
		lastCount = currentCountBackup;
	}

	// Build the array
	DataSet copy(obj.getCopy());
	for (int i = 0; i < size; i++)
	{
		int key = copy[i].getVal() - min;
		obj[ count[key]++ ] = copy[i];
	}
}

//=======================+============+
//                       | Bucket Sort / Bin Sort - Generic Bucket Sort |
//=======================+============+
/*
https://en.wikipedia.org/wiki/Bucket_sort

Keys are placed into each subarray/bucket using insertion sort so that they will be in sorted order in each bucket.

Optimizations:
A common optimization is to put the unsorted elements of the buckets back in the original array first,
then run insertion sort over the complete array; because insertion sort's runtime is based on how far each element is from its final position,
the number of comparisons remains relatively small, and the memory hierarchy is better exploited by storing the list contiguously in memory.
*/

int GenericBucketSort_1_calculateKey(const Object& element, int min, int max, int bucketCount)
{
	double bucketWidth = double(max - min) / (bucketCount - 1); //min and max can be any number. This sort can be used for any kind of object
	return floor((element.getVal() - min) / bucketWidth);
}

void GenericBucketSort_1(DataSet& obj, int lo, int hi)
{
	//Handle end conditions
	if (hi <= lo) return;
	if(hi - lo == 1)
	{
		if (obj[hi] < obj[lo])
			obj[hi].swap(obj[lo]);
		return;
	}

	int size = hi - lo + 1;
	int min = obj[lo].getVal();
	int max = min;
	for (int i = lo; i <= hi; i++)
	{
		int current = obj[i].getVal();
		if (min > current)
			min = current;
		else if (max < current)
			max = current;
	}
	//Its single repeated number set
	if (min == max) return;

	// count bucket size
	int bucketCount = size;
	std::vector<int> buckets(bucketCount, 0);

	for (int i = lo; i <= hi; i++)
	{
		int key = GenericBucketSort_1_calculateKey(obj[i], min, max, bucketCount); // Key calculating function
		buckets[key]++;
	}

	//Rest of the process can be carried out in many ways
	//Using the same logic used for "bucket-sort-subalgorithm" in radix sort above
	// inclusive prefix sum
	vector<int> bucketCumulative(bucketCount, 0);
	std::partial_sum(buckets.begin(), buckets.end(), bucketCumulative.begin());

	// reorder items in-place by walking cycles
	for (int i = lo; i <= hi; )
	{
		int key = GenericBucketSort_1_calculateKey(obj[i], min, max, bucketCount);
		int position = --bucketCumulative[key];
		while ((lo + position) > i)
		{
			obj[i].swap(obj[lo + position]);
			key = GenericBucketSort_1_calculateKey(obj[i], min, max, bucketCount);
			position = --bucketCumulative[key];
		}
		i += buckets[key];
	}

	// recurse on buckets
	int position = lo;
	for (int i = 0; i < bucketCount; ++i)
	{
		if (buckets[i] > 1)
			GenericBucketSort_1(obj, position, position + buckets[i] - 1);
		position += buckets[i];
	}
}

void GenericBucketSort_1(DataSet& obj)
{
	int size = obj.getSize();
	GenericBucketSort_1(obj, 0, size - 1);
}

//=======================+============+
//                       | Bucket Sort - Proxmap Sort |
//=======================+============+
/*
The name is short for computing a "proximity map".
*/


//=======================+============+
//                       | Bucket Sort - Histogram Sort |
//=======================+============+


//=======================+============+
//                       | Bucket Sort - Postman's Sort |
//=======================+============+


//=======================+============+
//                       | Bucket Sort - Shuffle Sort |
//=======================+============+


//=======================+==================+
//                       | Block Merge Sort |
//=======================+==================+

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

//=======================+============+
//                       | Shell Sort |
//=======================+============+

// Shell Sort - common functions
//=======================================================================================

void InsertionSort_t1_modifiedToResuseForShellSort(DataSet& obj, const vector<int>& gapSequence)
{
	int size = obj.getSize();
	if (size == 1) return;
	int gapSeqSize = gapSequence.size();
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
	int gapSeqSize = gapSequence.size();
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
	for (int i = 1; gapSequence[i] < size ;)
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

//=======================+=============+
//                       | Smooth Sort |
//=======================+=============+

void SmoothSortInPlace(DataSet& obj)
{
	int size = obj.getSize();
	for (int i = 0; i < size - 1; i++)
	{

	}
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



//	Sortign Algorithms - END
//=============================================================================================================
/*
class Timer
{
public:
	Timer()
		:m_startTime(HRClock::now())
	{
	}

	void reset()
	{
		m_startTime = HRClock::now();
	}

	long long getDurationTillNow()
	{
		HRClock::time_point end_time = HRClock::now();
		std::chrono::nanoseconds time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - m_startTime);
		return time_span.count() / 1000; //Convert to microseconds tempororily
	}

	string getDurationStringTillNow()
	{
		long long duration = getDurationTillNow();
		std::stringstream ss;
		ss.imbue(std::locale(""));
		ss << std::fixed << duration;
		return ss.str();
	}

	~Timer()
	{
		//cout << "\nTime Duration: " << getDurationStringTillNow() << " nanoseconds";
	}

private:
	HRClock::time_point m_startTime;
};*/

//=================== class ComparingFactors

ComparingFactors::ComparingFactors()
		: m_isSorted(true),
		 m_overallPerformance(0),
		 m_comparisons(0),
		 m_assignments(0),
		 m_assignmentsBy3(0),
		 m_swaps(0),
		 m_arrayAccess(0),
		 m_duration(0),
		 m_isStable(true)
	{

	}

	void ComparingFactors::set(SortingFactorType type, int count)
	{
		switch (type)
		{
		case OverallPerformance:
			m_overallPerformance = count;
			break;
		case Comparisons:
			m_comparisons = count;
			break;
		case Swaps:
			m_swaps = count;
			break;
		case Assignments:
			m_assignments = count;
			break;
		case AssignmentsBy3:
			m_assignmentsBy3 = count;
			break;
		case ArrayAccess:
			m_arrayAccess = count;
			break;
		default:
			MyAssert::myRunTimeAssert(false, "Unknown ComparingFactors");
		}
	}

	void ComparingFactors::set(SortingFactorType type, long long duration)
	{
		m_duration = duration;
	}

	void ComparingFactors::set(SortingFactorType type, string str)
	{
		m_durationString = str;
	}

	void ComparingFactors::set(SortingFactorType type, bool val)
	{
		if (type == IsSorted)
			m_isSorted = val;
		else if (type == IsStable)
			m_isStable = val;
		else
			MyAssert::myRunTimeAssert(false, "Unknown ComparingFactors");
	}

	const string ComparingFactors::get(SortingFactorType type) const
	{
		switch (type)
		{
		case IsSorted:				return (m_isSorted ? "Sorted" : "NOT Sorted");
		case OverallPerformance:	return to_string(m_overallPerformance);
		case Comparisons:			return to_string(m_comparisons);
		case AssignmentsBy3:		return to_string(m_assignmentsBy3);
		case Assignments:			return to_string(m_assignments);
		case Swaps:					return to_string(m_swaps);
		case ArrayAccess:			return to_string(m_arrayAccess);
		case Duration:				return to_string(m_duration);
		case IsStable:				return (m_isStable ? "Stable" : "NOT Stable");
		default:					MyAssert::myRunTimeAssert(false, "Unknown ComparingFactors");
		}

		return "";
	}

	const string& ComparingFactors::name(SortingFactorType type) const
	{
		static const string sorted				= "Sorted";
		static const string notSorted			= "NOT Sorted";
		static const string overallPerformance	= "#TotalPerf:";
		static const string comparisons			= "#Comparisons:";
		static const string assignmentsBy3		= "#AssignBy3:";
		static const string assignments			= "#Assign:";
		static const string swaps				= "#Swaps:";
		static const string arrayAccess			= "#EleAccess:";
		static const string duration			= "Time:";
		static const string stable				= "Stable";
		static const string notStable			= "NOT Stable";
		static const string defaultRetValue		= "";

		switch (type)
		{
		case IsSorted:				return (m_isSorted ? sorted : notSorted);
		case OverallPerformance:	return overallPerformance;
		case Comparisons:			return comparisons;
		case AssignmentsBy3:		return assignmentsBy3;
		case Assignments:			return assignments;
		case Swaps:					return swaps;
		case ArrayAccess:			return arrayAccess;
		case Duration:				return duration;
		case IsStable:				return (m_isStable ? stable : notStable);
		default:					MyAssert::myRunTimeAssert(false, "Unknown ComparingFactors");
		}

		return defaultRetValue;
	}

	void ComparingFactors::printResults() const
	{
		getBuffer(cout);
	}

	string ComparingFactors::getResultsString() const
	{
		std::stringstream buffer;
		getBuffer(buffer);
		return buffer.str();
	}

	void ComparingFactors::getBuffer(std::ostream& base) const
	{
		int gap = 2;
		base 
			//<< setw(8) << name(IsSorted) << ", " //Every list is sorted for sure when we reach here
			<< setw(name(Comparisons).length() + gap)			<< name(Comparisons)			<< setw(6) << m_comparisons			//<< ","
			<< setw(name(AssignmentsBy3).length() + gap)		<< name(AssignmentsBy3)			<< setw(6) << m_assignmentsBy3		//<< ","
			<< setw(name(Assignments).length() + gap)			<< name(Assignments)			<< setw(6) << m_assignments			//<< ","
			<< setw(name(Swaps).length() + gap)					<< name(Swaps)					<< setw(6) << m_swaps				//<< ","
			<< setw(name(ArrayAccess).length() + gap)			<< name(ArrayAccess)			<< setw(6) << m_arrayAccess			//<< ","
			<< setw(name(OverallPerformance).length() + gap)	<< name(OverallPerformance)		<< setw(6) << m_overallPerformance	//<< ","
			<< setw(name(Duration).length() + gap)				<< name(Duration)				<< setw(6) << m_duration			<< " ms"
			<< setw(13) << name(IsStable);
	}

	string ComparingFactors::getColumnTitlesForCSV(const string& algoName)
	{
		return algoName + "-" + name(OverallPerformance) + ","
			+ algoName + "-" + name(Comparisons) + ","
			+ algoName + "-" + name(AssignmentsBy3) + ","
			+ algoName + "-" + name(Assignments) + ","
			+ algoName + "-" + name(Swaps) + ","
			+ algoName + "-" + name(ArrayAccess) + ","
			+ algoName + "-" + name(Duration) + " (ms)";
	}

	string ComparingFactors::getResultsStringForCSV()
	{
		return to_string(m_overallPerformance) + ","
			+ to_string(m_comparisons) + ","
			+ to_string(m_assignmentsBy3) + ","
			+ to_string(m_assignments) + ","
			+ to_string(m_swaps) + ","
			+ to_string(m_arrayAccess) + ","
			+ to_string(m_duration) + ",";
			//+ "\"" + m_duration + "\"";
	}

	void ComparingFactors::operator+=(const ComparingFactors& obj)
	{
		m_isSorted = m_isSorted && obj.m_isSorted;
		m_overallPerformance += obj.m_overallPerformance;
		m_comparisons += obj.m_comparisons;
		m_assignments += obj.m_assignments;
		m_assignmentsBy3 += obj.m_assignmentsBy3;
		m_swaps += obj.m_swaps;
		m_arrayAccess += obj.m_arrayAccess;
		m_isStable = m_isStable && obj.m_isStable;
		m_duration += obj.m_duration;
	}

	void ComparingFactors::divideBy(int count)
	{
		m_overallPerformance /= count;
		m_comparisons /= count;
		m_assignments /= count;
		m_assignmentsBy3 /= count;
		m_swaps /= count;
		m_arrayAccess /= count;
		m_duration /= count;
	}

	bool ComparingFactors::operator< (const ComparingFactors& rhs) const
	{
		//return std::make_tuple(m_comparisons, m_assignmentsBy3, m_arrayAccess, m_duration) <
		//	std::make_tuple(rhs.m_comparisons, rhs.m_assignmentsBy3, rhs.m_arrayAccess, rhs.m_duration);
		return std::make_tuple(m_duration, m_comparisons, m_assignmentsBy3, m_arrayAccess) <
			std::make_tuple(rhs.m_duration, rhs.m_comparisons, rhs.m_assignmentsBy3, rhs.m_arrayAccess);
	}

//==================== class SortingAlgorithm

	SortingAlgorithm::SortingAlgorithm(string algoName, SortFun sortFun, bool isStableSortingAlgo)
		: m_algoName(algoName), 
		  m_sortFun(sortFun),
		  m_isStableSortingAlgo(isStableSortingAlgo),
		  m_testCaseCount(0)
	{
	}

	void SortingAlgorithm::apply(DataSet& dataSet) const
	{
		(*m_sortFun)(dataSet);
	}

	const string& SortingAlgorithm::getAlgoName() const
	{
		return m_algoName;
	}

	bool SortingAlgorithm::isStableSortingAlgo() const
	{
		return m_isStableSortingAlgo;
	}

	const ComparingFactors& SortingAlgorithm::getComparingFactors() const
	{
		return m_averagePerformance;
	}

	//void incrementTestCaseCount() { ++m_testCaseCount; }
	//int getTestCaseCount() { return m_testCaseCount; }

	void SortingAlgorithm::addComparingFactors(const ComparingFactors& obj)
	{
		m_averagePerformance += obj;
		++m_testCaseCount;
	}

	void SortingAlgorithm::calculateAverage()
	{
		if(m_testCaseCount != 0)
			m_averagePerformance.divideBy(m_testCaseCount);
	}

	void SortingAlgorithm::printAveragePerformance()
	{
		getBuffer(cout);
	}

	string SortingAlgorithm::getAveragePerformanceString() const
	{
		std::stringstream buffer;
		getBuffer(buffer);
		return buffer.str();
	}

	void SortingAlgorithm::getBuffer(std::ostream& base) const
	{
		base << setw(30) << m_algoName << ": ";
		m_averagePerformance.getBuffer(base);
		base << setw(20) << "Test Cases Count: " << m_testCaseCount;
	}

	bool SortingAlgorithm::operator< (const SortingAlgorithm& rhs) const
	{
		return m_averagePerformance < rhs.m_averagePerformance;
	}


//=============== class SortingPerformance

	SortingPerformance::SortingPerformance(DataSet& refDataSet, SortingAlgorithm& refSortingAlgo)
		: m_refSortingAlgo(refSortingAlgo), 
		m_refOriginalDataSet(refDataSet), 
		m_dataSetCopy(refDataSet.getCopy())
	{
	}

	SortingPerformance::SortingPerformance(const SortingPerformance& obj)
		:m_refSortingAlgo(obj.m_refSortingAlgo),
		m_refOriginalDataSet(obj.m_refOriginalDataSet),
		m_dataSetCopy(obj.m_dataSetCopy)
	{
		m_comparingFactors = obj.m_comparingFactors;
	}

	void SortingPerformance::sort()
	{
		SingletonCounters::resetCounters();
		Timer t;
		t.resetTimer();
		m_refSortingAlgo.apply(m_dataSetCopy);
		//string durationString = t.getDurationStringTillNow();
		long long duration = t.getDurationTillNowInNanoSeconds();

		bool isSorted = utils::checkIfSorted(m_dataSetCopy, m_refSortingAlgo.getAlgoName(), m_refOriginalDataSet);
		bool isStableSort = utils::checkIfStableSort(m_dataSetCopy, m_refSortingAlgo.isStableSortingAlgo(), m_refSortingAlgo.getAlgoName(), m_refOriginalDataSet);

		m_comparingFactors.set(ComparingFactors::SortingFactorType::IsSorted, isSorted);
		m_comparingFactors.set(ComparingFactors::SortingFactorType::OverallPerformance, SingletonCounters::getComparisons() + (SingletonCounters::getAssignments() / 3) + SingletonCounters::getArrayAccess());
		m_comparingFactors.set(ComparingFactors::SortingFactorType::Comparisons, SingletonCounters::getComparisons());
		m_comparingFactors.set(ComparingFactors::SortingFactorType::AssignmentsBy3, SingletonCounters::getAssignments()/3);
		m_comparingFactors.set(ComparingFactors::SortingFactorType::Assignments, SingletonCounters::getAssignments());
		m_comparingFactors.set(ComparingFactors::SortingFactorType::Swaps, SingletonCounters::getSwaps());
		m_comparingFactors.set(ComparingFactors::SortingFactorType::ArrayAccess, SingletonCounters::getArrayAccess());
		m_comparingFactors.set(ComparingFactors::SortingFactorType::Duration, duration);
		m_comparingFactors.set(ComparingFactors::SortingFactorType::IsStable, isStableSort);
	}

	void SortingPerformance::printResults()
	{
		getBuffer(cout);
		m_comparingFactors.printResults();
	}

	string SortingPerformance::getResultsString()
	{
		std::stringstream buffer;
		getBuffer(buffer);
		return buffer.str() + m_comparingFactors.getResultsString();
	}

	void SortingPerformance::getBuffer(std::ostream& base) const
	{
		base << "\n" << setw(30) << m_refSortingAlgo.getAlgoName() << ": ";
	}

	string SortingPerformance::getColumnTitlesForCSV()
	{
		return m_comparingFactors.getColumnTitlesForCSV(m_refSortingAlgo.getAlgoName());
	}

	string SortingPerformance::getResultsStringForCSV()
	{
		return m_comparingFactors.getResultsStringForCSV();
	}

	const SortingAlgorithm& SortingPerformance::getSortingAlgorithm()
	{
		return m_refSortingAlgo;
	}

	const DataSet& SortingPerformance::getOriginalDataSet()
	{
		return m_refOriginalDataSet;
	}

	const DataSet& SortingPerformance::getProcessedDataSet()
	{
		return m_dataSetCopy;
	}

	const ComparingFactors& SortingPerformance::getComparingFactors()
	{
		return m_comparingFactors;
	}


//====================== class CSVWriter

	CSVWriter::CSVWriter(std::string filename, bool newFile /*= false*/)
	{
		//int mode = ios::app;
		std::ios_base::openmode mode = ios::app;
		if (newFile)
			mode = ios::trunc;
		try
		{
			m_file.open(filename, mode);
		}
		catch (std::ofstream::failure &writeErr)
		{
			cout << "\nERROR: Can not open file: " << filename << endl;
		}
		catch (...)
		{
			cout << "\nUNKNOWN ERROR while opening file: " << filename << endl;
		}
	}
	CSVWriter::~CSVWriter()
	{
		if (m_file.is_open())
			m_file.close();
	}

	void CSVWriter::write(std::string text)
	{
		if (m_file.is_open())
			m_file.write(text.c_str(), text.length());
	}


//===================== class CompleteReport

	CompleteReport::CompleteReport()
	{
		m_sortingAlgorithms.push_back(SortingAlgorithm("bubbleSort_t1", bubbleSort_t1, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("bubbleSort_1", bubbleSort_1, SortingAlgorithm::STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("SelectionSort_t1", SelectionSort_t1, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("SelectionSort_1", SelectionSort_1, SortingAlgorithm::NOT_STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("InsertionSort_t1", InsertionSort_t1, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("InsertionSort_t2", InsertionSort_t2, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("InsertionSort_t3", InsertionSort_t3, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("InsertionSort_t4", InsertionSort_t4, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("InsertionSort_t5", InsertionSort_t5, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("InsertionSort_1", InsertionSort_1, SortingAlgorithm::STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortLR_t1", QuickSortLR_t1, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortLR_t2", QuickSortLR_t2, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortLR_t3TCO", QuickSortLR_t3TCO, SortingAlgorithm::NOT_STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortLL_t1", QuickSortLL_t1, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortLL_t2TCO", QuickSortLL_t2TCO, SortingAlgorithm::NOT_STABLE));

		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSort3WayLR_1", QuickSort3WayLR_1, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSort3WayLR_t2", QuickSort3WayLR_t2, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSort3WayLR_t3", QuickSort3WayLR_t3, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSort3WayLR_t4", QuickSort3WayLR_t4, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSort3WayLR_t5", QuickSort3WayLR_t5, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSort3WayLR_t6", QuickSort3WayLR_t6, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSort3WayLR_t7", QuickSort3WayLR_t7, SortingAlgorithm::NOT_STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortDualPivot_1", QuickSortDualPivot_1, SortingAlgorithm::NOT_STABLE));

		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortMultiPivot_1Pivots", QuickSortMultiPivot_1Pivots, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortMultiPivot_2Pivots", QuickSortMultiPivot_2Pivots, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortMultiPivot_3Pivots", QuickSortMultiPivot_3Pivots, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortMultiPivot_4Pivots", QuickSortMultiPivot_4Pivots, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortMultiPivot_5Pivots", QuickSortMultiPivot_5Pivots, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortMultiPivot_6Pivots", QuickSortMultiPivot_6Pivots, SortingAlgorithm::NOT_STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("QuickSortIterative", QuickSortIterative, SortingAlgorithm::NOT_STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortTopDown1", MergeSortTopDown1, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortTopDown2", MergeSortTopDown2, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortTopDown3", MergeSortTopDown3, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortTopDown4", MergeSortTopDown4, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortTopDown5", MergeSortTopDown5, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortTopDown6", MergeSortTopDown6, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortTopDown7", MergeSortTopDown7, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortBottomUp1", MergeSortBottomUp1, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortBottomUp2", MergeSortBottomUp2, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortBottomUp3", MergeSortBottomUp3, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortBottomUp4", MergeSortBottomUp4, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("MergeSortBottomUp5", MergeSortBottomUp5, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("NaturalMergeSort_noIterators", NaturalMergeSort_noIterators, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("NaturalMergeSort1", NaturalMergeSort1, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("NaturalMergeSort2", NaturalMergeSort2, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("NaturalMergeSort3", NaturalMergeSort3, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("NaturalMergeSort4", NaturalMergeSort4, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("NaturalMergeSort5", NaturalMergeSort5, SortingAlgorithm::STABLE));

		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace1", HeapSortInPlace1, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace2", HeapSortInPlace2, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace3", HeapSortInPlace3, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace4", HeapSortInPlace4, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace5", HeapSortInPlace5, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace6", HeapSortInPlace6, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace7", HeapSortInPlace7, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace8", HeapSortInPlace8, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace9", HeapSortInPlace9, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace10", HeapSortInPlace10, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace11", HeapSortInPlace11, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace12", HeapSortInPlace12, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace13", HeapSortInPlace13, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("HeapSortInPlace14", HeapSortInPlace14, SortingAlgorithm::STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortLSD_t1", RadixSortLSD_t1, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortLSD_t2", RadixSortLSD_t2, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortLSD_1", RadixSortLSD_1, SortingAlgorithm::STABLE));

		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortLSD_t3", RadixSortLSD_t3, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortLSD_t4", RadixSortLSD_t4, SortingAlgorithm::STABLE));

		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortMSD_t1", RadixSortMSD_t1, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortMSD_t2", RadixSortMSD_t2, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortMSD_t3", RadixSortMSD_t3, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortMSD_1", RadixSortMSD_1, SortingAlgorithm::NOT_STABLE));

		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortMSD_t4", RadixSortMSD_t4, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("RadixSortMSD_t5", RadixSortMSD_t5, SortingAlgorithm::STABLE));

		m_sortingAlgorithms.push_back(SortingAlgorithm("CountingSort_1", CountingSort_1, SortingAlgorithm::STABLE));

		m_sortingAlgorithms.push_back(SortingAlgorithm("GenericBucketSort_1", GenericBucketSort_1, SortingAlgorithm::NOT_STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("StlSort_1", StlSort_1, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("StlStableSort_1", StlStableSort_1, SortingAlgorithm::STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("StlHeapSort_1", StlHeapSort_1, SortingAlgorithm::NOT_STABLE));
		
		m_sortingAlgorithms.push_back(SortingAlgorithm("ShellSort_t1", ShellSort_t1, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("ShellSort_t2", ShellSort_t2, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("ShellSort_t3", ShellSort_t3, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("ShellSort_t4", ShellSort_t4, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("ShellSort_t5", ShellSort_t5, SortingAlgorithm::NOT_STABLE));
		m_sortingAlgorithms.push_back(SortingAlgorithm("ShellSort_t6", ShellSort_t6, SortingAlgorithm::NOT_STABLE));
		
		//const int variableSizeSets = 4; //These sets will have sizes 1, 2, 3, 4 respectively
		//const int hardcodedSets = 4;
		const int dataSize = 100; //Count of numbers in each dataset/array
		const int uniqueRandomNumberSets = 100;
		const int repeatedRandomNumberSets = 100;

		// Prepare data sets for sanity test cases

		//Generate 4 sets having sizes 1, 2, 3, 4
		//for (int i = 0; i < variableSizeSets; i++)
		//{
		//	DataSet dataSet("Short set count " + to_string(i + 1), i + 1);
		//	for (int j = 0; j < i + 1; j++)
		//		dataSet[j].setVal(1 + rand() % variableSizeSets);

		//	m_sanityDataSet.push_back(dataSet);
		//}

		int currentDataSize = 1;
		DataSet dataSet("Short set " + to_string(m_sanityDataSet.size() + 1), { 1 });
		m_sanityDataSet.push_back(dataSet);

		currentDataSize = 2;
		bool repeatition = true;
		vector< vector<int> > output;
		Permutations::generatePermutations({ 1, 2 }, repeatition, output);
		for (size_t i = 0; i < output.size(); i++)
		{
			DataSet dataSet("Short set " + to_string(m_sanityDataSet.size() + 1), output[i]);
			m_sanityDataSet.push_back(dataSet);
		}

		currentDataSize = 3;
		output.clear();
		Permutations::generatePermutations({ 1, 2, 3 }, repeatition, output);
		for (size_t i = 0; i < output.size(); i++)
		{
			DataSet dataSet("Short set " + to_string(m_sanityDataSet.size() + 1), output[i]);
			m_sanityDataSet.push_back(dataSet);
		}

		currentDataSize = 4;
		output.clear();
		Permutations::generatePermutations({ 1, 2, 3, 4 }, repeatition, output);
		for (size_t i = 0; i < output.size(); i++)
		{
			DataSet dataSet("Short set " + to_string(m_sanityDataSet.size() + 1), output[i]);
			m_sanityDataSet.push_back(dataSet);
		}

		//Generate random number sets of different sizes from currentDataSize to dataSize
		srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		int backup = currentDataSize;
		for (currentDataSize = currentDataSize + 1; currentDataSize <= dataSize; currentDataSize++)
		{
			DataSet dataSet("Unique random number set variable size " + to_string(currentDataSize), currentDataSize);

			//This code is repeated below. TODO: Avoid repeatition of code
			//I like my own algos :)
			for (int j = 0; j < currentDataSize; j++)
				dataSet[j].setVal(j + 1);
			//Shuffle the array: this shuffling algo generates all possible n! combinations from set of n numbers including the sorted array
			for (int j = currentDataSize - 1; j > 0; j--)
			{
				int coindex = rand() % (j + 1);
				if (j == coindex)
					continue;
				else
					std::swap(dataSet[j], dataSet[coindex]);
			}
			m_sanityDataSet.push_back(dataSet);
		}

		// Prepare data sets for extreme cases

		//Generate REPEATED random number sets of different sizes from currentDataSize to dataSize
		currentDataSize = backup;
		for (currentDataSize = currentDataSize + 1; currentDataSize <= dataSize; currentDataSize++)
		{
			DataSet dataSet("Repeated random number set variable size " + to_string(currentDataSize), currentDataSize);
			int uniqueSetSize = (currentDataSize / 3);
			for (int j = 0; j < currentDataSize; j++)
			{
				int num = rand() % uniqueSetSize + 1;
				dataSet[j].setVal(num);
			}
			m_sanityDataSet.push_back(dataSet);
		}

		//All below sets are of constant size = dataSize

		{
			//Generate set of single repeated number
			DataSet dataSet("Single repeated number", dataSize);
			for (int i = 0; i < dataSize; i++)
				dataSet[i].setVal(5);
			m_extremeDataSet.push_back(dataSet);
		}

		{
			//Generate Already sorted numbers
			DataSet dataSet("Already Sorted", dataSize);
			for (int i = 0; i < dataSize; i++)
				dataSet[i].setVal(i + 1);
			m_extremeDataSet.push_back(dataSet);
		}

		{
			//Generate sorted numbers but in reverse order
			DataSet dataSet("Reverse sorted", dataSize);
			for (int i = 0; i < dataSize; i++)
				dataSet[i].setVal(dataSize - i);
			m_extremeDataSet.push_back(dataSet);
		}

		{
			//Generate Almost sorted numbers
			DataSet dataSet("Almost sorted", dataSize);
			for (int i = 0; i < dataSize; i++)
				dataSet[i].setVal(i + 1);
			//Swap just 10% of them
			double percentage = 10;
			int increment = dataSize / (dataSize * percentage / 100);
			for (int i = 0; i < dataSize; i += increment)
			{
				int coindex = (i + 1) + rand() % (dataSize - (i + 1)); //Get random co-index in range [i+1, dataSize) 
				std::swap(dataSet[i], dataSet[coindex]);
			}
			m_extremeDataSet.push_back(dataSet);
		}

		{
			//Generate the data set where most of the numbers will be concentrated in some area on the entire range of objects
			//e.g. 1,2,8,9,10,11,12,13,14,15,51,52,75,100
		}

		//MyAssert::myRunTimeAssert(m_dataSets.size() == (variableSizeSets + hardcodedSets), "The number of data set mismatch");

		// Prepare data sets for average cases

		//Generate random numbers	
		srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		for (int i = 0; i < uniqueRandomNumberSets; i++)
		{
			DataSet dataSet("Unique random number set " + to_string(i + 1), dataSize);

			// This works:
			//for (int j = 1; j <= dataSize; j++)
			//	obj[i][j-1] = j;
			//std::random_shuffle(obj[i], obj[i] + dataSize - 1);

			//I like my own algos :)
			for (int j = 0; j < dataSize; j++)
				dataSet[j].setVal(j + 1);
			//Shuffle the array: this shuffling algo generates all possible n! combinations from set of n numbers including the sorted array
			for (int j = dataSize - 1; j > 0; j--)
			{
				int coindex = rand() % (j + 1);
				if (j == coindex)
					continue;
				else
					std::swap(dataSet[j], dataSet[coindex]);
			}

			//Works, but very bad algo. O(n^2)
			//std::list<int> refList;
			//for (int i = 1; i <= dataSize; i++)
			//	refList.push_back(i);
			//int j = 0;
			//int sizeOfList = dataSize;
			//while (!refList.empty())
			//{
			//	int n = rand() % sizeOfList;
			//	list<int>::iterator it = refList.begin();
			//	for (int k = 0; k < n; k++)
			//		++it;
			//	obj[i][j++] = *it;
			//	refList.erase(it);
			//	--sizeOfList;
			//}
			//MyAssert::myRunTimeAssert(j == 20, "\nValue of j is not equal to 20");

			// This works: But may take lot of iterations until it fills up all bits
			//int cashe = 0;
			//int j = 0;
			//int max = pow(2, (dataSize + 1)) - 1;
			//while((cashe & max) != max)
			//{
			//	int n = rand() % dataSize + 1;
			//	int mask = 1 << n;
			//	//Check if nth bit is OFF
			//	if((cashe & mask) == 0)
			//	{
			//		//Make nth bit ON
			//		cashe |= mask;
			//		obj[i][j++] = n;
			//	}
			//}
			//MyAssert::myRunTimeAssert(j == 20, "\nValue of j is not equal to 20");

			// This works: But may take lot of iterations until it fills up all bits
			//int cashe = 0;
			//int j = 0;
			////Make all 20 bits ON
			//int cashe = pow(2, dataSize) - 1;
			//while (cashe > 0)
			//{
			//	int n = rand() % dataSize + 1;
			//	//Check if nth bit in ON
			//	int mask = 1 << n;
			//	if ((cashe & mask) > 0)
			//	{
			//		//Make nth bit OFF
			//		cashe &= ~mask;
			//		obj[i][j++] = n;
			//	}
			//}
			//MyAssert::myRunTimeAssert(j == 20, "\nValue of j is not equal to 20");

			// This does not work:
			//for (int j = 0; j < dataSize; j++)
			//{
			//	srand(dataSize);
			//	obj[i][j] = rand();
			//}

			m_randomDataSet.push_back(dataSet);
		}

		//Generate repeated random numbers
		for (int i = 0; i < repeatedRandomNumberSets; i++)
		{
			DataSet dataSet("Repeated random number set " + to_string(i + 1), dataSize);
			int uniqueSetSize = (dataSize / 3);
			for (int j = 0; j < dataSize; j++)
			{
				int num = rand() % uniqueSetSize + 1;
				dataSet[j].setVal(num);
			}
			m_randomDataSet.push_back(dataSet);
		}		
	}

	void CompleteReport::sortData()
	{
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Performing SANITY TESTING ...\n";
		sortData(m_sanityDataSet);
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Working on EXTREME TEST CASES ...\n";
		sortData(m_extremeDataSet);
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Working on RANDOM TEST CASES ...\n";
		sortData(m_randomDataSet, true);
	}

	//Default argument should be seen by compiler before calling function ---- Not necessarily :)  ---- This is wrong comment
	void CompleteReport::sortData(vector<DataSet>& refDataSet, bool calcAverage /*= false*/)
	{
		const int totalSortingAlgorithms = m_sortingAlgorithms.size();
		const int dataSize = refDataSet.size();
		cout << "Total test cases: " << dataSize << " Total Algorithms: " << totalSortingAlgorithms << endl;
		for (int i = 0; i < dataSize; i++)
		{
			//int size = refDataSet[i].getSize();
			//cout << "\n\nTrying on dataset (size: " << size << ")";
			//cout << "\nDataSet: ";
			//for(int k = 0; k < size; k++)
			//{
			//	cout << refDataSet[i][k].getVal();
			//	if (k < size - 1)
			//		cout << ", ";
			//}

			//print the data set on screen
			//refDataSet[i].printSet();

			cout << "\r" << "Performing test " << setw(3) << i + 1 ;

			for (int j = 0; j < totalSortingAlgorithms; j++)
			{
				//Following message on console makes it very slow
				//cout << "\r" << "Testing in progress: testcase no.: " << setw(3) << i + 1 << " of " << dataSize << " Algo no.: " << setw(3) << j + 1 << " of " << totalSortingAlgorithms;

				SortingPerformance currentSort(refDataSet[i], m_sortingAlgorithms[j]);

				//cout << endl << "Trying " << m_sortingAlgorithms[j].getAlgoName() << "...";

				currentSort.sort();
				
				//If it reaches here, the data is successfully sorted
				//cout << endl << setw(50) << m_sortingAlgorithms[j].getAlgoName() << ": SUCCESS";

				m_sortingPerformance.push_back(currentSort);

				//Prepare for average performance
				if (!calcAverage)
					continue;

				m_sortingAlgorithms[j].addComparingFactors(currentSort.getComparingFactors());
			}
		}
	}

	void CompleteReport::createSummaryReport()
	{
		const int totalSortingAlgorithms = m_sortingAlgorithms.size();
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Calculating average and sorting average data ...\n";
		for (int i = 0; i < totalSortingAlgorithms; i++)
		{
			m_sortingAlgorithms[i].calculateAverage();
		}
		std::sort(m_sortingAlgorithms.begin(), m_sortingAlgorithms.end());
	}

	void CompleteReport::displayOnScreen()
	{
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Displaying on Screen ...\n";

		//const int totalSortingAlgorithms = m_sortingAlgorithms.size();
		const int totalRecords = m_sortingPerformance.size();
		for (int i = 0; i < totalRecords; i++)
		{
			//if (i % totalSortingAlgorithms == 0)
			//	m_sortingPerformance[i].getOriginalDataSet().printSet();

			m_sortingPerformance[i].printResults();
		}
	}

	void CompleteReport::displaySummaryReportOnScreen()
	{
		cout << "\n\nSummary Report:----------------------------------------------------------------------------------------------------------\n";

		const int totalSortingAlgorithms = m_sortingAlgorithms.size();
		for (int i = 0; i < totalSortingAlgorithms; i++)
		{
			m_sortingAlgorithms[i].printAveragePerformance();
			if (i < totalSortingAlgorithms - 1)
				cout << "\n";	
		}
	}

	void CompleteReport::writeToTextFile()
	{
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Writing to Text File ...\n";

		string fileName(reportLocation + textFileName);
		ofstream outputFile(fileName);
		string outputString;
		if (outputFile.is_open())
		{
			const int totalSortingAlgorithms = m_sortingAlgorithms.size();
			const int totalRecords = m_sortingPerformance.size();
			for (int i = 0; i < totalRecords; i++)
			{
				if (i % totalSortingAlgorithms == 0)
					outputString += m_sortingPerformance[i].getOriginalDataSet().getSetString();

				outputString += m_sortingPerformance[i].getResultsString();
				outputFile.write(outputString.c_str(), outputString.length());
				outputString.clear();
			}

			outputFile.close();
		}
	}

	void CompleteReport::writeSummaryReportToTextFile()
	{
		string fileName(reportLocation + textFileName);
		ofstream outputFile(fileName, std::ios_base::app);
		string outputString;
		if (outputFile.is_open())
		{
			string title("\n\nSummary Report:----------------------------------------------------------------------------------------------------------\n");
			const int totalSortingAlgorithms = m_sortingAlgorithms.size();
			outputFile.write(title.c_str(), title.length());
			for (int i = 0; i < totalSortingAlgorithms; i++)
			{
				string result = m_sortingAlgorithms[i].getAveragePerformanceString();
				outputFile.write(result.c_str(), result.length());
				if (i < totalSortingAlgorithms - 1)
					outputFile.write("\n", 1);
			}

			outputFile.close();
		}
	}

	void CompleteReport::writeToCSV_DataSetsOnRows()
	{
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Writing to CSV File (DataSetsOnRows) ...\n";

		string fileName(reportLocation + csvFileName_DataSetsOnRows);
		CSVWriter csvReport(fileName, true);
		string outputString;

		const int totalSortingAlgorithms = m_sortingAlgorithms.size();
		const int totalRecords = m_sortingPerformance.size();

		//Add column titles
		csvReport.write("Data Sets Type,Data Set,");
		for (int i = 0; i < totalSortingAlgorithms; i++)
		{
			outputString += m_sortingPerformance[i].getColumnTitlesForCSV();
			csvReport.write(outputString);
			outputString.clear();
			if(i < totalSortingAlgorithms)
				outputString += ",";
		}

		outputString.clear();
		for (int i = 0; i < totalRecords; i++)
		{
			if (i % totalSortingAlgorithms == 0)
			{
				csvReport.write("\n");
				outputString += m_sortingPerformance[i].getOriginalDataSet().getSetStringForCSV();
			}

			outputString += ",";

			outputString += m_sortingPerformance[i].getResultsStringForCSV();
			csvReport.write(outputString);
			outputString.clear();
		}
	}

	void CompleteReport::writeToCSV_SortingAlgosOnRows()
	{
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Writing to CSV File (SortingAlgosOnRows) ...\n";

		string fileName(reportLocation + csvFileName_SortingAlgosOnRows);
		CSVWriter csvReport(fileName, true);
		string outputString;

		const int totalDataSets = m_randomDataSet.size();

		//Add Data Sets on first row
		outputString.clear();
		csvReport.write("Data Sets,,");
		for (int i = 0; i < totalDataSets; i++)
		{
			const unsigned int size = m_randomDataSet[i].getSize();
			outputString = "\"";
			for (size_t j = 0; j < size; j++)
			{
				outputString += to_string(m_randomDataSet[i][j].getVal());
				if (j < size) outputString += ",";
			}
			outputString += "\"";
			if (i < totalDataSets) outputString += ",";
			csvReport.write(outputString);
			outputString.clear();
		}

		//Add Data Set Types on next row
		csvReport.write("\nData Set Types,,");
		for (int i = 0; i < totalDataSets; i++)
		{
			outputString += m_randomDataSet[i].getName();
			csvReport.write(outputString);
			outputString.clear();
			if (i < totalDataSets) outputString += ",";
		}

		const int totalSortingAlgorithms = m_sortingAlgorithms.size();
		//const int totalSortingPerformances = m_sortingPerformance.size();
		//Add sorting performance numbers
		for (int i = 0; i < totalSortingAlgorithms; i++)
		{
			const ComparingFactors& comparisonFactors = m_sortingPerformance[i].getComparingFactors();
			const int totalComparisonFactors = comparisonFactors._TotalSize;

			for (int j = 0; j < totalComparisonFactors; j++)
			{
				outputString.clear();
				ComparingFactors::SortingFactorType type = ComparingFactors::SortingFactorType(j);
				outputString = "\n" + (m_sortingPerformance[i].getSortingAlgorithm().getAlgoName())
					+ "," + comparisonFactors.name(type) + ",";
				for (int k = 0; k < totalDataSets; k++)
				{
					outputString += m_sortingPerformance[i + k * totalSortingAlgorithms].getComparingFactors().get(type);
					if (k < totalDataSets) outputString += ",";
				}

				csvReport.write(outputString);				
			}
		}
	}

	void CompleteReport::writeToCSV_ForGraph()
	{
		cout << "\n\n" << Timer::getCurrentLocalTimeInNanoSeconds() << " TASK: Writing to CSV File (ForGraph) ...\n";

		string fileName(reportLocation + csvFileName_ForGraph);
		CSVWriter csvReport(fileName, true);
		string outputString;

		const int totalDataSets = m_randomDataSet.size();

		//Add Data Sets on first row
		outputString.clear();
		csvReport.write("Data Sets,");
		for (int i = 0; i < totalDataSets; i++)
		{
			const unsigned int size = m_randomDataSet[i].getSize();
			outputString = "\"";
			for (size_t j = 0; j < size; j++)
			{
				outputString += to_string(m_randomDataSet[i][j].getVal());
				if (j < size) outputString += ",";
			}
			outputString += "\"";
			if (i < totalDataSets) outputString += ",";
			csvReport.write(outputString);
			outputString.clear();
		}

		//Add Data Set Types on next row
		csvReport.write("\nData Set Types,");
		for (int i = 0; i < totalDataSets; i++)
		{
			outputString += m_randomDataSet[i].getName();
			csvReport.write(outputString);
			outputString.clear();
			if (i < totalDataSets) outputString += ",";
		}

		const int totalSortingAlgorithms = m_sortingAlgorithms.size();
		//const int totalSortingPerformances = m_sortingPerformance.size();
		//Add sorting performance numbers
		for (int i = 0; i < totalSortingAlgorithms; i++)
		{
			const ComparingFactors& comparisonFactors = m_sortingPerformance[i].getComparingFactors();
			const int totalComparisonFactors = comparisonFactors._TotalSize;

			for (int j = 0; j < totalComparisonFactors; j++)
			{
				outputString.clear();
				ComparingFactors::SortingFactorType type = ComparingFactors::SortingFactorType(j);
				outputString = "\n" + (m_sortingPerformance[i].getSortingAlgorithm().getAlgoName())
					+ " - " + comparisonFactors.name(type) + ",";
				for (int k = 0; k < totalDataSets; k++)
				{
					outputString += m_sortingPerformance[i + k * totalSortingAlgorithms].getComparingFactors().get(type);
					if (k < totalDataSets) outputString += ",";
				}

				csvReport.write(outputString);
			}
		}
	}


void utils::printDebugInformation(const string& message, const DataSet& currentDataSet, const string& algoName, const DataSet& origDataSet)
{
	//Print entire array if not sorted
	cout << "\n\n" << message << "\n";
	cout << "\nAlgorithm Name : " << algoName;
	cout << "\nData Set Name : " << currentDataSet.getName();

	cout << "\nOriginal Data Set: ";
	int dataSize = currentDataSet.getSize();
	for (int j = 0; j < dataSize; j++)
	{
		cout << origDataSet[j].getVal();
		if (j < dataSize - 1)
			cout << ", ";
	}
	cout << "\n Current Data Set: ";
	for (int j = 0; j < dataSize; j++)
	{
		cout << currentDataSet[j].getVal();
		if (j < dataSize - 1)
			cout << ", ";
	}
	cout << "\n\n";

	MyAssert::myRunTimeAssert(false, message);
}

bool utils::checkIfSorted(const DataSet& currentDataSet, const string& algoName, const DataSet& origDataSet)
{
	int dataSize = currentDataSet.getSize();
	bool sorted = true;
	for (int i = 1; i < dataSize; i++)
	{
		if (currentDataSet[i - 1].getVal() > currentDataSet[i].getVal())
		{
			sorted = false;
			break;
		}
	}

	if (!sorted)
		utils::printDebugInformation("ERROR: ARRAY IS NOT SORTED:", currentDataSet, algoName, origDataSet);

	return true;
}

bool utils::checkIfStableSort(const DataSet& currentDataSet, bool isExpectedStable, const string& algoName, const DataSet& origDataSet)
{
	bool stable = true;
	int dataSize = currentDataSet.getSize();
	for (int i = 1; i < dataSize; i++)
	{
		if (currentDataSet[i - 1].getVal() == currentDataSet[i].getVal())
			if (currentDataSet[i - 1].getOriginalPosition() > currentDataSet[i].getOriginalPosition())
			{
				stable = false;
				break;
			}
	}

	if(isExpectedStable && !stable)
		utils::printDebugInformation("ERROR: ARRAY IS NOT STABLE:", currentDataSet, algoName, origDataSet);

	return stable;
}


string getCsvColumnSeparators(int count)
{
	string retVal;
	for (int i = 0; i < count; i++)
		retVal += ",";
		return retVal;
}

void testAllSorts()
{
	CompleteReport report;
	report.sortData();
	//if(displayOnScreen)
	//	report.displayOnScreen();
	if(writeToTextFile)
		report.writeToTextFile();
	if(writeToCSVDataSetsOnRows)
		report.writeToCSV_DataSetsOnRows();
	if(writeToCSVSortingAlgosOnRows)
		report.writeToCSV_SortingAlgosOnRows();
	if(writeToCSVForGraph)
		report.writeToCSV_ForGraph();

	report.createSummaryReport();

	//if(displayOnScreen)
	//	report.displaySummaryReportOnScreen();
	if (writeToTextFile)
		report.writeSummaryReportToTextFile();

}

void printPermutations(vector< vector<int> >& output)
{
	for (size_t j = 0; j < output.size(); j++)
	{
		for (size_t k = 0; k < output[j].size(); k++)
			cout << output[j][k] << " ";

		cout << endl;
	}
}

void testPermutations()
{
	vector< vector<int> > output;
	bool repeatition = true;
	const int maxSize = 4;
	initializer_list<int> list[maxSize] = 
	{	
		{ 1 }
		,{ 1, 2 }
		,{ 1, 2, 3 }
		,{ 1, 2, 3, 4 }
//		,{ 1, 2, 3, 4, 5 } 
	};

	for (int i = 0; i < maxSize; i++)
	{
		output.clear();
		Permutations::generatePermutations(list[i], repeatition, output);
		cout << "\nWith repeatition. Values: " << i + 1 << "\n";
		printPermutations(output);

		output.clear();
		Permutations::generatePermutationsUsingRecursion(list[i], repeatition, output);
		cout << "\nWith repeatition. Values: " << i + 1 << "\n";
		printPermutations(output);

		output.clear();
		Permutations::generatePermutations(list[i], !repeatition, output);
		cout << "\nWith NO repeatition. Values: " << i + 1 << "\n";
		printPermutations(output);

		output.clear();		
		Permutations::generatePermutationsUsingRecursion(list[i], !repeatition, output);
		cout << "\nWith NO repeatition. Values: " << i + 1 << "\n";
		printPermutations(output);
	}	
}


void Sorting()
{
	//testPermutations();
	testAllSorts();
}


/*********************************************************/


}
