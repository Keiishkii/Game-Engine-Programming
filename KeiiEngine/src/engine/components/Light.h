#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Component.h"

namespace Engine
{
	struct Core;
	namespace Components
	{
		/**	The Light is a child of Component, when placed on an entity in the scene it can be passed into the shader and used to calculate scene lighting.  	*/
		struct Light : Component
		{
			friend Engine::Core;

		private:
			float _intensity;
			glm::vec3 _colour;
		public:


		private:
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			~Light();

			glm::vec3& Colour();
			float& Intensity();
		};
	}
}