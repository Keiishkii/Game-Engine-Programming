#include "Scene_3.h"

#include "game/components/camera_controllers/ThirdPersonCameraController.h"
#include "game/components/SceneSwitcher.h"

namespace Game
{
	namespace Scenes
	{
		void Scene_3::LoadScene()
		{
			Skybox() = Core()->ResourceManager()->FindAsset<ResourceManagement::SkyboxMaterial>("- materials/skybox/night_sky.material");


			CreateEntity_SceneManager();

			CreateEntity_Player();
			CreateEntity_Camera();
		}



		void Scene_3::CreateEntity_SceneManager()
		{
			std::shared_ptr<Entity> sceneManagerEntity = AddEntity("Scene_Manager");
			std::shared_ptr<Game::Components::SceneSwitcher> sceneSwitcher = sceneManagerEntity->AddComponent<Game::Components::SceneSwitcher>();
		}

		void Scene_3::CreateEntity_Player()
		{
			std::shared_ptr<Entity> playerEntity = AddEntity("Player");
			{
				std::shared_ptr<Engine::Components::AudioListener> audioListener = playerEntity->AddComponent<Engine::Components::AudioListener>();

				std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/entities/shulk.fbx");
				{
					mesh->SetMaterial(0, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/eye.material"));
					mesh->SetMaterial(4, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/eye.material"));
					mesh->SetMaterial(8, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/hair.material"));
					mesh->SetMaterial(9, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/skin.material"));
					mesh->SetMaterial(10, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/metal_decals.material"));
					mesh->SetMaterial(11, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/clothing.material"));
					mesh->SetMaterial(12, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/boots.material"));
					mesh->SetMaterial(13, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/monado.material"));
					mesh->SetMaterial(14, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/entities/shulk/skin.material"));
				}

				std::shared_ptr<Engine::Components::MeshRenderer> meshRenderer = playerEntity->AddComponent<Engine::Components::MeshRenderer>(mesh);

				playerEntity->Transform()->Position() = glm::vec3(0, 0, 0);
				playerEntity->Transform()->Scale() = glm::vec3(0.1f, 0.1f, 0.1f);
			}
		}

		void Scene_3::CreateEntity_Camera()
		{
			std::shared_ptr<Entity> cameraEntity = AddEntity("Camera");
			{
				std::shared_ptr<Engine::Components::Camera> camera = cameraEntity->AddComponent<Engine::Components::Camera>();
				std::shared_ptr<Game::Components::ThirdPersonCameraController> cameraController = cameraEntity->AddComponent<Game::Components::ThirdPersonCameraController>();

				cameraEntity->Transform()->Position() = glm::vec3(0, 0, 0);
				cameraEntity->Transform()->Rotation() = glm::quat(glm::vec3(-0.25f, 0.0f, 0.0f));
			}
		}
	}
}