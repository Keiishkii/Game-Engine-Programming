#include "Component.h"
#include "Camera.h"
#include "Transform.h"
#include "engine/Entity.h"
#include "engine/Core.h"
#include "engine/TimeManager.h"
#include "engine/InputManager.h"
#include "engine/Inputs.h"

namespace Engine
{
	namespace Components
	{
		void Component::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			self->_self = self;
			self->_entity = entity;
			self->_transform = entity->Transform();
			self->_core = entity->Core();
			self->_timeManager = entity->Core()->TimeManager();
			self->_inputs = entity->Core()->InputManager()->Input();
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
		std::shared_ptr<Engine::Entity> Component::Entity() { return _entity.lock(); }
		std::shared_ptr<Engine::TimeManager> Component::Time() { return _timeManager.lock(); }
		std::shared_ptr<Engine::Inputs> Component::Input() { return _inputs.lock(); }
	}
}