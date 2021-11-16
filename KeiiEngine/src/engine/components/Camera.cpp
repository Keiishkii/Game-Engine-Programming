#include <iostream>
#include <glew.h>

#include "Camera.h"
#include "engine/Core.h"
#include "Transform.h"
#include "engine/entity.h"

namespace Engine
{
	namespace Components
	{
		glm::mat4x4 Camera::ProjectionMatrix() { return _projectionMatrix; }
		void Camera::GenerateNewProjectionMatrix(float windowWidth, float windowHeight)
		{
			_projectionMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.01f, 1000.f);
		}

		void Camera::Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPointer)
		{
			std::shared_ptr<Components::Transform> transform = std::dynamic_pointer_cast<Components::Transform>(self.lock());

			_self = self;
			entityPtr = entityPointer;
			corePtr = entityPointer.lock()->corePtr;

			corePtr.lock()->_cameraList.push_back(std::dynamic_pointer_cast<Camera>(_self.lock()));
		}

		void Camera::Update() { }
		void Camera::PhysicsUpdate() { }
	}
}