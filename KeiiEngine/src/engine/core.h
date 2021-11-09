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

		std::shared_ptr<ResourceManagement::Resources> _resources;
		std::shared_ptr<ErrorHandling::Debugger> _debugger;
		std::shared_ptr<SDL_Window*> _window;

		std::vector<std::shared_ptr<Entity>> _entityList;

		std::vector<std::weak_ptr<Camera>> _cameraList;
		std::weak_ptr<Camera> _activeCamera;

		int targetUpdatesPerSecond;
		bool running;


	private:
		void MainLoop();
		void SDLInitialisation();

		void Render();
		void Update();
		void PhysicsUpdate();

	public:
		~Core();
		static std::shared_ptr<Core> Initialise();

		std::shared_ptr<ResourceManagement::Resources> ResourceManager();
		std::shared_ptr<ErrorHandling::Debugger> Debugger();

		void Start();
		void Stop();

		std::shared_ptr<Entity> AddEntity();
	};
}

#endif