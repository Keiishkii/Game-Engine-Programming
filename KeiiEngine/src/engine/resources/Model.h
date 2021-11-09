#pragma once
#ifndef MODEL
#define MODEL
	#include "Resource.h"

	namespace Engine
	{
		namespace ResourceManagement
		{
			struct Model : Resource
			{
			private:
				virtual void Load(std::string path) override;
			};
		}
	}
#endif