#include "Collider.h"

namespace Engine
{
	namespace Components
	{
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