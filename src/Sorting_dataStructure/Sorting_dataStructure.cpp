#include <iostream>
#include <sstream>
#include <cassert>
using namespace std;

#include "Sorting_dataStructure/Sorting_dataStructure.h"
//#include "Assert/MyAssert.h"
#include "Timer/Timer_Timer.h"
#include "Maths/Maths_Permutations.h"

namespace mm {

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
		: m_val(rhs.m_val),
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
			assert(false, "Size is already set");
	}
	const unsigned int DataSet::getSize() const { return m_size; }

	Object& DataSet::operator[](const unsigned int index)
	{
		SingletonCounters::incrementArrayAccess();
		assert(index < m_size, "Size overflow");
		return m_data[index];
	}

	const Object& DataSet::operator[](const unsigned int index) const
	{
		SingletonCounters::incrementArrayAccess();
		assert(index < m_size, "Size overflow");
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

}