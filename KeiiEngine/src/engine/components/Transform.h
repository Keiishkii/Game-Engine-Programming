#pragma once
#ifndef TRANSFORM
#define TRANSFORM
	#include <glm/vec3.hpp>
	#include <glm/gtc/quaternion.hpp>

	#include "Component.h"

	namespace Engine
	{
		struct Transform : Component
		{
		public:
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scale;

		private:
			virtual void Update() override;
			virtual void PhysicsUpdate() override;
			
		public:
			Transform();
			virtual void Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr) override;
		};
	}
#endif