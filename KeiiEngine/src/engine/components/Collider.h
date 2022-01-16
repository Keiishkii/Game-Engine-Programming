#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include "PxPhysicsAPI.h"

namespace Engine
{
	namespace Components
	{
		/**	The Collider is a child of Component, and the base class of all other colliders, it is required to allow its child classes to interact with the PhysX engine.  	*/
		struct Collider : Component
		{
		protected:
			physx::PxShape* _collider;
		private:
		public:


		private:
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
		};
	}
}

#endif