#include "glew.h"

namespace Engine
{
	struct Core;
	namespace ResourceManagement 
	{ 
		struct SkyboxMaterial; 
		struct ShaderProgram;
	}

	namespace Graphics
	{
		struct VertexArray;
		struct GraphicsManager
		{
			friend Core;
			friend Scene;

		private:
			std::shared_ptr<SDL_Window*> _window;

			std::weak_ptr<Engine::Core> _core;

			std::shared_ptr<ResourceManagement::ShaderProgram> _postProcessingShader;
			std::shared_ptr<Graphics::VertexArray> _quad;
			std::shared_ptr<Graphics::VertexArray> _skybox;
		public:
		
		
		private:
			void Initialise(std::shared_ptr<Engine::Core> core);
			void SDLInitialisation();

			void RenderFrame(std::shared_ptr<Scene> activeScene);
			void RenderSkybox(std::shared_ptr<ResourceManagement::SkyboxMaterial> skybox, const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix);
		public:
			~GraphicsManager();
			void CreateRenderBuffer(GLuint& framebufferID, GLuint& framebufferColourTextureID, GLuint& frameBufferDepthTextureID, int width, int height);
			std::shared_ptr<Graphics::VertexArray> Quad();
			std::shared_ptr<Graphics::VertexArray> Skybox();
			std::shared_ptr<ResourceManagement::ShaderProgram> GetPostProcessingShader();
			void SetPostProcessingShader(std::shared_ptr<ResourceManagement::ShaderProgram> postProcessingShader);
			std::shared_ptr<Engine::Core> Core();
		};
	}
}