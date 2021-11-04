#include <iostream>
#include <string>

#include "Exception.h"

Engine::ErrorHandling::Exception::Exception(std::string errorMessage)
{
	_errorMessage = errorMessage;
}

Engine::ErrorHandling::Exception::~Exception() {}

const std::string Engine::ErrorHandling::Exception::What()
{
	return _errorMessage;
}

void Engine::ErrorHandling::Exception::Print()
{
	std::cout << _errorMessage << std::endl;
}
