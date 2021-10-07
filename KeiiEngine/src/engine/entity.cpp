#include "Entity.h"
#include "Component.h"

std::shared_ptr<Engine::Component> Engine::Entity::AddComponent()
{
	std::shared_ptr<Engine::Component> component = std::make_shared<Engine::Component>();
	componentList.push_back(component);

	return component;
}