#include <sstream> //for std::stringstream
#include <fstream> //for file read/write
#include <iomanip> //for setw(n)
#include <tuple>
#include <chrono>

#include "Sorting_Utils/Sorting_Utils.h"
#include "Sorting_Algorithms/Sorting_bubbleSort.h"
#include "Sorting_Algorithms/Sorting_bucketSort.h"
#include "Sorting_Algorithms/Sorting_countingSort.h"
#include "Sorting_Algorithms/Sorting_heapSort.h"
#include "Sorting_Algorithms/Sorting_insertionSort.h"
#include "Sorting_Algorithms/Sorting_mergeSort.h"
#include "Sorting_Algorithms/Sorting_quickSort.h"
#include "Sorting_Algorithms/Sorting_radixSort.h"
#include "Sorting_Algorithms/Sorting_selectionSort.h"
#include "Sorting_Algorithms/Sorting_shellSort.h"
#include "Sorting_Algorithms/Sorting_STL_Sort.h"
#include "Maths/Maths_Permutations.h"
#include "Timer/Timer_Timer.h"
#include "MM_UnitTestFramework/MM_UnitTestFramework.h"

namespace mm {

	//--------------------------------------------------------------------------------------------
// Global Configurtion
	bool displayOnScreen = false;
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
		static const string sorted = "Sorted";
		static const string notSorted = "NOT Sorted";
		static const string overallPerformance = "#TotalPerf:";
		static const string comparisons = "#Comparisons:";
		static const string assignmentsBy3 = "#AssignBy3:";
		static const string assignments = "#Assign:";
		static const string swaps = "#Swaps:";
		static const string arrayAccess = "#EleAccess:";
		static const string duration = "Time:";
		static const string stable = "Stable";
		static const string notStable = "NOT Stable";
		static const string defaultRetValue = "";

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
			<< setw(name(Comparisons).length() + gap) << name(Comparisons) << setw(6) << m_comparisons			//<< ","
			<< setw(name(AssignmentsBy3).length() + gap) << name(AssignmentsBy3) << setw(6) << m_assignmentsBy3		//<< ","
			<< setw(name(Assignments).length() + gap) << name(Assignments) << setw(6) << m_assignments			//<< ","
			<< setw(name(Swaps).length() + gap) << name(Swaps) << setw(6) << m_swaps				//<< ","
			<< setw(name(ArrayAccess).length() + gap) << name(ArrayAccess) << setw(6) << m_arrayAccess			//<< ","
			<< setw(name(OverallPerformance).length() + gap) << name(OverallPerformance) << setw(6) << m_overallPerformance	//<< ","
			<< setw(name(Duration).length() + gap) << name(Duration) << setw(6) << m_duration << " ms"
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
		if (m_testCaseCount != 0)
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
		m_comparingFactors.set(ComparingFactors::SortingFactorType::AssignmentsBy3, SingletonCounters::getAssignments() / 3);
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
			cout << "\nERROR: Can not open file: " << filename << " Error: " << writeErr.what() << endl;
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
		unsigned int init = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		srand(init);
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
			int increment = static_cast<int>(dataSize / (dataSize * percentage / 100));
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
		srand(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
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
		const int totalSortingAlgorithms = static_cast<int>(m_sortingAlgorithms.size());
		const int dataSize = static_cast<int>(refDataSet.size());
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

			cout << "\r" << "Performing test " << setw(3) << i + 1;

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
		const int totalSortingAlgorithms = static_cast<int>(m_sortingAlgorithms.size());
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
		const int totalRecords = static_cast<int>(m_sortingPerformance.size());
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

		const int totalSortingAlgorithms = static_cast<int>(m_sortingAlgorithms.size());
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
			const int totalSortingAlgorithms = static_cast<int>(m_sortingAlgorithms.size());
			const int totalRecords = static_cast<int>(m_sortingPerformance.size());
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
			const int totalSortingAlgorithms = static_cast<int>(m_sortingAlgorithms.size());
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

		const int totalSortingAlgorithms = static_cast<int>(m_sortingAlgorithms.size());
		const int totalRecords = static_cast<int>(m_sortingPerformance.size());

		//Add column titles
		csvReport.write("Data Sets Type,Data Set,");
		for (int i = 0; i < totalSortingAlgorithms; i++)
		{
			outputString += m_sortingPerformance[i].getColumnTitlesForCSV();
			csvReport.write(outputString);
			outputString.clear();
			if (i < totalSortingAlgorithms)
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

		const int totalDataSets = static_cast<int>(m_randomDataSet.size());

		//Add Data Sets on first row
		outputString.clear();
		csvReport.write("Data Sets,,");
		for (int i = 0; i < totalDataSets; i++)
		{
			const unsigned int size = m_randomDataSet[i].getSize();
			outputString = "\"";
			for (unsigned int j = 0; j < size; j++)
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

		const int totalSortingAlgorithms = static_cast<int>(m_sortingAlgorithms.size());
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

		const int totalDataSets = static_cast<int>(m_randomDataSet.size());

		//Add Data Sets on first row
		outputString.clear();
		csvReport.write("Data Sets,");
		for (int i = 0; i < totalDataSets; i++)
		{
			const unsigned int size = m_randomDataSet[i].getSize();
			outputString = "\"";
			for (unsigned int j = 0; j < size; j++)
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

		const int totalSortingAlgorithms = static_cast<int>(m_sortingAlgorithms.size());
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
		cout << "\n\n" << message;
		cout << " | Algorithm Name : " << algoName;
		cout << " | Data Set Name : " << currentDataSet.getName();

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
		//cout << "\n\n";

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

		if (isExpectedStable && !stable)
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
		if(displayOnScreen)
			report.displayOnScreen();
		if (writeToTextFile)
			report.writeToTextFile();
		if (writeToCSVDataSetsOnRows)
			report.writeToCSV_DataSetsOnRows();
		if (writeToCSVSortingAlgosOnRows)
			report.writeToCSV_SortingAlgosOnRows();
		if (writeToCSVForGraph)
			report.writeToCSV_ForGraph();

		report.createSummaryReport();

		if(displayOnScreen)
			report.displaySummaryReportOnScreen();
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

	//void Sorting()
	//{
	//	//testPermutations();
	//	testAllSorts();
	//}

	MM_DECLARE_FLAG(sortingUnitTests);

	MM_UNIT_TEST(sortingUnitTests_test_1, sortingUnitTests)
	{
		testAllSorts();
	}

}