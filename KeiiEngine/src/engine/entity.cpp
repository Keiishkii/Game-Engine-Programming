#include "Entity.h"
#include "components/Component.h"
#include "components/Transform.h"
#include "components/Camera.h"

namespace Engine
{
	Entity::Entity(std::string name)
	{
		_name = name;
	}

	void Entity::Initialise(std::shared_ptr<Entity> self, std::shared_ptr<Engine::Core> core)
	{
		self->_self = self;
		self->_core = core;

		self->_transform = self->AddComponent<Components::Transform>();
	}

	void Entity::Render(const std::shared_ptr<Components::Camera>& activeCamera)
	{
		for (int i = 0; i < _componentList.size(); i++)
		{
			_componentList[i]->Render(activeCamera);
		}
	}

	void Entity::Update()
	{
		for (int i = 0; i < _componentList.size(); i++)
		{
			_componentList[i]->Component::Update();
			_componentList[i]->Update();
		}
	}

	void Entity::PhysicsUpdate()
	{
		for (int i = 0; i < _componentList.size(); i++)
		{
			_componentList[i]->PhysicsUpdate();
		}
	}

	std::string& Entity::Name() { return _name; }
	std::shared_ptr<Entity> Entity::Self() { return _self.lock(); }
	std::shared_ptr<Core> Entity::Core() { return _core.lock(); }
	std::shared_ptr<Components::Transform> Entity::Transform() { return _transform.lock(); }
}