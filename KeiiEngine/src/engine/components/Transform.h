#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Component.h"

namespace Engine
{
	namespace Components
	{
		struct Transform : Component
		{
		private:
			glm::vec3 _position;
			glm::quat _rotation;
			glm::vec3 _scale;
		public:


		private:
		public:
			Transform();

			void PrintPosition();

			glm::mat4x4 TransformationMatrix();
			glm::vec3& Position();
			glm::quat& Rotation();
			glm::vec3& Scale();
		};
	}
}