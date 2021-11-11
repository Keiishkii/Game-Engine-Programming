#ifndef COMPONENT_H
#define COMPONENT_H
	#include <memory>

namespace Engine
{
	struct Core;
	struct Entity;
	namespace Components
	{
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
}
#endif