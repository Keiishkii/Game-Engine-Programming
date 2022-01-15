#include <ctype.h>

#include "PhysicsManager.h"
#include "engine/Entity.h"
#include "engine/components/Transform.h"
#include "engine/error-handling/Exception.h"
#include "engine/time/TimeManager.h"
#include "engine/engine-maths/Maths.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace Physics
	{
		void PhysicsManager::Initialise(std::shared_ptr<Engine::Core> core, std::shared_ptr<Engine::TimeManager> timeManager)
		{
			_core = core;
			_timeManager = timeManager;

			InitialiseFoundation();
			InitialisePhysics();
			InitialiseCooking();

			if (!PxInitExtensions(*_physXPhysics, _physXPVD))
			{
				throw Exception("PxInitExtensions failed!");
			}

			CreateScene();
		}

		void PhysicsManager::InitialiseFoundation()
		{
			_phsyXDefaultAllocator = std::make_shared<PxDefaultAllocator>();
			_phsyXDefaultErrorCallback = std::make_shared<PxDefaultErrorCallback>();

			_phsyXFoundation = NULL;
			_phsyXFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *_phsyXDefaultAllocator, *_phsyXDefaultErrorCallback);
		}

		void PhysicsManager::InitialisePhysics()
		{
			bool recordMemoryAllocations = true;

			_physXPVD = PxCreatePvd(*_phsyXFoundation);
			_physXTransport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
			_physXPVD->connect(*_physXTransport, PxPvdInstrumentationFlag::eALL);

			_physXPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *_phsyXFoundation, PxTolerancesScale(), recordMemoryAllocations, _physXPVD);
			
			if (_physXPhysics == nullptr)
			{
				throw Exception("PxCreatePhysics failed!");
			}
		}

		void PhysicsManager::InitialiseCooking()
		{
			PxCookingParams parameters = PxCookingParams(_physXPhysics->getTolerancesScale());
			_physXCooking = PxCreateCooking(PX_PHYSICS_VERSION, *_phsyXFoundation, PxCookingParams(parameters));
			
			if (!_physXCooking) 
			{
				throw Exception("PxCreateCooking failed!");
			}
		}

		void PhysicsManager::CreateScene()
		{
			PxSceneDesc paramters = PxSceneDesc(_physXPhysics->getTolerancesScale());
			_physXScene = _physXPhysics->createScene(paramters);
		}



		PhysicsManager::~PhysicsManager()
		{
			_physXScene->release();
			_physXCooking->release();

			_physXPhysics->release();
			_physXPVD->release();
			_physXTransport->release();

			_phsyXFoundation->release();
		}



		void PhysicsManager::Simulate(std::vector<std::shared_ptr<Entity>> entitys)
		{
			for (std::shared_ptr<Entity> entity : entitys)
			{
				glm::vec3 position = entity->Transform()->Position();
				Maths::ConvertVector_RightToLeftHandedCoordinateSystem(position);

				glm::quat rotation = entity->Transform()->Rotation();
				Maths::ConvertQuaterion_RightToLeftHandedCoordinateSystem(rotation);


				//entity->PhysXActor()->setGlobalPose(PxTransform(PxVec3(position.x, position.y, position.z)));

				entity->PhysXActor()->setGlobalPose(PxTransform(PxVec3(position.x, position.y, -position.z), PxQuat(rotation.x, rotation.y, rotation.z, rotation.w)));
			}

			_physXScene->simulate(TimeManager()->DeltaTime());
			_physXScene->fetchResults(true);


			for (std::shared_ptr<Entity> entity : entitys)
			{
				PxTransform physXTransform = entity->PhysXActor()->getGlobalPose();

				PxVec3 PxPosition = physXTransform.p;
				PxQuat PxRotation = physXTransform.q;

				glm::vec3 position = glm::vec3(PxPosition.x, PxPosition.y, PxPosition.z);
				Maths::ConvertVector_RightToLeftHandedCoordinateSystem(position);
				
				glm::quat rotation = glm::quat(PxRotation.x, PxRotation.y, PxRotation.z, PxRotation.w);
				Maths::ConvertQuaterion_RightToLeftHandedCoordinateSystem(rotation);

				entity->Transform()->Position() = position;
				entity->Transform()->Rotation() = rotation;
			}
		}



		PxScene* PhysicsManager::PhysXScene() { return _physXScene; }
		PxPhysics* PhysicsManager::PhysXPhysics() { return _physXPhysics; }

		std::shared_ptr<Engine::Core> PhysicsManager::Core() { return _core.lock(); }
		std::shared_ptr<Engine::TimeManager> PhysicsManager::TimeManager() { return _timeManager.lock(); }
	}
}