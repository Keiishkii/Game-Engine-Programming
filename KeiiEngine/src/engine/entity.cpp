#include "Entity.h"
#include "components/Component.h"
#include "components/Transform.h"

std::shared_ptr<Engine::Entity> Engine::Entity::Initialise(std::weak_ptr<Core> corePtr)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	entity->_self = entity;
	entity->corePtr = corePtr;

	entity->_transform = entity->AddComponent<Transform>();

	return entity;
}

void Engine::Entity::Render()
{
	for (int i = 0; i < componentList.size(); i++)
	{
		componentList[i]->Render();
	}
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