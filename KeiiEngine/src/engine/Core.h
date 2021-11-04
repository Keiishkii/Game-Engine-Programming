#pragma once
#ifndef CORE
#define CORE
	#include <memory>
	#include <vector>
	#include <SDL.h>

	#include "error-handling/Debugger.h"
	#include "resources/Resources.h"

	namespace Engine
	{
		struct Camera;
		struct Entity;

		struct Core
		{
		private:
			std::weak_ptr<Core> _self;

			std::shared_ptr<Engine::ErrorHandling::Debugger> _debugger;
			std::shared_ptr<SDL_Window*> _window;

			std::vector<std::shared_ptr<Entity>> _entityList;

			std::vector<std::weak_ptr<Camera>> _cameraList;
			std::weak_ptr<Camera> _activeCamera;

			int targetUpdatesPerSecond;
			bool running;
			
		public:
			std::shared_ptr<Engine::ResourceManagement::Resources> resources;

		private:
			void MainLoop();
			void SDLInitialisation();

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