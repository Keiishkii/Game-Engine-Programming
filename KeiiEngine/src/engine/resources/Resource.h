#pragma once
#ifndef RESOURCE
#define RESOURCE
	#include <string>
	#include <memory>

namespace Engine
{
	namespace ResourceManagement
	{		
		struct Resource
		{
		public:
			virtual void Load(std::string path);
		};
	}
}

#endif