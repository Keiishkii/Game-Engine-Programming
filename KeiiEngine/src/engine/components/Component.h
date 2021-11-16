#ifndef COMPONENT_H
#define COMPONENT_H
	#include <memory>

namespace Engine
{
	struct Core;
	struct Entity;
	namespace Components
	{
		struct Camera;
		struct Transform;
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
			virtual void PhysicsUpdate();
			virtual void Render(std::weak_ptr<Components::Camera>& activeCamera);
		public:
			virtual void Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr);

			std::weak_ptr<Transform> Transform();
		};
	}
}
#endif