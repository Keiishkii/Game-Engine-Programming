#include "glm/glm.hpp"

#include "Entity.h"
#include "components/Component.h"
#include "engine/physics/PhysicsManager.h"
#include "components/Transform.h"
#include "components/Camera.h"
#include "Core.h"
#include "SystemIndexer.h"

namespace Engine
{
	Entity::Entity(std::string name)
	{
		_name = name;
	}

	void Entity::PreDestructor()
	{
		for (std::shared_ptr<Components::Component> component : _componentList)
		{
			component->PreDestructor();
			component->Components::Component::PreDestructor();
		}

		_components.clear();
		_componentList.clear();

		PhysicsManager()->PhysXScene()->removeActor(*_physXActor);

		SystemIndexer()->ReturnIndex(_systemIndex);
	}

	void Entity::Initialise(std::shared_ptr<Entity> self, std::shared_ptr<Engine::Core> core)
	{
		self->_self = self;
		
		_core = core;
		_systemIndexer = core->SystemIndexer();
		_physicsManager = Core()->PhysicsManager();
		_transform = self->AddComponent<Components::Transform>();

		_physXActor = PhysicsManager()->PhysXPhysics()->createRigidDynamic(PxTransform());
		PhysicsManager()->PhysXScene()->addActor(*_physXActor);

		_systemIndex = SystemIndexer()->GetIndex(SystemIndexer::E_ENTITY);
	}

	void Entity::Render(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix)
	{
		for (int i = 0; i < _components.size(); i++)
		{
			Components()[i]->Render(transformationMatrix, projectionMatrix);
		}
	}

	void Entity::Update()
	{
		for (int i = 0; i < _componentList.size(); i++)
		{
			Components()[i]->Component::Update();
			Components()[i]->Update();
		}
	}

	void Entity::PhysicsUpdate()
	{
		for (int i = 0; i < _componentList.size(); i++)
		{
			Components()[i]->PhysicsUpdate();
		}
	}


	void Entity::RemoveComponent(std::shared_ptr<Components::Component> component)
	{
		_componentsMarkedForDelete.push_back(component->_systemIndex);
	}

	void Entity::CleanComponentList()
	{
		if (_componentsMarkedForDelete.size() > 0)
		{
			_componentListDirty = true;

			for (unsigned int index : _componentsMarkedForDelete)
			{
				_components.find(index)->second->PreDestructor();
				_components.erase(index);
			}

			_componentsMarkedForDelete.clear();
		}
	}

	std::vector<std::shared_ptr<Components::Component>> Entity::Components()
	{
		if (_componentListDirty)
		{
			_componentList.clear();
			for (const std::pair<unsigned int, std::shared_ptr<Components::Component>>& component : _components)
			{
				_componentList.push_back(component.second);
			}

			_componentListDirty = false;
		}

		return _componentList;
	}


	std::string& Entity::Name() { return _name; }
	std::shared_ptr<Entity> Entity::Self() { return _self.lock(); }
	std::shared_ptr<Core> Entity::Core() { return _core.lock(); }
	physx::PxRigidDynamic* Entity::PhysXActor() { return _physXActor; }
	std::shared_ptr<Engine::Physics::PhysicsManager> Entity::PhysicsManager() { return _physicsManager.lock(); }
	std::shared_ptr<SystemIndexer> Entity::SystemIndexer() { return _systemIndexer.lock(); }
	std::shared_ptr<Components::Transform> Entity::Transform() { return _transform.lock(); }
}