#include "engine/KeiiEngine.h"
#include "game/CustomScene.h"
#include "PhysX-4.1/include/PxPhysicsAPI.h"

int main()
{
	std::shared_ptr<Core> core = Core::Initialise(1600, 800, 60, 50);	
	std::shared_ptr<Game::CustomScene> customScene = std::make_shared<Game::CustomScene>();

	core->Start(customScene);

	return 0;
}