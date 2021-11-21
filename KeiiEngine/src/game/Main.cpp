#include <iostream>
#include <math.h>

#include "engine/KeiiEngine.h"
#include "game/components/PlayerController.h"
#include "game/components/CameraController.h"

#define _USE_MATH_DEFINES

std::shared_ptr<Entity> CreateCameraEntity(std::shared_ptr<Core> core);
std::shared_ptr<Entity> CreatePlayerEntity(std::shared_ptr<Core> core);
std::shared_ptr<Entity> CreateMapEntity(std::shared_ptr<Core> core);

int main()
{
	std::cout << "\033[0m" << " - [ENGINE START] - " << std::endl;

	std::shared_ptr<Core> core = Core::Initialise(144, 50);

	std::shared_ptr<ResourceManagement::TextureCubeMap> skybox = core->ResourceManager()->FindAsset<ResourceManagement::TextureCubeMap>("- textures/skybox/sky.png");

	std::shared_ptr<Entity> player = CreatePlayerEntity(core);
	std::shared_ptr<Entity> camera = CreateCameraEntity(core);
	std::shared_ptr<Entity> map = CreateMapEntity(core);
	

	core->Start();

	return 0;
}

std::shared_ptr<Entity> CreateCameraEntity(std::shared_ptr<Core> core)
{
	std::shared_ptr<Entity> cameraEntity = core->AddEntity("Camera");
	{
		std::shared_ptr<Components::Camera> camera = cameraEntity->AddComponent<Components::Camera>();
		{
			//camera->SkyboxMaterial() = core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/skybox/sky.material");
		}

		std::shared_ptr<Game::CameraController> cameraController = cameraEntity->AddComponent<Game::CameraController>();

		cameraEntity->Transform()->Position() = glm::vec3(0, 2, 0);
		cameraEntity->Transform()->Rotation() = glm::quat(glm::vec3(-0.25f, 0.0f, 0.0f));
	}

	return cameraEntity;
}

std::shared_ptr<Entity> CreatePlayerEntity(std::shared_ptr<Core> core)
{
	std::shared_ptr<Entity> playerEntity = core->AddEntity("Player");
	{
		std::shared_ptr<ResourceManagement::Model> mesh = core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/shulk.fbx");
		{
			mesh->SetMaterial(0,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/eye.material"));
			mesh->SetMaterial(4,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/eye.material"));
			mesh->SetMaterial(8,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/hair.material"));
			mesh->SetMaterial(9,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/skin.material"));
			mesh->SetMaterial(10, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/metal_decals.material"));
			mesh->SetMaterial(11, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/clothing.material"));
			mesh->SetMaterial(12, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/boots.material"));
			mesh->SetMaterial(13, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/monado.material"));
			mesh->SetMaterial(14, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/skin.material"));
		}

		std::shared_ptr<Components::MeshRenderer> meshRenderer = playerEntity->AddComponent<Components::MeshRenderer>(mesh);
		std::shared_ptr<Game::PlayerController> playerController = playerEntity->AddComponent<Game::PlayerController>();
		
		playerEntity->Transform()->Position() = glm::vec3(0, 0, -6);
		playerEntity->Transform()->Scale() = glm::vec3(0.1f, 0.1f, 0.1f);
	}

	return playerEntity;
}

std::shared_ptr<Entity> CreateMapEntity(std::shared_ptr<Core> core)
{
	std::shared_ptr<Entity> mapEntity = core->AddEntity("Level Geometry");
	{
		std::shared_ptr<ResourceManagement::Model> mesh = core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/gaur_plains.fbx");
		{
			mesh->SetMaterial(0,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/waves.material"));
			mesh->SetMaterial(1,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_1.material"));
			mesh->SetMaterial(2,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_2.material"));
			mesh->SetMaterial(3,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/ore.material"));
			mesh->SetMaterial(4,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
			mesh->SetMaterial(5,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/foliage.material"));
			mesh->SetMaterial(6,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/tree_1.material"));
			mesh->SetMaterial(8,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_1.material"));
			mesh->SetMaterial(9,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_4.material"));
			mesh->SetMaterial(7,  core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_2.material"));
			mesh->SetMaterial(10, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_6.material"));
			mesh->SetMaterial(11, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_3.material"));
				mesh->SetMaterial(12, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/colours/red.material"));
			mesh->SetMaterial(13, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_4.material"));
			mesh->SetMaterial(14, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(15, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(16, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(17, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_1.material"));
			mesh->SetMaterial(18, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_1.material"));
			mesh->SetMaterial(19, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(20, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/foliage.material"));
			mesh->SetMaterial(21, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
			mesh->SetMaterial(22, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_4.material"));
			mesh->SetMaterial(23, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/bridge_wood.material"));
			mesh->SetMaterial(24, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/tree_2.material"));
			mesh->SetMaterial(25, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_3.material"));
			mesh->SetMaterial(26, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_3.material"));
			mesh->SetMaterial(27, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
			mesh->SetMaterial(28, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_5.material"));
			mesh->SetMaterial(29, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
			mesh->SetMaterial(30, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(31, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(32, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(33, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(34, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_3.material"));
			mesh->SetMaterial(35, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(36, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(37, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_1.material"));
			mesh->SetMaterial(38, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_4.material"));
			mesh->SetMaterial(39, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/rocky_2.material"));
			mesh->SetMaterial(40, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/bridge_metal.material"));
			mesh->SetMaterial(41, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_7.material"));
			mesh->SetMaterial(42, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_6.material"));
			mesh->SetMaterial(43, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/chiseled_stone_8.material"));
			mesh->SetMaterial(44, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
			mesh->SetMaterial(45, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_2.material"));
			mesh->SetMaterial(46, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/vines.material"));
			mesh->SetMaterial(47, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_3.material"));
			mesh->SetMaterial(48, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/waterfall.material"));
			mesh->SetMaterial(49, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/waterfall.material"));
			mesh->SetMaterial(50, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/tree_3.material"));
			mesh->SetMaterial(51, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_2.material"));
			mesh->SetMaterial(52, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/waves.material"));
			mesh->SetMaterial(53, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_2.material"));
			mesh->SetMaterial(54, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/sky.material"));
			mesh->SetMaterial(55, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/water_1.material"));
		}

		std::shared_ptr<Components::MeshRenderer> meshRenderer = mapEntity->AddComponent<Components::MeshRenderer>(mesh);

		mapEntity->Transform()->Position() = glm::vec3(-10, -20, 25);
		mapEntity->Transform()->Rotation() = glm::quat(glm::vec3(0.0f, (M_PI / 2), 0.0f));
		mapEntity->Transform()->Scale() = glm::vec3(0.5f, 0.5f, 0.5f);
	}

	return mapEntity;
}