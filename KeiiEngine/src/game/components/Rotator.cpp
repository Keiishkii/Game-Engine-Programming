#include "Rotator.h"

namespace Game
{
	void Rotator::Start()
	{
		_startingRotation = Transform()->Rotation();
	}

	void Rotator::Update()
	{
		if (test-- < 0)
		{
			Scene()->RemoveEntity(Entity());
		}

		Transform()->Rotation() = (glm::quat(_eulerRotationSpeed * Time()->TimeSinceStartOfProgram())) * _startingRotation;
	}

	glm::vec3& Rotator::EulerRotation() { return _eulerRotationSpeed; }
}