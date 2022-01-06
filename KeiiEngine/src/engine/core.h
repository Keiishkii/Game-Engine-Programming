#include <memory>
#include <vector>
#include <string>
#include <SDL.h>
#include <glew.h>
#include "glm/glm.hpp"

namespace Engine
{
	namespace ResourceManagement 
	{ 
		struct ResourceManager; 
		struct ShaderProgram; 
		struct Texture;
	}

	namespace Audio { struct AudioManager; }
	namespace ErrorHandling { struct Debugger; }
	namespace Graphics
	{
		struct GraphicsManager;
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
	struct Scene;
	struct Core
	{
		friend Scene;

	private:
		std::weak_ptr<Core> _self;

		std::shared_ptr<Scene> _activeScene;

		std::shared_ptr<TimeManager> _timeManager;
		std::shared_ptr<InputManager> _inputManager;
		std::shared_ptr<ResourceManagement::ResourceManager> _resourceManager;
		std::shared_ptr<Graphics::GraphicsManager> _graphicsManager;
		std::shared_ptr<Audio::AudioManager> _audioManager;
		std::shared_ptr<ErrorHandling::Debugger> _debugger;

		bool _completedCoreInitialisation = false;
		bool _running = false;
	public:


	private:
		void MainLoop();

		void Update();
		void PhysicsUpdate();

		std::shared_ptr<Core> Self();
	public:
		static std::shared_ptr<Core> Initialise();
		static std::shared_ptr<Core> Initialise(int windowWidth, int windowHeight, int FPS, int fixedFPS);

		template <typename T>
		void Start(std::shared_ptr<T> defaultScene)
		{
			if (_completedCoreInitialisation)
			{
				_activeScene = defaultScene;

				defaultScene->Scene::Initialise(Self());
				defaultScene->LoadScene();

				MainLoop();
			}
		}

		void Stop();

		std::shared_ptr<ErrorHandling::Debugger> Debugger();
		std::shared_ptr<Graphics::GraphicsManager> GraphicsManager();
		std::shared_ptr<ResourceManagement::ResourceManager> ResourceManager();
		std::shared_ptr<TimeManager> TimeManager();
		std::shared_ptr<InputManager> InputManager();
		std::shared_ptr<Scene> ActiveScene();
	};
}