#include <memory>
#include <vector>
#include <map>
#include <string>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "PxPhysicsAPI.h"

namespace Engine
{
	namespace Components
	{
		struct Component;
		struct Camera;
		struct Transform;
	}
	
	namespace Physics
	{
		struct PhysicsManager;
	}

	struct Core;
	struct Scene;
	struct SystemIndexer;

	/**	Entity is the class in which defines objects within the game world. In other engines this could be considered an Actor or GameObject.  	*/
	struct Entity
	{
		friend Engine::Scene;

	private:
		unsigned int _systemIndex = 0;

		std::string _name;
		physx::PxRigidDynamic* _physXActor;

		std::weak_ptr<Entity> _self;
		std::weak_ptr<Engine::Core> _core;
		std::weak_ptr<Engine::Physics::PhysicsManager> _physicsManager;
		std::weak_ptr<Engine::SystemIndexer> _systemIndexer;
		std::weak_ptr<Components::Transform> _transform;

		bool _componentListDirty;
		std::map<unsigned int, std::shared_ptr<Components::Component>> _components;
		std::vector<std::shared_ptr<Components::Component>> _componentList;
		std::vector<unsigned int> _componentsMarkedForDelete;
	public:


	private:
		void Initialise(std::shared_ptr<Entity> self, std::shared_ptr<Engine::Core> core);

		void Update();
		void Render(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix);
		void PhysicsUpdate();

		std::shared_ptr<Entity> Self();
		std::vector<std::shared_ptr<Components::Component>> Components();

		void CleanComponentList();

		void PreDestructor();
	public:
		/** Entity Constructor: only used to set the name of the entity; */
		Entity(std::string name);


		/** Adds a component to the entity. */
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			std::shared_ptr<Entity> self = Self();

			component->Component::Initialise(component, self);
			component->Initialise(component, self);

			_components[component->_systemIndex] = component;
			_componentListDirty = true;

			return component;
		}

		/** Adds a component to the entity.
		@param parameter: a paramter passed at the end of the components constructor.		*/
		template <typename T, typename A>
		std::shared_ptr<T> AddComponent(A parameter)
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			std::shared_ptr<Entity> self = Self();

			component->Component::Initialise(component, self);
			component->Initialise(component, self, parameter);

			_components[component->_systemIndex] = component;
			_componentListDirty = true;

			return component;
		}

		/** Removes a component from the entity by using its system index.
		@param component: a shared pointer to the component to be removed.		*/
		void RemoveComponent(std::shared_ptr<Components::Component> component);

		/** Get Function: 
		@return Returns the name given to the Entity.		*/
		std::string& Name();
		/** Get Function: 
		@return Returns a shared pointer to the Core.		*/
		std::shared_ptr<Core> Core();
		/** Get Function: 
		@return Returns a shared pointer to the Entity's PhysXActor.		*/
		physx::PxRigidDynamic* PhysXActor();
		/** Get Function: 
		@return Returns a shared pointer to the Cores PhysicsManager.		*/
		std::shared_ptr<Physics::PhysicsManager> PhysicsManager();
		/** Get Function: 
		@return Returns a shared pointer to the Cores SystemIndexer.		*/
		std::shared_ptr<SystemIndexer> SystemIndexer();
		/** Get Function: 
		@return Returns a shared pointer to the Entity's Transform component.	*/
		std::shared_ptr<Components::Transform> Transform();
	};
}