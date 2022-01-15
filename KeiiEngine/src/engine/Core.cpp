#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <glew.h>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Core.h"
#include "SystemIndexer.h"
#include "time/TimeManager.h"
#include "input/InputManager.h"
#include "input/Inputs.h"
#include "Entity.h"
#include "Scene.h"
#include "components/Camera.h"
#include "components/Transform.h"
#include "error-handling/Debugger.h"
#include "error-handling/Exception.h"
#include "audio/AudioManager.h"
#include "graphics/GraphicsManager.h"
#include "graphics/PolygonMaterialGroup.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "physics/PhysicsManager.h"
#include "resources/ResourceManager.h"
#include "resources/ShaderProgram.h"
#include "resources/Model.h"
#include "resources/Texture.h"

using namespace Engine::ErrorHandling;
using namespace Engine::ResourceManagement;

namespace Engine
{
	std::shared_ptr<Core> Core::Initialise()
	{
		return Initialise(600, 400, 60, 50);
	}

	std::shared_ptr<Core> Core::Initialise(int windowWidth, int windowHeight, int FPS, int fixedFPS)
	{
		std::shared_ptr<Core> core = std::make_shared<Core>();
		core->_self = core;

		try
		{		// System Indexer
			core->_systemIndexer = std::make_shared<Engine::SystemIndexer>();

			// Time Manager
			core->_timeManager = std::make_shared<Engine::TimeManager>(FPS, fixedFPS);

				// Error Handling
			core->_debugger = std::make_shared<ErrorHandling::Debugger>();

			// Resource Manager
			core->_physicsManager = std::make_shared<Physics::PhysicsManager>();
			core->_physicsManager->Initialise(core, core->_timeManager);

				// Resource Manager
			core->_resourceManager = std::make_shared<ResourceManagement::ResourceManager>();
			core->_resourceManager->Initialise(core->_resourceManager, core);

				// Graphics Manager
			core->_graphicsManager = std::make_shared<Graphics::GraphicsManager>();
			core->_graphicsManager->Initialise(core, windowWidth, windowHeight);

				// Audio Manager
			core->_audioManager = std::make_shared<Audio::AudioManager>(core);

				// Input Manager
			core->_inputManager = std::make_shared<Engine::InputManager>();


			core->_completedCoreInitialisation = true;
		}
		catch (Exception e)
		{
			e.Print();
		}

		return core;
	}



	void Core::MainLoop()
	{
		_running = true;
		while (_running) [[likely]]
		{
			_inputManager->ProcessFrameInput();
					
			Update();
			
			int physicsCycles = _timeManager->CheckForFixedUpdates();
			for (int i = 0; i < physicsCycles; i++)
			{
				PhysicsUpdate();
			}

			GraphicsManager()->RenderFrame(ActiveScene());
			
			ActiveScene()->CleanEntityList();

			_timeManager->WaitForEndOfFrame();

			if (_inputManager->Input()->QuitEvent()) [[unlikely]] 
				_running = false;
		}

		PreDestructor();
	}



	void Core::Stop()
	{
		_running = !_running;
	}

	void Core::PreDestructor()
	{
		_activeScene->PreDestructor();
		_activeScene.reset();

		_resourceManager.reset();

		_graphicsManager.reset();

		_audioManager.reset();

		_timeManager.reset();

		_inputManager.reset();

		_systemIndexer.reset();

		_debugger.reset();
	}



	void Core::Update()
	{
		_activeScene->Update();

		_debugger->LogUpdate();
	}

	void Core::PhysicsUpdate()
	{
		_activeScene->PhysicsUpdate();
		_debugger->LogFixedUpdate();
	}

	std::shared_ptr<Core> Core::Self() { return _self.lock(); }
	std::shared_ptr<Scene> Core::ActiveScene() { return _activeScene; }

	std::shared_ptr<Debugger> Core::Debugger() { return _debugger; }

	std::shared_ptr<Graphics::GraphicsManager> Core::GraphicsManager() { return _graphicsManager; }
	std::shared_ptr<Audio::AudioManager> Core::AudioManager() { return _audioManager; }
	std::shared_ptr<ResourceManager> Core::ResourceManager() { return _resourceManager; }
	std::shared_ptr<Physics::PhysicsManager> Core::PhysicsManager() { return _physicsManager; }
	std::shared_ptr<TimeManager> Core::TimeManager() { return _timeManager; }
	std::shared_ptr<SystemIndexer> Core::SystemIndexer() { return _systemIndexer; }
	std::shared_ptr<InputManager> Core::InputManager() { return _inputManager; }
}