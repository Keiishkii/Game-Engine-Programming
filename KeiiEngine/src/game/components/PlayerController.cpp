#include "PlayerController.h"

#include <iostream>

#include <math.h>

namespace Game
{ 
	void PlayerController::Start()
	{
		_cameraTransform = Scene()->FindEntity("Camera")->Transform();
	}

	void PlayerController::Update()
	{
		glm::vec3 cameraPosition = _cameraTransform->Position(), position = Transform()->Position();
		glm::quat flattenedLookVector = glm::quatLookAt(glm::normalize(glm::vec3((cameraPosition.x - position.x), 0, ((cameraPosition.z - position.z)))), glm::vec3(0, 1, 0));
		if (!(flattenedLookVector[0] != flattenedLookVector[0]))
		{
			glm::vec3 translation = { 0, 0, 0 };

			if (Input()->KeyHeld(Input()->ESCAPE))
				Core()->Stop();

			if (Input()->KeyHeld(Input()->LSHIFT))
				translation += glm::vec3(0, -1, 0);

			if (Input()->KeyHeld(Input()->SPACE))
				translation += glm::vec3(0, 1, 0);

			if (Input()->KeyHeld(Input()->W))
				translation += glm::vec3(0, 0, 1);

			if (Input()->KeyHeld(Input()->A))
				translation += glm::vec3(1, 0, 0);

			if (Input()->KeyHeld(Input()->S))
				translation += glm::vec3(0, 0, -1);

			if (Input()->KeyHeld(Input()->D))
				translation += glm::vec3(-1, 0, 0);

			translation = flattenedLookVector * (translation * _movementSpeed);


			translation *= Time()->DeltaTime();
			Transform()->Position() += translation;
		}

		//Transform()->PrintPosition();
	}	
}