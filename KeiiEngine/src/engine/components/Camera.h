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
	namespace Graphics { struct GraphicsManager; }
	namespace Components
	{
		/**	The Camera is a child of Component, it is used to render the scene.  	*/
		struct Camera : Component
		{
			friend Engine::Core;
			friend Engine::Graphics::GraphicsManager;

		private:
			glm::mat4x4 _projectionMatrix;
		public:


		private:
			void GenerateNewProjectionMatrix(float windowWidth, float windowHeight, float fieldOfView);
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			~Camera();

			glm::mat4x4& ProjectionMatrix();
		};
	}
}