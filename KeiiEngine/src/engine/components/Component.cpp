#include "Component.h"
#include "engine/Entity.h"

namespace Engine
{
	namespace Components
	{
		void Component::Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr)
		{
			std::shared_ptr<Component> component = self.lock();

			component->_self = self;
			component->entityPtr = entityPtr;
			component->corePtr = entityPtr.lock()->corePtr;
		}

		void Component::Render() { }
		void Component::Update() { }
		void Component::PhysicsUpdate() { }
	}
}