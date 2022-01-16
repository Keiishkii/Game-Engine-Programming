#include "SamusController.h"
#include "game/components/Rocket.h"

namespace Game
{
	namespace Components
	{
		void SamusController::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			_rocketAudioSource = Entity()->AddComponent<Engine::Components::AudioSource>();
			_rocketAudioSource->SetAudioClip(Core()->ResourceManager()->FindAsset<ResourceManagement::AudioClip>("- audio/sfx/samus/rocket.ogg"));

			_superRocketAudioSource = Entity()->AddComponent<Engine::Components::AudioSource>();
			_superRocketAudioSource->SetAudioClip(Core()->ResourceManager()->FindAsset<ResourceManagement::AudioClip>("- audio/sfx/samus/super_rocket.ogg"));
		}

		void SamusController::Start()
		{
			std::shared_ptr<Engine::Entity> cameraEntity = Scene()->FindEntity("Camera");
			_cameraTransform = cameraEntity->Transform();
		}

		void SamusController::Update()
		{
			std::shared_ptr<Inputs> inputs = Input();

			MovementControls(inputs);
			WeaponControls(inputs);
		}

		void SamusController::WeaponControls(std::shared_ptr<Inputs> inputs)
		{
			if (inputs->KeyDown(inputs->F))
			{
				if (!inputs->KeyHeld(inputs->LSHIFT))
				{
					_rocketAudioSource->PlayAudioClip();
					SpawnRocket();
				}
				else
				{
					_superRocketAudioSource->PlayAudioClip();
					SpawnSuperRocket();
				}
			}
		}

		void SamusController::SpawnRocket()
		{
			std::shared_ptr<Engine::Entity> rocketEntity = Scene()->AddEntity("Rocket");
			std::shared_ptr<Game::Components::Rocket> rocketComponent = rocketEntity->AddComponent<Game::Components::Rocket>();
			
			glm::vec3 samusPosition = Transform()->Position();
			glm::quat cameraRotation = _cameraTransform->Rotation();

			glm::vec3 lookDirection = cameraRotation * glm::vec3(0, 0, -1);
			lookDirection = glm::normalize(lookDirection);

			rocketComponent->SetFlightVector(lookDirection * 10.0f);

			std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/entities/missile.fbx");
			{
				mesh->SetMaterial(0, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/missile.material"));
			}

			std::shared_ptr<Engine::Components::MeshRenderer> meshRenderer = rocketEntity->AddComponent<Engine::Components::MeshRenderer>(mesh);

			std::shared_ptr<Engine::Components::Transform> transform = rocketEntity->Transform();
				transform->Position() = samusPosition + glm::vec3(0, 2, 0) + (lookDirection * 0.5f);
				transform->Rotation() = glm::quatLookAt(lookDirection, glm::vec3(0, 1, 0)) * glm::quat(glm::vec3(0, M_PI, 0));
				transform->Scale() = glm::vec3(0.1f);
		}

		void SamusController::SpawnSuperRocket()
		{
			std::shared_ptr<Engine::Entity> rocketEntity = Scene()->AddEntity("Super Rocket");
			std::shared_ptr<Game::Components::Rocket> rocketComponent = rocketEntity->AddComponent<Game::Components::Rocket>();

			glm::vec3 samusPosition = Transform()->Position();
			glm::quat cameraRotation = _cameraTransform->Rotation();

			glm::vec3 lookDirection = cameraRotation * glm::vec3(0, 0, -1);
			lookDirection = glm::normalize(lookDirection);

			rocketComponent->SetFlightVector(lookDirection * 10.0f);

			std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/entities/super_missile.fbx");
			{
				mesh->SetMaterial(0, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/super_missile.material"));
			}

			std::shared_ptr<Engine::Components::MeshRenderer> meshRenderer = rocketEntity->AddComponent<Engine::Components::MeshRenderer>(mesh);

			std::shared_ptr<Engine::Components::Transform> transform = rocketEntity->Transform();			
				transform->Position() = samusPosition + glm::vec3(0, 2, 0) + (lookDirection * 0.5f);
				transform->Rotation() = glm::quatLookAt(lookDirection, glm::vec3(0, 1, 0)) * glm::quat(glm::vec3(0, M_PI, 0));
				transform->Scale() = glm::vec3(0.1f);
		}




		void SamusController::MovementControls(std::shared_ptr<Inputs> inputs)
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
				Transform()->Rotation() = lookRotation * glm::quat(glm::vec3((M_PI / 2.0f), M_PI, 0.0f));
			}
		}

		void SamusController::SetMovementSpeed(float speed) { _movementSpeed = speed; }
	}
}