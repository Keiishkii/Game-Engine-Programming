#include <iostream>

#include "Transform.h"
#include "engine/entity.h"

namespace Engine
{
	namespace Components
	{
		Transform::Transform()
		{
			_position = glm::vec3{ 0, 0, 0 };
			_rotation = glm::quat{ 1, 0, 0, 0 };
			_scale = glm::vec3{ 1, 1, 1 };
		}

		glm::mat4x4 Transform::TransformationMatrix()
		{
			glm::mat4x4 scaleMatrix = glm::scale(glm::identity<glm::mat4x4>(), _scale);
			glm::mat4x4 rotationMatrix = glm::mat4_cast(_rotation);
			glm::mat4x4 translationMatrix = glm::translate(glm::identity<glm::mat4x4>(), _position);

			return translationMatrix * rotationMatrix * scaleMatrix;
		}

		glm::vec3& Transform::Position() { return _position; }
		glm::quat& Transform::Rotation() { return _rotation; }
		glm::vec3& Transform::Scale() { return _scale;  }
	}
}