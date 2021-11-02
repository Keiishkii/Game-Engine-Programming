#include "Component.h"
#include "engine/Entity.h"

void Engine::Component::Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr)
{
	std::shared_ptr<Component> component = self.lock();

	component->_self = self;
	component->entityPtr = entityPtr;
	component->corePtr = entityPtr.lock()->corePtr;
}

void Engine::Component::Render() { }
void Engine::Component::Update() { }
void Engine::Component::PhysicsUpdate() { }