#include "ShulkController.h"

namespace Game
{
	namespace Components
	{
		void ShulkController::Start()
		{
			std::shared_ptr<Engine::Entity> cameraEntity = Scene()->FindEntity("Camera");
			_cameraTransform = cameraEntity->Transform();
		}

		void ShulkController::Update()
		{
			std::shared_ptr<Inputs> inputs = Input();

			MovementControls(inputs);
		}

		void ShulkController::MovementControls(std::shared_ptr<Inputs> inputs)
		{
			bool isMoving = false;
			glm::vec3 viewSpaceDirection = glm::vec3(0);

			if (inputs->KeyHeld(inputs->W))
			{
				viewSpaceDirection -= glm::vec3(0, 0, 1);
				isMoving = true;
			}

			if (inputs->KeyHeld(inputs->S))
			{
				viewSpaceDirection += glm::vec3(0, 0, 1);
				isMoving = true;
			}

			if (inputs->KeyHeld(inputs->D))
			{
				viewSpaceDirection += glm::vec3(1, 0, 0);
				isMoving = true;
			}

			if (inputs->KeyHeld(inputs->A))
			{
				viewSpaceDirection -= glm::vec3(1, 0, 0);
				isMoving = true;
			}

			if (inputs->KeyHeld(inputs->SPACE))
			{
				viewSpaceDirection += glm::vec3(0, 1, 0);
				isMoving = true;
			}

			if (inputs->KeyHeld(inputs->LSHIFT))
			{
				viewSpaceDirection -= glm::vec3(0, 1, 0);
				isMoving = true;
			}

			if (isMoving && glm::length(viewSpaceDirection) > 0.1f)
			{
				viewSpaceDirection = glm::normalize(viewSpaceDirection);

				glm::vec3 samusPosition = Transform()->Position();
				glm::vec3 cameraPosition = _cameraTransform->Position();

				glm::vec3 lookDirection = samusPosition - cameraPosition;
				lookDirection.y = 0;
				lookDirection = glm::normalize(lookDirection);

				glm::quat lookRotation = glm::quatLookAt(lookDirection, glm::vec3(0, 1, 0));
				glm::vec3 motionVector = (lookRotation * viewSpaceDirection) * _movementSpeed * TimeManager()->DeltaTime();

				Transform()->Position() = samusPosition + motionVector;
				Transform()->Rotation() = lookRotation * glm::quat(glm::vec3(0, M_PI, 0.0f));
			}
		}

		void ShulkController::SetMovementSpeed(float speed) { _movementSpeed = speed; }
	}
}