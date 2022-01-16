#include "Collider.h"

namespace Engine
{
	namespace Components
	{
		/**	The CapsuleCollider is a child of Collider, it allows for collisions to be caluclated using the PhysX engine.  	*/
		struct CapsuleCollider : Collider
		{
		private:
		public:

		private:
			virtual void PreDestructor() override;
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
		};
	}
}