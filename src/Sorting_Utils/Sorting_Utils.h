#pragma once

#include <iostream>

#include "Sorting_dataStructure/Sorting_dataStructure.h"

namespace mm {

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

		bool getIsSorted() const { return m_isSorted; }
		int getOverallPerformance() const { return m_overallPerformance; }
		int getComparisons() const { return m_comparisons; }
		int getAssignments() const { return m_assignments; }
		int getAssignmentsBy3() const { return m_assignmentsBy3; }
		int getSwaps() const { return m_swaps; }
		int getArrayAccess() const { return m_arrayAccess; }
		string getDurationString() const { return m_durationString; }
		long long getDuration() const { return m_duration; }
		bool getIsStable() const { return m_isStable; }

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