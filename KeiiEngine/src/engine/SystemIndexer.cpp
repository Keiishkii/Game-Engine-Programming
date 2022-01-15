#include "SystemIndexer.h"
#include "error-handling/Debugger.h"

#include <string>

namespace Engine
{
	unsigned int SystemIndexer::GetIndex(Type type)
	{
		unsigned int returnedID = 1;

		while (_activeIndexes.contains(returnedID))
		{
			returnedID++;
		}

		#if DEBUG
		{
			ErrorHandling::Debugger::Print("Allocating ID " + std::to_string(returnedID) + " to " + TypeToString(type) + " object.");
		}
		#endif
		
		_activeIndexes.insert(std::pair<unsigned int, Type>(returnedID, type));

		return returnedID;
	}

	void SystemIndexer::ReturnIndex(unsigned int index)
	{
		#if DEBUG
		{
			ErrorHandling::Debugger::Print("Returning ID " + std::to_string(index) + " from object " + TypeToString(_activeIndexes[index]) + " for reallocation.");
		}
		#endif

		_activeIndexes.erase(index);
	}

	std::string SystemIndexer::TypeToString(Type type)
	{
		std::string string;
		switch (type)
		{
			case E_COMPONENT:
			{
				string = ("\x1B[92m" + std::string("Component") + "\033[0m");
			} break;				
			case E_ENTITY:
			{
				string = ("\x1B[32m" + std::string("Entity") + "\033[0m");
			} break;
		}

		return string;
	}
}