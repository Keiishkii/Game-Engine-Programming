#include "ThirdPersonCameraController.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <algorithm>

namespace Game
{
	namespace Components
	{
		void ThirdPersonCameraController::Start()
		{
			std::shared_ptr<Engine::Entity> playerEntity = Scene()->FindEntity("Player");

			if (playerEntity)
			{
				_orbitTarget = Scene()->FindEntity("Player")->Transform();
				std::shared_ptr<Engine::Components::Transform> orbitTarget = _orbitTarget.lock();

				glm::vec3 orbitTargetPosition = _orbitTarget.lock()->Position();
				glm::vec3 normalisedOrbitDisplacement = glm::vec3(
					sin(_theta) * cos(_phi),
					sin(_phi),
					cos(_theta) * cos(_phi));

				Transform()->Position() = _orbitOffset + orbitTargetPosition + (normalisedOrbitDisplacement * _currentOrbitDistance);
				Transform()->Rotation() = glm::identity<glm::quat>() * glm::quatLookAt(glm::normalize(orbitTargetPosition + _orbitOffset - Transform()->Position()), glm::vec3(0, 1, 0));
			}
		}

		void ThirdPersonCameraController::Update()
		{
			std::shared_ptr<Engine::Components::Transform> orbitTarget = _orbitTarget.lock();
			if (orbitTarget)
			{
				RecalcualteOrbitAngle();
				RecalcualteOrbitDistance();



				glm::vec3 orbitTargetPosition = orbitTarget->Position();
				glm::vec3 normalisedOrbitDisplacement = glm::vec3(
					sin(_theta) * cos(_phi),
					sin(_phi),
					cos(_theta) * cos(_phi));

				glm::vec3 prevousFrameNormalisedOrbitDisplacement = ((Transform()->Position() - _orbitOffset - orbitTargetPosition) / _currentOrbitDistance);
				glm::vec3 lerpedOrbitDisplacement = Engine::Maths::Lerp(prevousFrameNormalisedOrbitDisplacement, normalisedOrbitDisplacement, 0.075f);

				glm::vec3 cameraPosition = orbitTargetPosition + _orbitOffset + (lerpedOrbitDisplacement * _currentOrbitDistance);
				Transform()->Position() = cameraPosition;
				Transform()->Rotation() = glm::identity<glm::quat>() * glm::quatLookAt(glm::normalize(orbitTargetPosition + _orbitOffset - cameraPosition), glm::vec3(0, 1, 0));
			}
		}

		void ThirdPersonCameraController::RecalcualteOrbitAngle()
		{
			glm::vec2 mouseDelta = Input()->MousePosition();

			_theta -= (mouseDelta.x * _orbitRotationSpeed);
			_phi += (mouseDelta.y * _orbitRotationSpeed);

			_phi = std::max(-1.0f, std::min(_phi, 1.0f));
		}

		void ThirdPersonCameraController::RecalcualteOrbitDistance()
		{
			float scrollDelta = Input()->MouseScrollDelta();

			_desiredOrbitDistance += (scrollDelta * _orbitZoomSpeed);

			_desiredOrbitDistance = std::max(_minOrbitDistance, std::min(_desiredOrbitDistance, _maxOrbitDistance));
			_currentOrbitDistance = Engine::Maths::Lerp(_currentOrbitDistance, _desiredOrbitDistance, 0.075f);
		}

		void ThirdPersonCameraController::SetOrbitTarget(std::shared_ptr<Engine::Components::Transform> transform)
		{
			_orbitTarget = transform;
		}
		void ThirdPersonCameraController::SetOrbitTarget(std::shared_ptr<Engine::Entity> entity)
		{
			_orbitTarget = entity->Transform();
		}
		
		void ThirdPersonCameraController::SetOrbitOffset(glm::vec3 offset)
		{
			_orbitOffset = offset;
		}
	}
}