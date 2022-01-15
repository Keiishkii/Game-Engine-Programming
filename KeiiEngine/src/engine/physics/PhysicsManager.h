//#define NDEBUG
#include "PxPhysicsAPI.h"
#include <memory>
#include <vector>

#define PVD_HOST "127.0.0.1"


using namespace physx;

namespace Engine
{
	struct Core;
	struct Entity;
	struct TimeManager;

	namespace Components
	{
		struct CapsuleCollider;
	}

	namespace Physics
	{
		struct PhysicsManager
		{
			friend Core;
			friend Entity;
			friend Components::CapsuleCollider;

		private:
			std::weak_ptr<Engine::Core> _core;
			std::weak_ptr<Engine::TimeManager> _timeManager;

			PxFoundation* _phsyXFoundation;
			std::shared_ptr<PxDefaultErrorCallback> _phsyXDefaultErrorCallback;
			std::shared_ptr<PxDefaultAllocator> _phsyXDefaultAllocator;

			PxPhysics* _physXPhysics;
			PxPvdTransport* _physXTransport;
			PxPvd* _physXPVD;

			PxCooking* _physXCooking;

			PxScene* _physXScene;
		public:


		private:
			void Initialise(std::shared_ptr<Engine::Core> core, std::shared_ptr<Engine::TimeManager> timeManager);

			void InitialiseFoundation();
			void InitialisePhysics();
			void InitialiseCooking();

			void CreateScene();

			PxScene* PhysXScene();
			PxPhysics* PhysXPhysics();
		public:
			~PhysicsManager();

			void Simulate(std::vector<std::shared_ptr<Entity>> entitys);

			std::shared_ptr<Engine::Core> Core();
			std::shared_ptr<Engine::TimeManager> TimeManager();
		};
	}
}