#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Component.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct Model;
		struct SkyboxMaterial;
	}

	struct Core;
	namespace Components
	{
		struct Camera : Component
		{
			friend Engine::Core;

		private:
			glm::mat4x4 _projectionMatrix;

			std::shared_ptr<ResourceManagement::Model> _skyboxCube;
		public:


		private:
			void GenerateNewProjectionMatrix(float windowWidth, float windowHeight, float fieldOfView);
			void RenderSkybox();
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			
			glm::mat4x4& ProjectionMatrix();
		};
	}
}