#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include "glm/glm.hpp"

namespace Engine
{
	struct Core;
	struct Scene;
	struct Entity;
	struct TimeManager;
	struct SystemIndexer;
	struct Inputs;

	namespace Physics
	{
		struct PhysicsManager;
	}

	namespace Components
	{
		struct Camera;
		struct Transform;

		/**	The Component is the base class of all other components, it stores all required information for other components to work.  	*/
		struct Component
		{
			friend Engine::Entity;

		protected:
			unsigned int _systemIndex = 0;
		private:
			bool _startCalled = false;

			bool _initialiseCalled = false;
			bool _preDestructorCalled = false;

			std::weak_ptr<Component> _self;
			std::weak_ptr<Transform> _transform;

			std::weak_ptr<Engine::Core> _core;
			std::weak_ptr<Engine::SystemIndexer> _systemIndexer;
			std::weak_ptr<Engine::Scene> _scene;
			std::weak_ptr<Engine::Entity> _entity;
			std::weak_ptr<Engine::TimeManager> _timeManager;
			std::weak_ptr<Engine::Physics::PhysicsManager> _physicsManager;
			std::weak_ptr<Engine::Inputs> _inputs;
		public:


		protected:
			virtual void Start();

			virtual void Update();
			virtual void PhysicsUpdate();
			virtual void Render(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix);

			std::shared_ptr<Component> Self();
			
			virtual void PreDestructor();
		public:
			/** The Component initialiser, this is called both for the base component and the inherited copy of it.
			@param self: a pointer to the Component itself.
			@param entity: a pointer to the Entity that has ownership of the Component.	*/
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity);

			/** Get Function:
			@return Returns a shared pointer to Entity's Transform component.	*/
			std::shared_ptr<Transform> Transform();
			/** Get Function:
			@return Returns a shared pointer to the Cores.	*/
			std::shared_ptr<Engine::Core> Core();
			/** Get Function:
			@return Returns a shared pointer to the Cores's SystemIndexer.	*/
			std::shared_ptr<Engine::SystemIndexer> SystemIndexer();
			/** Get Function:
			@return Returns a shared pointer to the Scene.	*/
			std::shared_ptr<Engine::Scene> Scene();
			/** Get Function:
			@return Returns a shared pointer to the Entity.	*/
			std::shared_ptr<Engine::Entity> Entity();
			/** Get Function:
			@return Returns a shared pointer to the Cores's TimeManager.	*/
			std::shared_ptr<Engine::TimeManager> TimeManager();
			/** Get Function:
			@return Returns a shared pointer to the Cores's PhysicsManager.	*/
			std::shared_ptr<Engine::Physics::PhysicsManager> PhysicsManager();
			/** Get Function:
			@return Returns a shared pointer of the current frames Inputs.	*/
			std::shared_ptr<Engine::Inputs> Input();
		};
	}
}
#endif