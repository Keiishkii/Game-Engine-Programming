#include <iostream>
#include <math.h>

#include "engine/KeiiEngine.h"
#include "game/components/PlayerController.h"

#define _USE_MATH_DEFINES

void CreateCameraEntity(std::shared_ptr<Core> core);
void CreatePlayerEntity(std::shared_ptr<Core> core);
void CreateMapEntity(std::shared_ptr<Core> core);

int main()
{
	std::cout << "\033[0m" << " - [ENGINE START] - " << std::endl;

	std::shared_ptr<Core> core = Core::Initialise();

	CreateCameraEntity(core);
	CreatePlayerEntity(core);
	CreateMapEntity(core);
	
	core->Start(144, 50);

	return 0;
}

void CreateCameraEntity(std::shared_ptr<Core> core)
{
	std::shared_ptr<Entity> cameraEntity = core->AddEntity();
	{
		std::shared_ptr<Components::Camera> camera = cameraEntity->AddComponent<Components::Camera>();

		cameraEntity->Transform().lock()->position = glm::vec3(0, 2, 0);
		cameraEntity->Transform().lock()->rotation = glm::quat(glm::vec3(-0.25f, 0.0f, 0.0f));
	}
}

void CreatePlayerEntity(std::shared_ptr<Core> core)
{
	std::shared_ptr<Entity> playerEntity = core->AddEntity();
	{
		std::shared_ptr<ResourceManagement::Model> mesh = core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/shulk.fbx");
		{
			mesh->SetMaterial(0, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/eye.material"));
			mesh->SetMaterial(4, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/eye.material"));
			mesh->SetMaterial(8, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/hair.material"));
			mesh->SetMaterial(9, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/skin.material"));
			mesh->SetMaterial(10, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/metal_decals.material"));
			mesh->SetMaterial(11, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/clothing.material"));
			mesh->SetMaterial(12, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/boots.material"));
			mesh->SetMaterial(13, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/monado.material"));
			mesh->SetMaterial(14, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/skin.material"));
		}

		std::shared_ptr<Components::MeshRenderer> meshRenderer = playerEntity->AddComponent<Components::MeshRenderer>(mesh);
		std::shared_ptr<Game::PlayerController> playerController = playerEntity->AddComponent<Game::PlayerController>();
		
		playerEntity->Transform().lock()->position = glm::vec3(0, 0, -6);
		playerEntity->Transform().lock()->scale = glm::vec3(0.1f, 0.1f, 0.1f);
	}
}

void CreateMapEntity(std::shared_ptr<Core> core)
{
	std::shared_ptr<Entity> mapEntity = core->AddEntity();
	{
		std::shared_ptr<ResourceManagement::Model> mesh = core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/gaur_plains.fbx");
		{
			mesh->SetMaterial(0, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/colours/red.material"));
			//mesh->SetMaterial(0, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/gaur_plains/grass.material"));
		}

		std::shared_ptr<Components::MeshRenderer> meshRenderer = mapEntity->AddComponent<Components::MeshRenderer>(mesh);

		mapEntity->Transform().lock()->position = glm::vec3(-10, -20, 25);
		mapEntity->Transform().lock()->rotation = glm::quat(glm::vec3(0.0f, (M_PI / 2), 0.0f));
		mapEntity->Transform().lock()->scale = glm::vec3(0.1f, 0.1f, 0.1f);
	}
}