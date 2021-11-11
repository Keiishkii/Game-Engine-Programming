#include <iostream>

#include "Transform.h"
#include "engine/entity.h"

namespace Engine
{
	namespace Components
	{
		Transform::Transform()
		{
			position = glm::vec3{ 0, 0, 0 };
			rotation = glm::quat{ 1, 0, 0, 0 };
			scale = glm::vec3{ 1, 1, 1 };
		}

		void Transform::Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPointer)
		{
			std::shared_ptr<Transform> transform = std::dynamic_pointer_cast<Transform>(self.lock());

			_self = self;
			entityPtr = entityPointer;
			corePtr = entityPointer.lock()->corePtr;
		}

		void Transform::Update() { }
		void Transform::PhysicsUpdate() { }
	}
}