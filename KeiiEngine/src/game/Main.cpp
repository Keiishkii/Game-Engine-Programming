#include <iostream>

#include "engine/KeiiEngine.h"

int main()
{
	std::shared_ptr<Core> core = Core::Initialise();

	std::shared_ptr<Entity> cameraEntity = core->AddEntity();
	std::shared_ptr<Components::Camera> camera = cameraEntity->AddComponent<Components::Camera>();

	cameraEntity->Transform().lock()->position = glm::vec3(0, 10, 0);


	std::shared_ptr<Entity> playerEntity = core->AddEntity();
	std::shared_ptr<Components::MeshRenderer> meshRenderer = playerEntity->AddComponent<Components::MeshRenderer>(core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/shulk.fbx"));




	core->Start();

	return 0;
}