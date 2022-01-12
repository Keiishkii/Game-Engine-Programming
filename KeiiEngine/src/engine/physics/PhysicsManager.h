#include "PxPhysicsAPI.h"
#include <memory>

namespace Engine
{
	struct Core;

	namespace Physics
	{
		struct PhysicsManager
		{
			friend Core;

		private:
			std::weak_ptr<Engine::Core> _core;

			std::shared_ptr<physx::PxDefaultErrorCallback> _phsyXDefaultErrorCallback;
			std::shared_ptr<physx::PxDefaultAllocator> _phsyXDefaultAllocator;
			physx::PxFoundation* _phsyXFoundation;
		public:


		private:
			void Initialise(std::shared_ptr<Engine::Core> core);
		public:
			std::shared_ptr<Engine::Core> Core();
		};
	}
}