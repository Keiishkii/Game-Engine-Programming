#include "Scene_2.h"

#include "game/components/camera_controllers/ThirdPersonCameraController.h"
#include "game/components/player_controllers/SamusController.h"
#include "game/components/PostProcessorEffects.h"
#include "game/components/SceneSwitcher.h"

namespace Game
{
	namespace Scenes
	{
		void Scene_2::LoadScene()
		{
			Skybox() = Core()->ResourceManager()->FindAsset<ResourceManagement::SkyboxMaterial>("- materials/skybox/night_sky.material");


			CreateEntity_SceneManager();

			CreateEntity_Samus();
			CreateEntity_Kraid();

			CreateEntity_Camera();

			CreateEntity_Lighting();
			CreateEntity_Enviroment();

			PreLoadResources();
		}



		void Scene_2::CreateEntity_SceneManager()
		{
			std::shared_ptr<Entity> sceneManagerEntity = AddEntity("Scene_Manager");
			std::shared_ptr<Game::Components::SceneSwitcher> sceneSwitcher = sceneManagerEntity->AddComponent<Game::Components::SceneSwitcher>();
			std::shared_ptr<Game::Components::PostProcessorEffects> postProcessingEffector = sceneManagerEntity->AddComponent<Game::Components::PostProcessorEffects>();
		}

		void Scene_2::CreateEntity_Samus()
		{
			std::shared_ptr<Entity> samusEntity = AddEntity("Player");
			{
				std::shared_ptr<Engine::Components::AudioListener> audioListener = samusEntity->AddComponent<Engine::Components::AudioListener>();

				std::shared_ptr<Engine::Components::AudioSource> musicAudioSource = samusEntity->AddComponent<Engine::Components::AudioSource>();
				musicAudioSource->SetAudioClip(Core()->ResourceManager()->FindAsset<ResourceManagement::AudioClip>("- audio/music/brinstar.ogg"));
				musicAudioSource->PlayOnStart(true);
				musicAudioSource->Looping(true);

				std::shared_ptr<Game::Components::SamusController> samusController = samusEntity->AddComponent<Game::Components::SamusController>();
				samusController->SetMovementSpeed(6.0f);

				std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/entities/samus.fbx");
				{
					mesh->SetMaterial(0, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/eye_L.material"));
					mesh->SetMaterial(1, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/eye_LD.material"));
					mesh->SetMaterial(2, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/eye_LG.material"));
					mesh->SetMaterial(3, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/eye_LL.material"));
					mesh->SetMaterial(4, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/samus_emi.material"));
					mesh->SetMaterial(5, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/metal_gun.material"));
					mesh->SetMaterial(6, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/metal_morph.material"));
					mesh->SetMaterial(7, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/metal_samus.material"));
				}

				std::shared_ptr<Engine::Components::MeshRenderer> meshRenderer = samusEntity->AddComponent<Engine::Components::MeshRenderer>(mesh);

				samusEntity->Transform()->Position() = glm::vec3(0, -0.1f, 0);
				samusEntity->Transform()->Rotation() = glm::quat(glm::vec3((M_PI / 2.0f), 0.0f, 0.0f));
				samusEntity->Transform()->Scale() = glm::vec3(0.1f, 0.1f, 0.1f);
			}
		}

		void Scene_2::CreateEntity_Kraid()
		{
			std::shared_ptr<Entity> kraidEntity = AddEntity("Kraid");
			{
				std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/entities/kraid.fbx");
				{
					mesh->SetMaterial(0, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/kraid/kraid_body.material"));
					mesh->SetMaterial(1, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/kraid/kraid_special.material"));
				}

				std::shared_ptr<Engine::Components::MeshRenderer> meshRenderer = kraidEntity->AddComponent<Engine::Components::MeshRenderer>(mesh);

				kraidEntity->Transform()->Position() = glm::vec3(0, -25, -20);
				kraidEntity->Transform()->Rotation() = glm::quat(glm::vec3(((M_PI / 2.0f) * 1.25f), 0.0f, 0.0f));
				kraidEntity->Transform()->Scale() = glm::vec3(0.25f, 0.25f, 0.25f);
			}
		}

		void Scene_2::CreateEntity_Camera()
		{
			std::shared_ptr<Entity> cameraEntity = AddEntity("Camera");
			{
				std::shared_ptr<Engine::Components::Camera> camera = cameraEntity->AddComponent<Engine::Components::Camera>();
				std::shared_ptr<Game::Components::ThirdPersonCameraController> cameraController = cameraEntity->AddComponent<Game::Components::ThirdPersonCameraController>();

				cameraController->SetOrbitOffset(glm::vec3(0, 2.3f, 0));

				cameraEntity->Transform()->Position() = glm::vec3(0, 0, 0);
				cameraEntity->Transform()->Rotation() = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
			}
		}

		void Scene_2::CreateEntity_Lighting()
		{
			std::shared_ptr<Entity> light_1 = AddEntity("Light_1");
			{
				std::shared_ptr<Engine::Components::Light> lightComponent = light_1->AddComponent<Engine::Components::Light>();
				{
					lightComponent->Colour() = glm::vec3(0.75f, 1.0f, 1.0f);
					lightComponent->Intensity() = 12000000.0f;
				}

				light_1->Transform()->Position() = glm::vec3(-1000, 1000, 1000);
			}
		}

		void Scene_2::CreateEntity_Enviroment()
		{
			std::shared_ptr<Entity> enviromentEntity = AddEntity("Enviroment");

			std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/enviroments/result_stage.fbx");
			{
				mesh->SetMaterial(1, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/result_stage/tiles.material"));
				mesh->SetMaterial(2, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/result_stage/grass_1.material"));
				mesh->SetMaterial(3, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/result_stage/grass_2.material"));
				mesh->SetMaterial(5, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/result_stage/leaves.material"));
				mesh->SetMaterial(6, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/result_stage/flowers.material"));
				mesh->SetMaterial(7, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/result_stage/flowers.material"));
				mesh->SetMaterial(11, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/result_stage/rocks.material"));
				mesh->SetMaterial(12, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/result_stage/ground.material"));
			}

			std::shared_ptr<Engine::Components::MeshRenderer> meshRenderer = enviromentEntity->AddComponent<Engine::Components::MeshRenderer>(mesh);
			enviromentEntity->Transform()->Scale() = glm::vec3(0.1f, 0.1f, 0.1f);
		}

		void Scene_2::PreLoadResources()
		{
				// Missile
			Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/entities/missile.fbx");
			Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/missile.material");
			Core()->ResourceManager()->FindAsset<ResourceManagement::AudioClip>("- audio/sfx/samus/rocket.ogg");

				// Super Missile
			Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/entities/super_missile.fbx");
			Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/samus/super_missile.material");
			Core()->ResourceManager()->FindAsset<ResourceManagement::AudioClip>("- audio/sfx/samus/super_rocket.ogg");

			Core()->ResourceManager()->FindAsset<ResourceManagement::AudioClip>("- audio/sfx/samus/rocket_flight.ogg");
		}
	}
}