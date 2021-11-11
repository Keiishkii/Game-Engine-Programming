#include <iostream>

#include "Camera.h"
#include "Transform.h"
#include "engine/entity.h"

namespace Engine
{
	namespace Components
	{
		void Camera::Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPointer)
		{
			std::shared_ptr<Transform> transform = std::dynamic_pointer_cast<Transform>(self.lock());

			_self = self;
			entityPtr = entityPointer;
			corePtr = entityPointer.lock()->corePtr;
		}

		void Camera::Update() { }
		void Camera::PhysicsUpdate() { }
	}
}