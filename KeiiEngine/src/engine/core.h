#pragma once
#include <memory>
#include <vector>

#include <SDL.h>


namespace Engine
{
	struct Debugger;
	struct Entity;
	struct Core
	{
	private:
		std::weak_ptr<Core> _self;

		std::shared_ptr<Debugger> _debugger;
		std::shared_ptr<SDL_Window*> _window;
		std::vector<std::shared_ptr<Entity>> _entityList;

		int targetUpdatesPerSecond;
		bool running;

	private:
		void MainLoop();

		void Update();
		void PhysicsUpdate();

	public:
		static std::shared_ptr<Core> Initialise();

		~Core();

		void Start();
		void Stop();

		std::shared_ptr<Entity> AddEntity();
	};
}