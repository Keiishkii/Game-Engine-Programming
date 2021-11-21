#include <iostream>
#include <string>

#include "Exception.h"

namespace Engine
{
	namespace ErrorHandling
	{
		Exception::Exception(std::string errorMessage)
		{
			_errorMessage = errorMessage;
		}

		const std::string Exception::What()
		{
			return _errorMessage;
		}

		void Exception::Print()
		{
			std::cout << "\x1B[31m" << "Exception:" << "\033[0m" << " " << _errorMessage << std::endl;
		}

		Exception::~Exception() {}
	}
}

