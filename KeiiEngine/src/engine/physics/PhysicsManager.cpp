#include <ctype.h>
#include "PhysicsManager.h"

using namespace physx;

namespace Engine
{
	namespace Physics
	{
		void PhysicsManager::Initialise(std::shared_ptr<Engine::Core> core)
		{
			_core = core;

			_phsyXFoundation = NULL;
			_phsyXFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *_phsyXDefaultAllocator, *_phsyXDefaultErrorCallback);
		}

		std::shared_ptr<Engine::Core> PhysicsManager::Core() { return _core.lock(); }
	}
}