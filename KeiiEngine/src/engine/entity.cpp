#include "Entity.h"
#include "Component.h"

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