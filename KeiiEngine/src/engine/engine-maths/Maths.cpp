#include "Maths.h"

namespace Engine
{
	void Maths::ConvertVector_RightToLeftHandedCoordinateSystem(glm::vec3& position)
	{
		position = glm::vec3(position.x, position.z, position.y);
	}

	void Maths::ConvertQuaterion_RightToLeftHandedCoordinateSystem(glm::quat& quaternion)
	{
		quaternion = glm::quat(-quaternion.x, -quaternion.z, -quaternion.y, quaternion.w);
	}



	glm::vec3 Maths::Lerp(glm::vec3 x, glm::vec3 y, float t)
	{
		return x * (1.f - t) + y * t;
	}

	float Maths::Lerp(float x, float y, float t)
	{
		return x * (1.f - t) + y * t;
	}
}