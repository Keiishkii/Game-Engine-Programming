#include <iostream>
#include <math.h>
#include "glm/stb_image_write.h"

#include "engine/KeiiEngine.h"
#include "game/CustomScene.h"

int main()
{
	std::cout << "\033[0m" << " - [ENGINE START] - " << std::endl;

	std::shared_ptr<Core> core = Core::Initialise(144, 50);
	
	std::shared_ptr<Game::CustomScene> customScene = std::make_shared<Game::CustomScene>();

	core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/skybox.fbx");


	core->Start(customScene);

	return 0;
}