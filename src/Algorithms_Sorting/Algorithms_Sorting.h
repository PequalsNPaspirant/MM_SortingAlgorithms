//Goal:
//Try various sorting algorithms
//Implement performance measuring techniques to measure time, number of comparisons, number of swaps/assignments
//Use fixed size arrays of objects to avoid performance impact due to allocation and deallocation

//TODO:
// Done: Add a function to check whether it is stable sort or not
// Collect all statistics in vector and plot a graph

/*
#include <iostream>
#include <vector>
#include <string>
#include <sstream> //for std::stringstream

#include <chrono> //C++11
using HRClock = std::chrono::high_resolution_clock;
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
*/
using namespace std;

//Enable this to debug
//#define DEBUG
namespace mm {

class DataSet;
class utils
{
public:
	static bool checkIfSorted(const DataSet& temp, const string& algoName, const DataSet& origDataSet);
	static bool checkIfStableSort(const DataSet& temp, bool isExpectedStable, const string& algoName, const DataSet& origDataSet);

private:
	static void printDebugInformation(const string& message, const DataSet& currentDataSet, const string& algoName, const DataSet& origDataSet);
};

class SingletonCounters
{
public:
	static void resetCounters();
	static void incrementComparisons();
	static void incrementSwaps();
	static void incrementAssignments();
	static void incrementArrayAccess();
	static int getComparisons();
	static int getSwaps();
	static int getAssignments();
	static int getArrayAccess();

private:
	static SingletonCounters& get();

	int m_comparisons;
	int m_swaps;
	int m_assignments;
	int m_arrayAccess;
};

class Object
{
public:
	Object(int n = 0);
	Object(const Object& rhs);
	const Object& operator=(const Object& rhs);
	bool operator<(const Object& rhs) const;
	bool operator==(const Object& rhs);
	bool operator<=(const Object& rhs);
	void swap(Object& rhs);
	int getVal() const;
	void setVal(int val);
	unsigned int getOriginalPosition() const;
	void setOriginalPosition(unsigned int pos);

private:
	int m_val;
	unsigned int m_originalPosition;

	bool operator>(const Object& rhs) = delete;
};

class DataSet
{
public:
	DataSet(string name, const unsigned int size = 0);
	DataSet(string name, initializer_list<int> list);
	DataSet(string name, vector<int> vec);
	~DataSet();

	//Transfer ownership
	DataSet(const DataSet& obj);
	//Transfer ownership
	DataSet operator=(const DataSet& obj);
	DataSet getCopy();
	DataSet getCopy(int start, int end);
	void setSize(const unsigned int size);
	const unsigned int getSize() const;

	Object& operator[](const unsigned int index);
	const Object& operator[](const unsigned int index) const;
	const string& getName() const;
	void printSet() const;
	string getSetString() const;
	void getBuffer(std::ostream& base) const;
	string getSetStringForCSV() const;

private:

	void setOriginalPositions();

	string m_dataSetName;
	Object* m_data;
	unsigned int m_size;
};


//=============================================================================================================
//	Sortign Algorithms - START

//=======================+=============+
//                       | Bubble Sort |
//=======================+=============+

// Bubble Sort - trial version 1
//=======================================================================================

//Stable sort
void bubbleSort_t1(DataSet& obj);

// Bubble Sort - 1
//=======================================================================================

//Stable sort
//Optimizes the next iteration. Keeps track of last swap happened in last iteration. No comparison required after this position.
void bubbleSort_1(DataSet& obj);


//=======================+================+
//                       | Selection Sort |
//=======================+================+

// Selection Sort - Trial Version 1
//=======================================================================================

//NOT Stable sort
void SelectionSort_t1(DataSet& obj);

// Selection Sort - 1
//=======================================================================================

//NOT Stable sort
void SelectionSort_1(DataSet& obj);

//=======================+================+
//                       | Insertion Sort |
//=======================+================+

// Insertion Sort - Trial Version 1
//=======================================================================================

//Stable sort
void InsertionSort_t1(DataSet& obj);

// Insertion Sort - Trial Version 2
//=======================================================================================

//Stable sort
//This is slightly faster than above
void InsertionSort_t2(DataSet& obj);

// Insertion Sort - Trial Version 3
//=======================================================================================

//Stable sort
//This is slightly faster than above. Some silly effort to save initial assignment temp = obj[i];
void InsertionSort_t3(DataSet& obj);

// Insertion Sort - Trial Version 4
//=======================================================================================

//Stable sort
//Different implementation. Go on comparing adjusant elements. Iterate backwards when conflict is found. 
void InsertionSort_t4(DataSet& obj);

// Insertion Sort - Trial Version 5
//=======================================================================================

//Stable sort
//Binary insertion sort
//Do binary search to reduce comparisons.
void InsertionSort_t5(DataSet& obj);

// Insertion Sort - 1
//=======================================================================================

//Stable sort
//Binary insertion sort
//Do binary search more effectively than above algo.
void InsertionSort_1(DataSet& obj);

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

//=======================+============+
//                       | Heap Sort |
//=======================+============+

//Common Helper Functions
//------------------------------------------------------------------------------------

int LeftChild(int index);

int RightChild(int index);
int Parent(int index);
int getLeftChildIndex(int index);

int getRightChildIndex(int index);

//floor rounds towards negative infinity, while integer division rounds towards zero (truncates)
// floor((2 - 1) / 2.0) = floor(0.5) = 0
// (2 - 1) / 2 = 1 / 2 = 0   ( .5 is truncated from actual result 0.5. In fact, integer division does not calculate anything after decimal point)
// (2 + 1) / 2 - 1 = 3 / 2 - 1 = 1 - 1 = 0

int getParentIndex(int index);

int getParentIndex2(int index);

int getParentIndex3(int index);

int getParentIndex4(int index);
int getLevel(int index); //level starts from zero


// sift up Functions
//------------------------------------------------------------------------------------

//This is equivalent to adding new element at the end of a valid heap
//Used for heapify top-down		- Yes
//Used for heapify bottom-up	- No
//Used for extract Max			- No

void siftUp1(DataSet& obj, int childIndex);

//This is equivalent to replacing the top element of a valid heap. So new top element needs to be places at appropriate position
//Used for heapify top-down		- No
//Used for heapify bottom-up	- Yes
//Used for extract Max			- Yes
void siftUp2(DataSet& obj, const int heapSize, const int index);

//This is optimized version of siftUp2(). Do binary search in SECOND while loop along the path the root element can descend. So the element can be positioned in O(log log n)
//Used for heapify top-down		- No
//Used for heapify bottom-up	- Yes
//Used for extract Max			- Yes
void siftUp3(DataSet& obj, const int heapSize, const int index);

//This is optimized version of siftUp3(). Return if the top element is already at right position.
//Used for heapify top-down		- No
//Used for heapify bottom-up	- Yes
//Used for extract Max			- Yes
void siftUp4(DataSet& obj, const int heapSize, const int index);

//This is optimized version of siftUp4(). Return if the top element is already at right position. But do binary search more efficiently.
//Used for heapify top-down		- No
//Used for heapify bottom-up	- Yes
//Used for extract Max			- Yes
void siftUp5(DataSet& obj, const int heapSize, const int index);


//This is optimized version of siftUp2(). Do binary search in FIRST while loop along the path the root element can descend. 
//So the element can be positioned in O(log log n). Second while loop may not be needed. This may give same performace as siftDown3().
//In fact it is same as siftDown3() because the first loop descends down, so it is sift-down.
//Used for heapify top-down		- No
//Used for heapify bottom-up	- Yes
//Used for extract Max			- Yes
void siftDown3(DataSet& obj, const int heapSize, const int index);
void siftUp6(DataSet& obj, const int heapSize, const int index);

// sift down Functions
//------------------------------------------------------------------------------------

//Used for heapify top-down		- No
//Used for heapify bottom-up	- Yes
//Used for extract Max			- Yes
void siftDown1_usingRecursion(DataSet& obj, int heapSize, int subTreeRootIndex);
void siftDown1_withoutRecursion(DataSet& obj, int heapSize, int subTreeRootIndex);

//Used for heapify top-down		- No
//Used for heapify bottom-up	- No
//Used for extract Max			- Yes
int leafSearch(DataSet& obj, int index);
void siftDown2(DataSet& obj, int heapSize, int index);

//This is optimized version of siftDown1_withoutRecursion(). Do binary search along the path the root element can descend. So the element can be positioned in O(log log n)
//Used for heapify top-down		- No
//Used for heapify bottom-up	- Yes
//Used for extract Max			- Yes
void siftDown3(DataSet& obj, int heapSize, int index);

//This is optimized version of siftDown3(). Return if the top element is already at right position.
//Used for heapify top-down		- No
//Used for heapify bottom-up	- Yes
//Used for extract Max			- Yes
void siftDown4(DataSet& obj, int heapSize, int index);

// heapify top-down Functions
//------------------------------------------------------------------------------------

void heapify_TopDown1(DataSet& obj);

// heapify bottom-up Functions
//------------------------------------------------------------------------------------

void heapify_BottomUp1_usingRecursion(DataSet& obj);

void heapify_BottomUp1_withoutRecursion(DataSet& obj);
void heapify_BottomUp2(DataSet& obj);

void heapify_BottomUp3(DataSet& obj);
void heapify_BottomUp4(DataSet& obj);
void heapify_BottomUp5(DataSet& obj);

void heapify_BottomUp6(DataSet& obj);

// Extract max Functions
//------------------------------------------------------------------------------------

void extractMax1_usingRecursion(DataSet& obj);

void extractMax1_withoutRecursion(DataSet& obj);

//This is most optimized function as it avoids swaps
void extractMax2(DataSet& obj);

void extractMax3(DataSet& obj);

void extractMax4(DataSet& obj);

// HeapSort
//=======================================================================================

//This is NOT stable sort
void HeapSortInPlace1(DataSet& obj);

//This is stable sort
void HeapSortInPlace2(DataSet& obj);

//This is NOT stable sort
void HeapSortInPlace3(DataSet& obj);

//This is NOT stable sort
void HeapSortInPlace4(DataSet& obj);

//This is NOT stable sort
void HeapSortInPlace5(DataSet& obj);

//This is stable sort
void HeapSortInPlace6(DataSet& obj);

//This is NOT stable sort
void HeapSortInPlace7(DataSet& obj);

//This is NOT stable sort
void HeapSortInPlace8(DataSet& obj);

//This is stable sort
void HeapSortInPlace9(DataSet& obj);

//This is NOT stable sort
void HeapSortInPlace10(DataSet& obj);

//This is stable sort
void HeapSortInPlace11(DataSet& obj);

//This is stable sort
void HeapSortInPlace12(DataSet& obj);

//This is stable sort
void HeapSortInPlace13(DataSet& obj);

//This is stable sort
void HeapSortInPlace14(DataSet& obj);

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

void CountSort_t1(DataSet& obj, int base, int LSDPosition);

void RadixSortLSD_t1(DataSet& obj);

// Radix Sort LSD - Trial Version 2
//It is same as above, except it uses std::partial_sum()
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void CountSort_t2(DataSet& obj, int base, int LSDPosition);

void RadixSortLSD_t2(DataSet& obj);

// This is best version of LSD
// Radix Sort LSD - Version 1
//It is same as Trial Version 2, except it avoid copying the temp array back into original array, rather it alternatively uses each array as temp array
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void CountSort_1(DataSet& input, int base, int LSDPosition, DataSet& output);

void RadixSortLSD_1(DataSet& obj);

// Radix Sort LSD - Trial Version 3
// It is same as Version 1, except it does not use std::partial_sum() and 
// it stores the start position of each object having particular digit at LSDPosition. This exactly same as what is done in Counting Sort
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void CountSort_t3(DataSet& input, int base, int LSDPosition, DataSet& output);

void RadixSortLSD_t3(DataSet& obj);

// Radix Sort LSD - Trial Version 3 - Stable in-place LSD radix sort
// It is same as MSD Version 1. It does not use O(n) space, it does swapping in-place
// THIS IS NOT POSSIBLE AND IT DOES NOT WORK as the inner swapping loop produces unstable order of objects and LSD needs stable ordering
//=======================================================================================

void RadixSortLSD_t4_doesNotWork(DataSet& obj, int base, int LSDPosition);
void RadixSortLSD_t4_doesNotWork(DataSet& obj);

// Radix Sort LSD - Trial Version 3
// It is same as Version 1, except it uses queue instead of temp array
// This is not more efficient, but very simple to implement
//=======================================================================================

void RadixSortLSD_t4(DataSet& obj, int base, int LSDPosition);

void RadixSortLSD_t4(DataSet& obj);

//==================================== MSD ===========================================================================================

// Radix Sort MSD - Trial Version 1
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void RadixSortMSD_t1(DataSet& obj, int base, int lo, int hi, int MSDPosition);

void RadixSortMSD_t1(DataSet& obj);


// Radix Sort MSD - Trial Version 2
// It is same as version 1, except the loop is from lo to hi
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void RadixSortMSD_t2(DataSet& obj, int base, int lo, int hi, int MSDPosition);

void RadixSortMSD_t2(DataSet& obj);

// Radix Sort MSD - Trial Version 3
// This is NOT Stable sort
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void RadixSortMSD_t3(DataSet& obj, int base, int lo, int hi, int MSDPosition);

void RadixSortMSD_t3(DataSet& obj);

// This is the best version
// Radix Sort MSD - Version 1
// It is same as Trial Version 1, except it uses loop from lo to hi inseat of i = 0 to i < (hi - lo)
// counting sort, least significant digit(LSD) first, out - of - place redistribute
//=======================================================================================

void RadixSortMSD_1(DataSet& obj, int base, int lo, int hi, int MSDPosition);

void RadixSortMSD_1(DataSet& obj);

// Radix Sort MSD - Trial Version 4
// stable MSD, with max O(n) extra space. It uses O(n) only for first iteration
// It is same as Version 1, except it uses extra space to sort each bucket
//=======================================================================================

void RadixSortMSD_t4(DataSet& obj, int base, int lo, int hi, int MSDPosition);

void RadixSortMSD_t4(DataSet& obj);

// Radix Sort MSD - Trial Version 5
// It is same as LSD Trial Version 3. It uses queue for MSD.
// This is not more efficient, but very simple to implement
//=======================================================================================

void RadixSortMSD_t5(DataSet& obj, int base, int lo, int hi, int MSDPosition);

void RadixSortMSD_t5(DataSet& obj);


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

int CountingSort_1_calculateKey(const Object& element, int min);

void CountingSort_1(DataSet& obj);

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

int GenericBucketSort_1_calculateKey(const Object& element, int min, int max, int bucketCount);

void GenericBucketSort_1(DataSet& obj, int lo, int hi);

void GenericBucketSort_1(DataSet& obj);

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

void StlSort_1(DataSet& obj);

void StlStableSort_1(DataSet& obj);

void StlHeapSort_1(DataSet& obj);

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

//=======================+=============+
//                       | Smooth Sort |
//=======================+=============+

void SmoothSortInPlace(DataSet& obj);


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


class ComparingFactors
{
public:
	enum SortingFactorType { IsSorted, IsStable, OverallPerformance, Comparisons, AssignmentsBy3, Assignments, Swaps, ArrayAccess, Duration, _TotalSize };

	ComparingFactors();

	void set(SortingFactorType type, int count);
	void set(SortingFactorType type, long long duration);
	void set(SortingFactorType type, string str);
	void set(SortingFactorType type, bool val);

	const string get(SortingFactorType type) const;
	const string& name(SortingFactorType type) const;

	void printResults() const;
	string getResultsString() const;
	void getBuffer(std::ostream& base) const;

	string getColumnTitlesForCSV(const string& algoName);
	string getResultsStringForCSV();

	void operator+=(const ComparingFactors& obj);
	bool operator< (const ComparingFactors& rhs) const;
	void divideBy(int count);

	bool getIsSorted() const			{ return m_isSorted; }
	int getOverallPerformance() const	{ return m_overallPerformance; }
	int getComparisons() const			{ return m_comparisons; }
	int getAssignments() const			{ return m_assignments; }
	int getAssignmentsBy3() const		{ return m_assignmentsBy3; }
	int getSwaps() const				{ return m_swaps; }
	int getArrayAccess() const			{ return m_arrayAccess; }
	string getDurationString() const	{ return m_durationString; }
	long long getDuration() const		{ return m_duration; }
	bool getIsStable() const			{ return m_isStable; }

private:
	bool m_isSorted;
	int m_overallPerformance;
	int m_comparisons;
	int m_assignments;
	int m_assignmentsBy3;
	int m_swaps;
	int m_arrayAccess;
	string m_durationString;
	long long m_duration;
	bool m_isStable;
};

class SortingAlgorithm
{
private:
	typedef void(*SortFun)(DataSet& obj);

public:

	static const bool STABLE = true;
	static const bool NOT_STABLE = false;

	SortingAlgorithm(string algoName, SortFun sortFun, bool isStableSortingAlgo);

	void apply(DataSet& dataSet) const;
	const string& getAlgoName() const;
	bool isStableSortingAlgo() const;
	const ComparingFactors& getComparingFactors() const;

	//void incrementTestCaseCount() { ++m_testCaseCount; }
	//int getTestCaseCount() { return m_testCaseCount; }

	void addComparingFactors(const ComparingFactors& obj);
	void calculateAverage();
	void printAveragePerformance();
	string getAveragePerformanceString() const;
	void getBuffer(std::ostream& base) const;
	bool operator< (const SortingAlgorithm& rhs) const;

private:
	string m_algoName;
	SortFun m_sortFun;
	bool m_isStableSortingAlgo;
	ComparingFactors m_averagePerformance;
	int m_testCaseCount;
};

class SortingPerformance
{
public:
	SortingPerformance(DataSet& refDataSet, SortingAlgorithm& refSortingAlgo);
	SortingPerformance(const SortingPerformance& obj);

	void sort();
	void printResults();
	string getResultsString();
	void getBuffer(std::ostream& base) const;
	string getColumnTitlesForCSV();
	string getResultsStringForCSV();
	const SortingAlgorithm& getSortingAlgorithm();
	const DataSet& getOriginalDataSet();
	const DataSet& getProcessedDataSet();
	const ComparingFactors& getComparingFactors();

private:
	const SortingAlgorithm& m_refSortingAlgo;
	const DataSet& m_refOriginalDataSet;
	DataSet m_dataSetCopy;
	ComparingFactors m_comparingFactors;
};

class CSVWriter
{
public:
	CSVWriter(std::string filename, bool newFile = false);
	~CSVWriter();

	void write(std::string text);

private:
	ofstream m_file;
};


class CompleteReport
{
public:
	CompleteReport();

	void sortData();
	//Default argument should be seen by compiler before calling function ---- Not necessarily :)  ---- This is wrong comment
	void sortData(vector<DataSet>& refDataSet, bool calcAverage = false);
	void createSummaryReport();
	void displayOnScreen();
	void displaySummaryReportOnScreen();
	void writeToTextFile();
	void writeSummaryReportToTextFile();
	void writeToCSV_DataSetsOnRows();
	void writeToCSV_SortingAlgosOnRows();
	void writeToCSV_ForGraph();

private:
	vector<SortingAlgorithm> m_sortingAlgorithms;
	vector<DataSet> m_sanityDataSet;
	vector<DataSet> m_extremeDataSet;
	vector<DataSet> m_randomDataSet;
	
	vector<SortingPerformance> m_sortingPerformance;
};


}
