#include "CapsuleCollider.h"

#include "engine/physics/PhysicsManager.h"
#include "Transform.h"
#include "engine/Entity.h"

namespace Engine
{
	namespace Components
	{
		void CapsuleCollider::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			PxPhysics* physics = PhysicsManager()->PhysXPhysics();
			PxRigidDynamic* actor = Entity()->PhysXActor();

			float radius = 1, height = 1;

			PxMaterial* material = physics->createMaterial(0.5f, 0.5f, 0.1f);
			_collider = physics->createShape(PxCapsuleGeometry(radius, (height / 2.0f)), *material, true);


			PxTransform relativePose(PxQuat(PxHalfPi, PxVec3(0, 0, 1)));
			_collider->setLocalPose(relativePose);

			actor->attachShape(*_collider);

			PxRigidBodyExt::updateMassAndInertia(*actor, 0);
		}

		void CapsuleCollider::PreDestructor()
		{
			PxRigidDynamic* actor = Entity()->PhysXActor();
			actor->detachShape(*_collider);
		}
	}
}