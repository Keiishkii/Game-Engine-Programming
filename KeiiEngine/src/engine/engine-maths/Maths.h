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

		static float Lerp(float x, float y, float t);
		static glm::vec3 Lerp(glm::vec3 x, glm::vec3 y, float t);
	};
}