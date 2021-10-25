#pragma once
#ifndef COMPONENT
#define COMPONENT
	#include <memory>

	namespace Engine
	{
		struct Core;
		struct Entity;
		struct Component
		{
			friend Engine::Entity;

		private:
			std::weak_ptr<Component> _self;

			std::weak_ptr<float> _deltaTimePtr;

		public:
			std::weak_ptr<Engine::Entity> entityPtr;
			std::weak_ptr<Engine::Core> corePtr;

		private:
			static std::shared_ptr<Component> Initialise(std::weak_ptr<Entity> entityPtr);

			virtual void Update();
			virtual void PhysicsUpdate();
		};
	}
#endif