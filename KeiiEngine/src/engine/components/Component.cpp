#include "Component.h"
#include "Camera.h"
#include "Transform.h"
#include "engine/SystemIndexer.h"
#include "engine/Core.h"
#include "engine/Scene.h"
#include "engine/Entity.h"
#include "engine/time/TimeManager.h"
#include "engine/physics/PhysicsManager.h"
#include "engine/input/InputManager.h"
#include "engine/input/Inputs.h"

namespace Engine
{
	namespace Components
	{
		void Component::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			if (!_initialiseCalled)
			{
				self->_self = self;

				_entity = entity;
				_transform = entity->Transform();
				_core = entity->Core();
				_physicsManager = entity->PhysicsManager();
				_systemIndexer = Core()->SystemIndexer();
				_scene = Core()->ActiveScene();
				_timeManager = Core()->TimeManager();
				_inputs = Core()->InputManager()->Input();

				_systemIndex = SystemIndexer()->GetIndex(SystemIndexer::E_COMPONENT);

				_initialiseCalled = true;
			}
		}



		void Component::PreDestructor()
		{
			if (!_preDestructorCalled)
			{
				SystemIndexer()->ReturnIndex(_systemIndex);
				_preDestructorCalled = true;
			}
		}



		void Component::Start() { }
		void Component::Update() 
		{
			if (!_startCalled) [[unlikely]]
			{
				_startCalled = true;
				Start();
			}
		}

		void Component::PhysicsUpdate() { }
		void Component::Render(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix) { }

		std::shared_ptr<Transform> Component::Transform() { return _transform.lock(); }
		std::shared_ptr<Component> Component::Self() { return _self.lock(); }
		std::shared_ptr<Engine::Core> Component::Core() { return _core.lock(); }
		std::shared_ptr<SystemIndexer> Component::SystemIndexer() { return _systemIndexer.lock(); }
		std::shared_ptr<Engine::Scene> Component::Scene() { return _scene.lock(); }
		std::shared_ptr<Engine::Entity> Component::Entity() { return _entity.lock(); }
		std::shared_ptr<Engine::TimeManager> Component::TimeManager() { return _timeManager.lock(); }
		std::shared_ptr<Engine::Physics::PhysicsManager> Component::PhysicsManager() { return _physicsManager.lock(); }
		std::shared_ptr<Engine::Inputs> Component::Input() { return _inputs.lock(); }
	}
}