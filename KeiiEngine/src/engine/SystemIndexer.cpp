#include "SystemIndexer.h"
#include "error-handling/Debugger.h"

#include <string>

namespace Engine
{
	SystemIndexer::SystemIndexer()
	{

	}

	unsigned int SystemIndexer::GetIndex()
	{
		unsigned int returnedID = 1;

		_indexIterator = std::find(_activeIndexes.begin(), _activeIndexes.end(), returnedID);
		while (_indexIterator != _activeIndexes.end())
		{
			returnedID++;
			_indexIterator = std::find(_activeIndexes.begin(), _activeIndexes.end(), returnedID);
		}

		#if _DEBUG
		{
			ErrorHandling::Debugger::Print("Allocating object with ID " + std::to_string(returnedID));
		}
		#endif
		
		_activeIndexes.push_back(returnedID);
		return returnedID;
	}

	void SystemIndexer::ReturnIndex(unsigned int index)
	{
		#if _DEBUG
		{
			ErrorHandling::Debugger::Print("Returning " + std::to_string(index) + " to free index's.");
		}
		#endif

		_indexIterator = std::find(_activeIndexes.begin(), _activeIndexes.end(), index);
		
		if (_indexIterator != _activeIndexes.end())
			_activeIndexes.erase(_indexIterator);
	}
}