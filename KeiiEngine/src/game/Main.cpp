#include <iostream>
#include <math.h>

#include "engine/KeiiEngine.h"
#include "game/components/PlayerController.h"

#define _USE_MATH_DEFINES

int main()
{
	std::cout << "\033[0m" << " - [ENGINE START] - " << std::endl;

	std::shared_ptr<Core> core = Core::Initialise();

	std::shared_ptr<Entity> cameraEntity = core->AddEntity();
	{
		std::shared_ptr<Components::Camera> camera = cameraEntity->AddComponent<Components::Camera>(); 
		cameraEntity->Transform().lock()->position = glm::vec3(0, 2, 0);
		cameraEntity->Transform().lock()->rotation = glm::quat(glm::vec3(-0.25f, 0.0f, 0.0f));
	}

	//std::shared_ptr<Entity> mapEntity = core->AddEntity();
	{
		//std::shared_ptr<Components::MeshRenderer> meshRenderer = mapEntity->AddComponent<Components::MeshRenderer>(core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/gaur_plains.fbx"));
		//mapEntity->Transform().lock()->position = glm::vec3(-10, -20, 25);
		//mapEntity->Transform().lock()->rotation = glm::quat(glm::vec3(0.0f, (M_PI / 2), 0.0f));
		//mapEntity->Transform().lock()->scale = glm::vec3(0.1f, 0.1f, 0.1f);
	}


	std::shared_ptr<Entity> cubeEntity = core->AddEntity();
	{
		std::shared_ptr<Components::MeshRenderer> meshRenderer = cubeEntity->AddComponent<Components::MeshRenderer>(core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/cube.fbx"));
		cubeEntity->Transform().lock()->position = glm::vec3(0, 1, -3);
		cubeEntity->Transform().lock()->scale = glm::vec3(0.1f, 0.1f, 0.1f);
	}

	std::shared_ptr<Entity> playerEntity = core->AddEntity();
	{
		std::shared_ptr<ResourceManagement::Model> mesh = core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/shulk.fbx");
		//for (int i = 0; i < 16; i++)
			//mesh->SetMaterial(i, core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk_clothing.material"));

		std::shared_ptr<Components::MeshRenderer> meshRenderer = playerEntity->AddComponent<Components::MeshRenderer>(mesh);
		std::shared_ptr<Game::PlayerController> playerController = playerEntity->AddComponent<Game::PlayerController>();
			playerEntity->Transform().lock()->position = glm::vec3(0, 0, -6);
			playerEntity->Transform().lock()->scale = glm::vec3(0.1f, 0.1f, 0.1f);
	}

	core->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/default_material.material");
	
	core->Start(144, 50);

	return 0;
}