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
}