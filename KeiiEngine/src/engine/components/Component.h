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
		struct Component
		{
			friend Engine::Entity;

		protected:
			unsigned int _systemIndex = 0;
		private:
			bool _startCalled = false;
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
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity);

			std::shared_ptr<Transform> Transform();
			std::shared_ptr<Engine::Core> Core();
			std::shared_ptr<Engine::SystemIndexer> SystemIndexer();
			std::shared_ptr<Engine::Scene> Scene();
			std::shared_ptr<Engine::Entity> Entity();
			std::shared_ptr<Engine::TimeManager> TimeManager();
			std::shared_ptr<Engine::Physics::PhysicsManager> PhysicsManager();
			std::shared_ptr<Engine::Inputs> Input();
		};
	}
}
#endif