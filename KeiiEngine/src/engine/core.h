#pragma once
#ifndef CORE
#define CORE
	#include <memory>
	#include <vector>

	#include <SDL.h>


	namespace Engine
	{
		struct Debugger;
		struct Camera;
		struct Entity;

		struct Core
		{
		private:
			std::weak_ptr<Core> _self;

			std::shared_ptr<Debugger> _debugger;
			std::shared_ptr<SDL_Window*> _window;
			std::vector<std::shared_ptr<Entity>> _entityList;

			std::vector<std::weak_ptr<Camera>> _cameraList;
			std::weak_ptr<Camera> _activeCamera;

			int targetUpdatesPerSecond;
			bool running;

		private:
			void MainLoop();

			void Render();
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
#endif