#include <glm/vec3.hpp>

#include "Component.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct Texture;
		struct ShaderProgram;
	}

	namespace Graphics
	{
		struct VertexArray;
		struct VertexBuffer;
	}

	struct Core;
	namespace Components
	{
		struct Gizmo : Component
		{
		private:
			glm::vec3 _colour;

			std::shared_ptr<ResourceManagement::Texture> _gizmoTexture;
			std::shared_ptr<ResourceManagement::ShaderProgram> _gizmoShaderProgram;
			std::shared_ptr<Graphics::VertexArray> _gizmoVertexArrayObject;
		public:


		private:
			virtual void Render(const std::shared_ptr<Components::Camera>& activeCamera) override;
		public:
			void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity, std::shared_ptr<ResourceManagement::Texture> gizmoTexture);
		};
	}
}