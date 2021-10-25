#pragma once
#ifndef TRANSFORM
#define TRANSFORM
	#include <glm/vec3.hpp>
	#include <glm/vec4.hpp>

	#include "Component.h"

	namespace Engine
	{
		struct Transform : Component
		{
		public:
			glm::vec3 position;
			glm::vec4 rotation;
			glm::vec3 scale;

		private:
			virtual void Update();
			virtual void PhysicsUpdate();

		public:
			Transform();
		};
	}
#endif