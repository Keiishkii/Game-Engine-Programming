#include "engine/KeiiEngine.h"

#include "game/scenes/Scene_2.h"

int main()
{
	std::shared_ptr<Core> core = Core::Initialise(1600, 800, 60, 50);	
	std::shared_ptr<Game::Scenes::Scene_2> scene = std::make_shared<Game::Scenes::Scene_2>();

	core->LoadScene(scene);

	return 0;
}