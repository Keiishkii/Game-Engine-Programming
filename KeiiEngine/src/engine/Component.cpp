#include "Component.h"
#include "Entity.h"

std::shared_ptr<Engine::Component> Engine::Component::Initialise(std::weak_ptr<Engine::Entity> entityPtr)
{
	std::shared_ptr<Component> component = std::make_shared<Component>();

	component->_self = component;
	component->entityPtr = entityPtr;
	component->corePtr = entityPtr.lock()->corePtr;
	
	return component;
}

void Engine::Component::Update() { }
void Engine::Component::PhysicsUpdate() { }