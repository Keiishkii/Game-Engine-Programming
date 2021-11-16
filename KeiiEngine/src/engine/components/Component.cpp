#include "Component.h"
#include "Camera.h"
#include "Transform.h"
#include "engine/Entity.h"

namespace Engine
{
	namespace Components
	{
		std::weak_ptr<Transform> Component::Transform() { return entityPtr.lock()->Transform(); }

		void Component::Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr)
		{
			std::shared_ptr<Component> component = self.lock();

			component->_self = self;
			component->entityPtr = entityPtr;
			component->corePtr = entityPtr.lock()->corePtr;
		}

		void Component::Render(std::weak_ptr<Components::Camera>& activeCamera) { }
		void Component::Update() { }
		void Component::PhysicsUpdate() { }
	}
}