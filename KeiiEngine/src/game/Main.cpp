#include <iostream>

#include "engine/KeiiEngine.h"
#include "game/components/PlayerController.h"

int main()
{
	std::shared_ptr<Core> core = Core::Initialise();

	std::shared_ptr<Entity> cameraEntity = core->AddEntity();
	{
		std::shared_ptr<Components::Camera> camera = cameraEntity->AddComponent<Components::Camera>();
		cameraEntity->Transform().lock()->position = glm::vec3(0, 1, 0);
	}

	//std::shared_ptr<Entity> mapEntity = core->AddEntity();
	{
		//std::shared_ptr<Components::MeshRenderer> meshRenderer = mapEntity->AddComponent<Components::MeshRenderer>(core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/gaur_plains.fbx"));
		//mapEntity->Transform().lock()->scale = glm::vec3(0.1f, 0.1f, 0.1f);
	}

	std::shared_ptr<Entity> playerEntity = core->AddEntity();
	{
		std::shared_ptr<Components::MeshRenderer> meshRenderer = playerEntity->AddComponent<Components::MeshRenderer>(core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/shulk.fbx"));
		std::shared_ptr<Game::PlayerController> playerController = playerEntity->AddComponent<Game::PlayerController>();
		playerEntity->Transform().lock()->position = glm::vec3(0, 0, -6);
		playerEntity->Transform().lock()->scale = glm::vec3(0.1f, 0.1f, 0.1f);
	}



	core->Start(144, 50);

	return 0;
}