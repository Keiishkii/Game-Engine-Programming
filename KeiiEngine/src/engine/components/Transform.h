#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Component.h"

namespace Engine
{
	namespace Components
	{
		/**	The Transform is a child of Component, on creation of an Entity a Transform component will be added. It is used to store the transformation data in world space of an object.  	*/
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