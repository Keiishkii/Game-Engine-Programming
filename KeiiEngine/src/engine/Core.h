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

	/**	Core acts as the main interface to the engine for games using it. This class contains the main loop of the engine, and has ownership of all sub-systems within the project.  	*/
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
		/** Called to create a Core object. This function sets up all other sub-systems within the engine, then returns a shared pointer to a Core that object can be used to load a scene.
		* @see Initialise(int windowWidth, int windowHeight, int FPS, int fixedFPS)	*/
		static std::shared_ptr<Core> Initialise();
		/** Called to create a Core object, the extra parameters passed in allow for the initial state of the engine to be altered slightly based on the users preference. This function sets up all other sub-systems within the engine, then returns a shared pointer to a Core object that can be used to load a scene.
		* @param windowWidth: the size along the x-axis of the program window.
		* @param windowHeight: the size along the y-axis of the program window.
		* @param FPS: the visual frame rate of the program - Update() syncs to this.
		* @param fixedFPS: the fixed time step of the program - FixedUpdate() syncs to this.
		* @see Initialise()		*/
		static std::shared_ptr<Core> Initialise(int windowWidth, int windowHeight, int FPS, int fixedFPS);
		
		/** The funciton used to load scenes, if a scene is already loaded it will be safely shut down and the new one will replace it.
		@param scene: a pointer to the scene inteded to be loaded.	*/
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

		/** Stops the main loop from starting the next frame, after which the game will be shut down.	*/
		void Stop();

		/** Get Function: 
		@return Returns a shared pointer to the Cores Debugger.			*/
		std::shared_ptr<ErrorHandling::Debugger> Debugger();
		/** Get Function:
		@return Returns a shared pointer to the Cores GraphicsManager.	*/
		std::shared_ptr<Graphics::GraphicsManager> GraphicsManager();
		/** Get Function:
		@return Returns a shared pointer to the Cores AudioManager.		*/
		std::shared_ptr<Audio::AudioManager> AudioManager();
		/** Get Function:
		@return Returns a shared pointer to the Cores ResourceManager.	*/
		std::shared_ptr<ResourceManagement::ResourceManager> ResourceManager();
		/** Get Function:
		@return Returns a shared pointer to the Cores PhysicsManager.	*/
		std::shared_ptr<Physics::PhysicsManager> PhysicsManager();
		/** Get Function:
		@return Returns a shared pointer to the Cores SystemIndexer.		*/
		std::shared_ptr<SystemIndexer> SystemIndexer();
		/** Get Function:
		@return Returns a shared pointer to the Cores TimeManager.		*/
		std::shared_ptr<TimeManager> TimeManager();
		/** Get Function:
		@return Returns a shared pointer to the Cores InputManager.		*/
		std::shared_ptr<InputManager> InputManager();
		/** Get Function: 
		@return Returns a shared pointer to the Cores active Scene.		*/
		std::shared_ptr<Scene> ActiveScene();
	};
}