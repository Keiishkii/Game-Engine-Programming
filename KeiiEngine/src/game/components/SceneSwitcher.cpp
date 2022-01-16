#include "SceneSwitcher.h"

#include "game/scenes/Scene_1.h"
#include "game/scenes/Scene_2.h"
#include "game/scenes/Scene_3.h"

namespace Game
{
	namespace Components
	{		
		void SceneSwitcher::Update()
		{
			std::shared_ptr<Inputs> inputs = Input();

			if (inputs->KeyDown(inputs->k1))
			{
				std::shared_ptr<Game::Scenes::Scene_1> scene_1 = std::make_shared<Game::Scenes::Scene_1>();
				Core()->LoadScene(scene_1);
			}
			else if (inputs->KeyDown(inputs->k2))
			{
				std::shared_ptr<Game::Scenes::Scene_2> scene_2 = std::make_shared<Game::Scenes::Scene_2>();
				Core()->LoadScene(scene_2);
			}
			else if (inputs->KeyDown(inputs->k3))
			{
				std::shared_ptr<Game::Scenes::Scene_3> scene_3 = std::make_shared<Game::Scenes::Scene_3>();
				Core()->LoadScene(scene_3);
			}
		}
	}
}