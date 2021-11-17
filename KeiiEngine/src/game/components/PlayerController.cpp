#include "PlayerController.h"

#include <iostream>
#include <math.h>

namespace Game
{
	void PlayerController::Start()
	{
		_initialSpawnPosition = Transform().lock()->position;
	}

	void PlayerController::Update()
	{
		Transform().lock()->position = glm::vec3(std::sin(corePtr.lock()->TimeManager()->TimeSinceStartOfProgram()) * 2, 0, 0) + _initialSpawnPosition;
		Transform().lock()->rotation = glm::quat(glm::vec3(0, corePtr.lock()->TimeManager()->TimeSinceStartOfProgram(), 0));
	}	
}