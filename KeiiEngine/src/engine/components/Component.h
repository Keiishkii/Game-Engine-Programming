#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

namespace Engine
{
	struct Core;
	struct Entity;
	struct TimeManager;
	struct Inputs;
	namespace Components
	{
		struct Camera;
		struct Transform;
		struct Component
		{
			friend Engine::Entity;

		private:
			bool _startCalled = false;

			std::weak_ptr<Component> _self;
			std::weak_ptr<Transform> _transform;

			std::weak_ptr<Engine::Entity> _entity;
			std::weak_ptr<Engine::Core> _core;
			std::weak_ptr<Engine::TimeManager> _timeManager;
			std::weak_ptr<Engine::Inputs> _inputs;
		public:


		protected:
			virtual void Start();

			virtual void Update();
			virtual void PhysicsUpdate();
			virtual void Render(const std::shared_ptr<Components::Camera>& activeCamera);

			std::shared_ptr<Component> Self();
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity);

			std::shared_ptr<Transform> Transform();
			std::shared_ptr<Engine::Core> Core();
			std::shared_ptr<Engine::Entity> Entity();
			std::shared_ptr<Engine::TimeManager> Time();
			std::shared_ptr<Engine::Inputs> Input();
		};
	}
}
#endif