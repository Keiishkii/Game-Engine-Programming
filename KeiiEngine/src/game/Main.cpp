#include <iostream>
#include <math.h>
#include "glm/stb_image_write.h"
#include <chrono>

#include "engine/KeiiEngine.h"
#include "game/CustomScene.h"

int main()
{
	
	std::shared_ptr<Core> core = Core::Initialise(144, 50);	
	std::shared_ptr<Game::CustomScene> customScene = std::make_shared<Game::CustomScene>();

	core->Start(customScene);
	
	return 0;
}