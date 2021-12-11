#include "CustomScene.h"

#include "game/components/PlayerController.h"
#include "game/components/CameraController.h"
#include "game/components/ShaderTextureSampler.h"

namespace Game
{
	void CustomScene::LoadScene()
	{
		Skybox() = Core()->ResourceManager()->FindAsset<ResourceManagement::SkyboxMaterial>("- materials/skybox/sky.material");


		CreateMapEntity();

		CreatePlayerEntity();
		CreateCameraEntity();

		CreateLights();
		CreateReflectionProbes();

		CreateDebuggingEntity();
	}

	void CustomScene::CreateReflectionProbes()
	{
		std::vector<glm::vec3> reflectionProbeLocations = 
		{
			glm::vec3(-10, -20, 31),
			glm::vec3(-10, -15, -12),
			glm::vec3(30, -10, -44),
			glm::vec3(32, 0, -130),
			glm::vec3(32, 0, -130),
			glm::vec3(-74, 7, -152),
			glm::vec3(-53, 28, -243),
			glm::vec3(111, 30, -236),
			glm::vec3(240, 16, -165),
			glm::vec3(118, -3, -81)
		};

		for (int i = 0; i < reflectionProbeLocations.size(); i++)
		{
			std::shared_ptr<Entity> reflectionProbe = AddEntity("Reflection Probe: " + i);
			{
				std::shared_ptr<Components::ReflectionProbe> reflectionProbeComponent = reflectionProbe->AddComponent<Components::ReflectionProbe>();
				reflectionProbe->Transform()->Position() = reflectionProbeLocations[i];
			}
		}
	}

	void CustomScene::CreateLights()
	{
		///*
		std::shared_ptr<Entity> light_1 = AddEntity("Light_1");
		{
			std::shared_ptr<Components::Light> lightComponent = light_1->AddComponent<Components::Light>();
			{
				lightComponent->Colour() = glm::vec3(1, 1, 1);
				lightComponent->Intensity() = 12000000.0f;
			}

			light_1->Transform()->Position() = glm::vec3(-1000, 1000, 1000);
		}
		//*/

		///*
		std::shared_ptr<Entity> light_2 = AddEntity("Light_2");
		{
			std::shared_ptr<Components::Light> lightComponent = light_2->AddComponent<Components::Light>();
			{
				lightComponent->Colour() = glm::vec3(1, 1, 1);
				lightComponent->Intensity() = 25.0f;
			}

			light_2->Transform()->Position() = glm::vec3(-10, -10, -10);
		}
		//*/

		/*
		std::shared_ptr<Entity> light_3 = AddEntity("Light_3");
		{
			std::shared_ptr<Components::Light> lightComponent = light_3->AddComponent<Components::Light>();
			{
				lightComponent->Colour() = glm::vec3(10, 10, 10);
				lightComponent->Intensity() = 1.0f;
			}

			light_3->Transform()->Position() = glm::vec3(30, 10, -35);
		}
		//*/
	}

	void CustomScene::CreateDebuggingEntity()
	{
		std::shared_ptr<Entity> debuggingEntity = AddEntity("Debugger");
		{
			std::shared_ptr<Game::ShaderTextureSampler> shaderTextureSampler = debuggingEntity->AddComponent<Game::ShaderTextureSampler>();
		}
	}

	void CustomScene::CreateCameraEntity()
	{
		std::shared_ptr<Entity> cameraEntity = AddEntity("Camera");
		{
			std::shared_ptr<Components::Camera> camera = cameraEntity->AddComponent<Components::Camera>();
			std::shared_ptr<Game::CameraController> cameraController = cameraEntity->AddComponent<Game::CameraController>();

			cameraEntity->Transform()->Position() = glm::vec3(0, 0, 0);
			cameraEntity->Transform()->Rotation() = glm::quat(glm::vec3(-0.25f, 0.0f, 0.0f));
		}
	}

	void CustomScene::CreatePlayerEntity()
	{
		std::shared_ptr<Entity> playerEntity = AddEntity("Player");
		{
			std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/shulk.fbx");
			{
				mesh->SetMaterial(0, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/eye.material"));
				mesh->SetMaterial(4, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/eye.material"));
				mesh->SetMaterial(8, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/hair.material"));
				mesh->SetMaterial(9, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/skin.material"));
				mesh->SetMaterial(10, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/metal_decals.material"));
				mesh->SetMaterial(11, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/clothing.material"));
				mesh->SetMaterial(12, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/boots.material"));
				mesh->SetMaterial(13, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/monado.material"));
				mesh->SetMaterial(14, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/skin.material"));
			}

			std::shared_ptr<Components::MeshRenderer> meshRenderer = playerEntity->AddComponent<Components::MeshRenderer>(mesh);
			std::shared_ptr<Game::PlayerController> playerController = playerEntity->AddComponent<Game::PlayerController>();

			playerEntity->Transform()->Position() = glm::vec3(0, 0, 0);
			playerEntity->Transform()->Scale() = glm::vec3(0.1f, 0.1f, 0.1f);
		}
	}

	void CustomScene::CreateMapEntity()
	{
		std::shared_ptr<Entity> mapEntity = AddEntity("Level Geometry");
		{
			std::shared_ptr<ResourceManagement::Model> mesh = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/gaur_plains.fbx");
			{
				mesh->SetMaterial(0, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/waves.material"));
				mesh->SetMaterial(1, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_1.material"));
				mesh->SetMaterial(2, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_2.material"));
				mesh->SetMaterial(3, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/ore.material"));
				mesh->SetMaterial(4, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
				mesh->SetMaterial(5, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/foliage.material"));
				mesh->SetMaterial(6, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/tree_1.material"));
				mesh->SetMaterial(8, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_1.material"));
				mesh->SetMaterial(9, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_4.material"));
				mesh->SetMaterial(7, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_2.material"));
				mesh->SetMaterial(10, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_6.material"));
				mesh->SetMaterial(11, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_3.material"));
				/*No Mat*/	mesh->SetMaterial(12, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/colours/red.material"));
				mesh->SetMaterial(13, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_4.material"));
				mesh->SetMaterial(14, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(15, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(16, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(17, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_1.material"));
				mesh->SetMaterial(18, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_1.material"));
				mesh->SetMaterial(19, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(20, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/foliage.material"));
				mesh->SetMaterial(21, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
				mesh->SetMaterial(22, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_4.material"));
				mesh->SetMaterial(23, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/bridge_wood.material"));
				mesh->SetMaterial(24, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/tree_2.material"));
				mesh->SetMaterial(25, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_3.material"));
				mesh->SetMaterial(26, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_3.material"));
				mesh->SetMaterial(27, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
				mesh->SetMaterial(28, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_5.material"));
				mesh->SetMaterial(29, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
				mesh->SetMaterial(30, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(31, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(32, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(33, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(34, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_3.material"));
				mesh->SetMaterial(35, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(36, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(37, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_1.material"));
				mesh->SetMaterial(38, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_4.material"));
				mesh->SetMaterial(39, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
				mesh->SetMaterial(40, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/bridge_metal.material"));
				mesh->SetMaterial(41, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_7.material"));
				mesh->SetMaterial(42, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_6.material"));
				mesh->SetMaterial(43, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_8.material"));
				mesh->SetMaterial(44, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
				mesh->SetMaterial(45, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_2.material"));
				mesh->SetMaterial(46, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/vines.material"));
				mesh->SetMaterial(47, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_3.material"));
				mesh->SetMaterial(48, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/waterfall.material"));
				mesh->SetMaterial(49, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/waterfall.material"));
				mesh->SetMaterial(50, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/tree_3.material"));
				mesh->SetMaterial(51, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_2.material"));
				mesh->SetMaterial(52, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/waves.material"));
				mesh->SetMaterial(53, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_2.material"));
				mesh->SetMaterial(54, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/sky.material"));
				mesh->SetMaterial(55, Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_1.material"));
			}

			std::shared_ptr<Components::MeshRenderer> meshRenderer = mapEntity->AddComponent<Components::MeshRenderer>(mesh);

			mapEntity->Transform()->Position() = glm::vec3(-10, -20, 25);
			mapEntity->Transform()->Rotation() = glm::quat(glm::vec3(0.0f, (M_PI / 2), 0.0f));
			mapEntity->Transform()->Scale() = glm::vec3(0.5f, 0.5f, 0.5f);
		}
	}
}