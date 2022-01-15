#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace Engine
{
	struct Maths
	{
	private:
	public:

	private:
	public:
		static void ConvertVector_RightToLeftHandedCoordinateSystem(glm::vec3& position);
		static void ConvertQuaterion_RightToLeftHandedCoordinateSystem(glm::quat& quaternion);
	};
}