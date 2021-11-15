#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Component.h"

namespace Engine
{
	struct Core;
	namespace Components
	{
		struct Camera : Component
		{
			friend Core;

		private:
			glm::mat4x4 _projectionMatrix;
		public:


		private:
			virtual void Update() override;
			virtual void PhysicsUpdate() override;

			void GenerateNewProjectionMatrix(float windowWidth, float windowHeight);
		public:
			virtual void Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr) override;

			glm::mat4x4 ProjectionMatrix();
		};
	}
}