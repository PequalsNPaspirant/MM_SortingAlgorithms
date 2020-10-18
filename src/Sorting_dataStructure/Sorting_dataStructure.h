#pragma once

#include <string>
#include <vector>
using namespace std;

namespace mm {

	class MyAssert
	{
	public:
		static void myRunTimeAssert(bool condition, const std::string& msg)
		{
			if (!condition)
			{
				int* ptr = nullptr;
				*ptr = 0;
			}
		}
	};

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

}