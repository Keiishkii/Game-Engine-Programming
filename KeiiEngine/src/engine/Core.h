#include <memory>
#include <vector>
#include <string>
#include <SDL.h>

namespace Engine
{
	namespace ResourceManagement { struct ResourceManager; }
	namespace ErrorHandling { struct Debugger; }

	struct Entity;
	namespace Components { struct Camera; }

	struct TimeManager;
	struct InputManager;
	struct Core
	{
		friend Components::Camera;

	private:
		std::weak_ptr<Core> _self;

		std::shared_ptr<TimeManager> _timeManager;
		std::shared_ptr<InputManager> _inputManager;
		std::shared_ptr<ResourceManagement::ResourceManager> _resources;
		std::shared_ptr<ErrorHandling::Debugger> _debugger;
		std::shared_ptr<SDL_Window*> _window;

		std::vector<std::shared_ptr<Entity>> _entityList;

		std::vector<std::weak_ptr<Components::Camera>> _cameraList;

		bool _running;
	public:


	private:
		void MainLoop();
		void SDLInitialisation();

		void Render();
		void Update();
		void PhysicsUpdate();

		std::shared_ptr<Core> Self();
	public:
		~Core();
		static std::shared_ptr<Core> Initialise(int FPS, int fixedFPS);

		std::shared_ptr<ErrorHandling::Debugger> Debugger();
		std::shared_ptr<ResourceManagement::ResourceManager> ResourceManager();
		std::shared_ptr<TimeManager> TimeManager();
		std::shared_ptr<InputManager> InputManager();

		void Start();
		void Stop();

		std::shared_ptr<Entity> AddEntity(std::string name);

		std::shared_ptr<Entity> Find(std::string name);
	};
}