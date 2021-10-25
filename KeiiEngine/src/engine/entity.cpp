#include "Entity.h"
#include "components/Component.h"
#include "components/Transform.h"

Engine::Entity::Entity()
{
	_transform = AddComponent<Transform>();
}

std::shared_ptr<Engine::Entity> Engine::Entity::Initialise(std::weak_ptr<Core> corePtr)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	entity->_self = entity;
	entity->corePtr = corePtr;

	return entity;
}

void Engine::Entity::Update()
{
	for (int i = 0; i < componentList.size(); i++)
	{
		componentList[i]->Update();
	}
}

void Engine::Entity::PhysicsUpdate()
{
	for (int i = 0; i < componentList.size(); i++)
	{
		componentList[i]->PhysicsUpdate();
	}
}