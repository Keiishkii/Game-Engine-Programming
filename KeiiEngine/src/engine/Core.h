#include <memory>
#include <vector>
#include <string>
#include <SDL.h>
#include <glew.h>

namespace Engine
{
	namespace ResourceManagement 
	{ 
		struct ResourceManager; 
		struct ShaderProgram; 
	}
	namespace ErrorHandling { struct Debugger; }
	namespace Graphics
	{
		struct VertexArray;
	}

	struct Entity;
	namespace Components 
	{ 
		struct Camera; 
		struct Light; 
	}

	struct TimeManager;
	struct InputManager;
	struct Core
	{
		friend Components::Camera;
		friend Components::Light;

	private:
		std::weak_ptr<Core> _self;

		std::shared_ptr<TimeManager> _timeManager;
		std::shared_ptr<InputManager> _inputManager;
		std::shared_ptr<ResourceManagement::ResourceManager> _resources;
		std::shared_ptr<ErrorHandling::Debugger> _debugger;
		std::shared_ptr<SDL_Window*> _window;

		std::vector<std::shared_ptr<Entity>> _entityList;

		std::vector<std::weak_ptr<Components::Camera>> _cameraList;
		std::vector<std::weak_ptr<Components::Light>> _lightList;

		std::shared_ptr<ResourceManagement::ShaderProgram> _frameBufferShader;
		std::shared_ptr<Graphics::VertexArray> _frameBufferVertexArrayObject;

		bool _running;
	public:


	private:
		void MainLoop();
		void SDLInitialisation();
		void RenderBufferInitialisation();

		void SetUpFrameBuffer(GLuint& framebufferID, GLuint& framebufferColourTextureID, GLuint& frameBufferDepthTextureID, int width, int height);
		void ClearFrameBufferAndDrawToMainBuffer(GLuint framebufferID, GLuint framebufferColourTextureID, GLuint frameBufferDepthTextureID);

		void Render();
		void Update();
		void PhysicsUpdate();

		std::shared_ptr<Core> Self();
	public:
		~Core();
		static std::shared_ptr<Core> Initialise(int FPS, int fixedFPS);
		
		void Start();
		void Stop();

		std::shared_ptr<ErrorHandling::Debugger> Debugger();
		std::shared_ptr<ResourceManagement::ResourceManager> ResourceManager();
		std::shared_ptr<TimeManager> TimeManager();
		std::shared_ptr<InputManager> InputManager();

		std::vector<std::weak_ptr<Components::Light>> Lights();
		std::shared_ptr<Entity> AddEntity(std::string name);
		std::shared_ptr<Entity> Find(std::string name);
	};
}