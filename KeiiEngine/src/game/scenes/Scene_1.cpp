#include "Scene_1.h"

#include "game/components/camera_controllers/ThirdPersonCameraController.h"
#include "game/components/player_controllers/ShulkController.h"
#include "game/components/PostProcessorEffects.h"
#include "game/components/SceneSwitcher.h"

namespace Game
{
	namespace Scenes
	{
		void Scene_1::LoadScene()
		{
			Skybox() = Core()->ResourceManager()->FindAsset<ResourceManagement::SkyboxMaterial>("- materials/skybox/cloudy_sky.material");


			CreateEntity_SceneManager();

			CreateEntity_Player();
			CreateEntity_Camera();

			CreateEntity_Lighting();
			CreateEntity_Enviroment();
		}



		void Scene_1::CreateEntity_SceneManager()
		{
			std::shared_ptr<Entity> sceneManagerEntity = AddEntity("Scene_Manager");
			std::shared_ptr<Game::Components::SceneSwitcher> sceneSwitcher = sceneManagerEntity->AddComponent<Game::Components::SceneSwitcher>();
			std::shared_ptr<Game::Components::PostProcessorEffects> postProcessingEffector = sceneManagerEntity->AddComponent<Game::Components::PostProcessorEffects>();
		}

		void Scene_1::CreateEntity_Player()
		{
			std::shared_ptr<Entity> shulkEntity = AddEntity("Player");
			{
				std::shared_ptr<Engine::Components::AudioListener> audioListener = shulkEntity->AddComponent<Engine::Components::AudioListener>();

				std::shared_ptr<Engine::Components::AudioSource> musicAudioSource = shulkEntity->AddComponent<Engine::Components::AudioSource>();
				musicAudioSource->SetAudioClip(Core()->ResourceManager()->FindAsset<ResourceManagement::AudioClip>("- audio/music/Gaur Plains.ogg"));
				musicAudioSource->PlayOnStart(true);
				musicAudioSource->Looping(true);

				std::shared_ptr<Game::Components::ShulkController> shulkController = shulkEntity->AddComponent<Game::Components::ShulkController>();
				shulkController->SetMovementSpeed(10.0f);

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

				std::shared_ptr<Engine::Components::MeshRenderer> meshRenderer = shulkEntity->AddComponent<Engine::Components::MeshRenderer>(mesh);

				shulkEntity->Transform()->Position() = glm::vec3(72, 6.5f, -160);
				shulkEntity->Transform()->Scale() = glm::vec3(0.1f, 0.1f, 0.1f);
			}
		}

		void Scene_1::CreateEntity_Camera()
		{
			std::shared_ptr<Entity> cameraEntity = AddEntity("Camera");
			{
				std::shared_ptr<Engine::Components::Camera> camera = cameraEntity->AddComponent<Engine::Components::Camera>();
				std::shared_ptr<Game::Components::ThirdPersonCameraController> cameraController = cameraEntity->AddComponent<Game::Components::ThirdPersonCameraController>();

				cameraController->SetOrbitOffset(glm::vec3(0, 2.3f, 0));

				cameraEntity->Transform()->Position() = glm::vec3(0, 0, 0);
				cameraEntity->Transform()->Rotation() = glm::quat(glm::vec3(-0.25f, 0.0f, 0.0f));
			}
		}

		void Scene_1::CreateEntity_Lighting()
		{
			std::shared_ptr<Entity> light_1 = AddEntity("Light_1");
			{
				std::shared_ptr<Engine::Components::Light> lightComponent = light_1->AddComponent<Engine::Components::Light>();
				{
					lightComponent->Colour() = glm::vec3(1, 1, 1);
					lightComponent->Intensity() = 12000000.0f;
				}

				light_1->Transform()->Position() = glm::vec3(-1000, 1000, 1000);
			}
		}

		void Scene_1::CreateEntity_Enviroment()
		{
			std::shared_ptr<Entity> mapEntity = AddEntity("Level Geometry");
			{
				std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/enviroments/gaur_plains.fbx");
				{
					mesh->SetMaterial(0, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/waves.material"));
					mesh->SetMaterial(1, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/water_1.material"));
					mesh->SetMaterial(2, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/water_2.material"));
					mesh->SetMaterial(3, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/ore.material"));
					mesh->SetMaterial(4, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_2.material"));
					mesh->SetMaterial(5, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/foliage.material"));
					mesh->SetMaterial(6, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/tree_1.material"));
					mesh->SetMaterial(8, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_1.material"));
					mesh->SetMaterial(9, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_4.material"));
					mesh->SetMaterial(7, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_2.material"));
					mesh->SetMaterial(10, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_6.material"));
					mesh->SetMaterial(11, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_3.material"));
		/*No Mat*/	mesh->SetMaterial(12, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/colours/red.material"));
					mesh->SetMaterial(13, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_4.material"));
					mesh->SetMaterial(14, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(15, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(16, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(17, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_1.material"));
					mesh->SetMaterial(18, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_1.material"));
					mesh->SetMaterial(19, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(20, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/foliage.material"));
					mesh->SetMaterial(21, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_2.material"));
					mesh->SetMaterial(22, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_4.material"));
					mesh->SetMaterial(23, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/bridge_wood.material"));
					mesh->SetMaterial(24, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/tree_2.material"));
					mesh->SetMaterial(25, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_3.material"));
					mesh->SetMaterial(26, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_3.material"));
					mesh->SetMaterial(27, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_2.material"));
					mesh->SetMaterial(28, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_5.material"));
					mesh->SetMaterial(29, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_2.material"));
					mesh->SetMaterial(30, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(31, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(32, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(33, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(34, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_3.material"));
					mesh->SetMaterial(35, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(36, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(37, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_1.material"));
					mesh->SetMaterial(38, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_4.material"));
					mesh->SetMaterial(39, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/rocky_2.material"));
					mesh->SetMaterial(40, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/bridge_metal.material"));
					mesh->SetMaterial(41, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_7.material"));
					mesh->SetMaterial(42, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_6.material"));
					mesh->SetMaterial(43, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/chiseled_stone_8.material"));
					mesh->SetMaterial(44, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/grass.material"));
					mesh->SetMaterial(45, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/water_2.material"));
					mesh->SetMaterial(46, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/vines.material"));
					mesh->SetMaterial(47, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/water_3.material"));
					mesh->SetMaterial(48, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/waterfall.material"));
					mesh->SetMaterial(49, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/waterfall.material"));
					mesh->SetMaterial(50, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/tree_3.material"));
					mesh->SetMaterial(51, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/water_2.material"));
					mesh->SetMaterial(52, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/waves.material"));
					mesh->SetMaterial(53, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/water_2.material"));
					mesh->SetMaterial(54, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/sky.material"));
					mesh->SetMaterial(55, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/enviroments/gaur_plains/water_1.material"));
				}

				std::shared_ptr<Engine::Components::MeshRenderer> meshRenderer = mapEntity->AddComponent<Engine::Components::MeshRenderer>(mesh);

				mapEntity->Transform()->Position() = glm::vec3(-10, -20, 25);
				mapEntity->Transform()->Rotation() = glm::quat(glm::vec3(0.0f, (M_PI / 2), 0.0f));
				mapEntity->Transform()->Scale() = glm::vec3(1.0f, 1.0f, 1.0f);
			}
		}
	}
}