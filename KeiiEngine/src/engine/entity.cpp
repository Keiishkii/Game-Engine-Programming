#include "Entity.h"
#include "components/Component.h"
#include "components/Transform.h"
#include "components/Camera.h"

namespace Engine
{
	std::weak_ptr<Components::Transform> Entity::Transform() { return _transform; }

	std::shared_ptr<Entity> Entity::Initialise(std::weak_ptr<Core> corePtr)
	{
		std::shared_ptr<Entity> entity = std::make_shared<Entity>();

		entity->_self = entity;
		entity->corePtr = corePtr;

		entity->_transform = entity->AddComponent<Components::Transform>();

		return entity;
	}

	void Entity::Render(std::weak_ptr<Components::Camera>& activeCamera)
	{
		for (int i = 0; i < componentList.size(); i++)
		{
			componentList[i]->Render(activeCamera);
		}
	}

	void Entity::Update()
	{
		for (int i = 0; i < componentList.size(); i++)
		{
			componentList[i]->Update();
		}
	}

	void Entity::PhysicsUpdate()
	{
		for (int i = 0; i < componentList.size(); i++)
		{
			componentList[i]->PhysicsUpdate();
		}
	}
}