#include <memory>
#include <vector>
#include <SDL.h>

namespace Engine
{
	namespace ResourceManagement { struct ResourceManager; }
	namespace ErrorHandling { struct Debugger; }

	struct Entity;
	namespace Components { struct Camera; }

	struct Core
	{
	private:
		std::weak_ptr<Core> _self;

		std::shared_ptr<ResourceManagement::ResourceManager> _resources;
		std::shared_ptr<ErrorHandling::Debugger> _debugger;
		std::shared_ptr<SDL_Window*> _window;

		std::vector<std::shared_ptr<Entity>> _entityList;

		std::vector<std::weak_ptr<Components::Camera>> _cameraList;
		std::weak_ptr<Components::Camera> _activeCamera;

		bool _running;


	private:
		void MainLoop();
		void SDLInitialisation();

		void Render();
		void Update();
		void PhysicsUpdate();

	public:
		~Core();
		static std::shared_ptr<Core> Initialise();

		std::shared_ptr<ResourceManagement::ResourceManager> ResourceManager();
		std::shared_ptr<ErrorHandling::Debugger> Debugger();

		void Start();
		void Stop();

		std::shared_ptr<Entity> AddEntity();
	};
}