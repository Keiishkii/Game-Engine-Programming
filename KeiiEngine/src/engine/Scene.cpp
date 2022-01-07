#include "Scene.h"

#include <string>

#include "Core.h"
#include "Entity.h"
#include "error-handling/Debugger.h"
#include "graphics/GraphicsManager.h"
#include "resources/ResourceManager.h"
#include "resources/SkyboxMaterial.h"
#include "resources/Texture.h"


using Engine::ErrorHandling::Debugger;

namespace Engine
{
	void Scene::Initialise(std::shared_ptr<Engine::Core> core)
	{
		_core = core;
	}

	Scene::~Scene()
	{
		_entitys.clear();
		_entityList.clear();
	}

	void Scene::LoadScene() { }

	void Scene::Update()
	{
		if (_audioListeners.size() != 1)
		{
			Debugger::PrintWarning((_audioListeners.size() > 1) ?
				("There is more then one 'AudioListener' in the scene, remove " + std::to_string(_audioListeners.size() - 1) + " from the scene.") :
				("There is no 'AudioListner' in the scene."));
		}

		for (int i = 0; i < Entitys().size(); i++)
		{
			Entitys()[i]->Update();
		}
	}

	void Scene::PhysicsUpdate()
	{
		for (int i = 0; i < Entitys().size(); i++)
		{
			Entitys()[i]->PhysicsUpdate();
		}
	}

	std::shared_ptr<ResourceManagement::Texture> Scene::RenderSceneToTexture(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix, int width, int height)
	{
		glViewport(0, 0, width, height);
		std::shared_ptr<ResourceManagement::Texture> texture = Core()->ResourceManager()->Create<ResourceManagement::Texture>();

		GLuint framebufferID = 0, framebufferColourTextureID = 0, frameBufferDepthTextureID = 0;
		Core()->GraphicsManager()->CreateRenderBuffer(framebufferID, framebufferColourTextureID, frameBufferDepthTextureID, width, height);

		// - - Renders scene to current buffer.
		RenderScene(transformationMatrix, projectionMatrix);


		int dataLength = width * height * 4;
		GLubyte* textureData = new GLubyte[dataLength];

		glBindTexture(GL_TEXTURE_2D, framebufferColourTextureID);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

		texture->CreateTexture(width, height, 4, textureData);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glDeleteTextures(1, &framebufferColourTextureID);
		glDeleteRenderbuffers(1, &frameBufferDepthTextureID);
		glDeleteFramebuffers(1, &framebufferID);

		return texture;
	}

	GLuint Scene::RenderSceneToTextureBuffer(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix, int width, int height)
	{
		glViewport(0, 0, width, height);

		GLuint framebufferID = 0, framebufferColourTextureID = 0, frameBufferDepthTextureID = 0;
		Core()->GraphicsManager()->CreateRenderBuffer(framebufferID, framebufferColourTextureID, frameBufferDepthTextureID, width, height);


		// - - Renders scene to current buffer.
		RenderScene(transformationMatrix, projectionMatrix);


		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glDeleteRenderbuffers(1, &frameBufferDepthTextureID);
		glDeleteFramebuffers(1, &framebufferID);

		return framebufferColourTextureID;
	}

	void Scene::RenderScene(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix)
	{
		int channelNumber = 4;
		for (int j = 0; j < Entitys().size(); j++)
		{
			Entitys()[j]->Render(transformationMatrix, projectionMatrix);
		}

		Core()->GraphicsManager()->RenderSkybox(Skybox(), transformationMatrix, projectionMatrix);
	}




	std::shared_ptr<Entity> Scene::AddEntity(std::string name)
	{
		std::shared_ptr<Entity> entity = std::make_shared<Entity>(name);

		entity->Initialise(entity, Core());;

		_entitys[entity->_systemIndex] = entity;
		_entityListDirty = true;

		return entity;
	}

	void Scene::RemoveEntity(std::shared_ptr<Entity> entity)
	{
		_entitys.erase(_entitys.find(entity->_systemIndex));
		_entityListDirty = true;
	}

	std::shared_ptr<Entity> Scene::FindEntity(std::string name)
	{
		std::shared_ptr<Entity> foundObject;
		for (int i = 0; i < Entitys().size(); i++)
		{
			if (Entitys()[i]->Name().find(name) != std::string::npos)
			{
				foundObject = Entitys()[i];
				break;
			}
		}

		return foundObject;
	}

	std::vector<std::shared_ptr<Entity>> Scene::Entitys()
	{
		if (_entityListDirty)
		{
			_entityList.clear();
			for (const std::pair<unsigned int, std::shared_ptr<Entity>>& entity : _entitys)
			{
				_entityList.push_back(entity.second);
			}

			_entityListDirty = false;
		}

		return _entityList;
	}



	std::shared_ptr<Components::Camera> Scene::MainCamera()
	{
		std::shared_ptr<Components::Camera> mainCamera = _mainCamera.lock();
		if (!mainCamera)
		{
			std::vector<std::weak_ptr<Components::Camera>> cameras = Cameras();
			
			if (cameras.size() > 0)
			{
				_mainCamera = cameras[0];
				mainCamera = _mainCamera.lock();
			}
			else
			{
				Debugger::PrintWarning("There is no 'Camera' component in the scene.");
			}
		}

		return mainCamera;
	}

	std::vector<std::weak_ptr<Components::Camera>> Scene::Cameras()
	{
		std::vector<std::weak_ptr<Components::Camera>> cameras;
		for (const std::pair<unsigned int, std::weak_ptr<Components::Camera>>& camera : _cameras)
		{
			cameras.push_back(camera.second);
		}

		return cameras;
	}

	std::vector<std::weak_ptr<Components::Light>> Scene::Lights() 
	{
		std::vector<std::weak_ptr<Components::Light>> lights;
		for (const std::pair<unsigned int, std::weak_ptr<Components::Light>>& light : _lights)
		{
			lights.push_back(light.second);
		}

		return lights;
	}


	std::shared_ptr<Engine::Core> Scene::Core() { return _core.lock(); }
	std::shared_ptr<ResourceManagement::SkyboxMaterial>& Scene::Skybox() { return _skyboxMaterial; }
}