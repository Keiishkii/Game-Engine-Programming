#pragma once
#ifndef RESOURCE
#define RESOURCE

namespace Engine
{
	namespace ResourceManagement
	{
		#include <string>
		
		struct Resource
		{
		public:
			virtual void Load(std::string path);
		};
	}
}
#endif