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

		protected:
			std::weak_ptr<Component> _self;
			std::weak_ptr<float> _deltaTimePtr;

		public:
			std::weak_ptr<Engine::Entity> entityPtr;
			std::weak_ptr<Engine::Core> corePtr;

		private:
			virtual void Update();
			virtual void Render();
			virtual void PhysicsUpdate();

		public:
			virtual void Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr);
		};
	}
#endif