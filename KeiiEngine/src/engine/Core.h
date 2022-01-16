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

	namespace Physics
	{
		struct PhysicsManager;
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
	struct SystemIndexer;
	struct Core
	{
		friend Scene;

	private:
		std::weak_ptr<Core> _self;
		std::shared_ptr<SystemIndexer> _systemIndexer;

		std::shared_ptr<Scene> _activeScene;

		std::shared_ptr<TimeManager> _timeManager;
		std::shared_ptr<InputManager> _inputManager;
		std::shared_ptr<ResourceManagement::ResourceManager> _resourceManager;
		std::shared_ptr<Physics::PhysicsManager> _physicsManager;
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

		void PreDestructor();
	public:
		static std::shared_ptr<Core> Initialise();
		static std::shared_ptr<Core> Initialise(int windowWidth, int windowHeight, int FPS, int fixedFPS);

		template <typename T>
		void LoadScene(std::shared_ptr<T> scene)
		{
			if (_completedCoreInitialisation)
			{
				if (_activeScene)
				{
					if (_activeScene != scene)
					{
						#ifdef DEBUG
						{
							Engine::ErrorHandling::Debugger::Print("Unloading Old Scene");
						}
						#endif // DEBUG

						_activeScene->Scene::PreDestructor();
						_activeScene.reset();

						#ifdef DEBUG
						{
							Engine::ErrorHandling::Debugger::Print("Loading New Scene");
						}
						#endif // DEBUG

						_activeScene = scene;

						scene->Scene::Initialise(Self());
						scene->LoadScene();
					}
				}
				else
				{
					#ifdef DEBUG
					{
						Engine::ErrorHandling::Debugger::Print("Loading Start Scene");
					}
					#endif // DEBUG

					_activeScene = scene;

					scene->Scene::Initialise(Self());
					scene->LoadScene();

					MainLoop();
				}
			}
		}

		void Stop();

		std::shared_ptr<ErrorHandling::Debugger> Debugger();
		std::shared_ptr<Graphics::GraphicsManager> GraphicsManager();
		std::shared_ptr<Audio::AudioManager> AudioManager();
		std::shared_ptr<ResourceManagement::ResourceManager> ResourceManager();
		std::shared_ptr<Physics::PhysicsManager> PhysicsManager();
		std::shared_ptr<SystemIndexer> SystemIndexer();
		std::shared_ptr<TimeManager> TimeManager();
		std::shared_ptr<InputManager> InputManager();
		std::shared_ptr<Scene> ActiveScene();
	};
}