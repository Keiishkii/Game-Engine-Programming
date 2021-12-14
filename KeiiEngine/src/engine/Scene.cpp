#include "Scene.h"

#include "Core.h"
#include "Entity.h"
#include "graphics/GraphicsManager.h"
#include "resources/ResourceManager.h"
#include "resources/SkyboxMaterial.h"
#include "resources/Texture.h"

namespace Engine
{
	void Scene::Initialise(std::shared_ptr<Engine::Core> core)
	{
		_core = core;
	}

	void Scene::LoadScene() 
	{ 
	}

	void Scene::Update()
	{
		for (int i = 0; i < _entityList.size(); i++)
		{
			_entityList[i]->Update();
		}
	}

	void Scene::PhysicsUpdate()
	{
		for (int i = 0; i < _entityList.size(); i++)
		{
			_entityList[i]->PhysicsUpdate();
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
		for (int j = 0; j < _entityList.size(); j++)
		{
			_entityList[j]->Render(transformationMatrix, projectionMatrix);
		}

		Core()->GraphicsManager()->RenderSkybox(Skybox(), transformationMatrix, projectionMatrix);
	}




	std::shared_ptr<Entity> Scene::AddEntity(std::string name)
	{
		std::shared_ptr<Entity> entity = std::make_shared<Entity>(name);

		entity->Initialise(entity, Core());;
		_entityList.push_back(entity);

		return entity;
	}

	std::shared_ptr<Entity> Scene::FindEntity(std::string name)
	{
		std::shared_ptr<Entity> foundObject;
		for (int i = 0; i < _entityList.size(); i++)
		{
			if (_entityList[i]->Name().find(name) != std::string::npos)
			{
				foundObject = _entityList[i];
				break;
			}
		}

		return foundObject;
	}

	std::shared_ptr<Components::Camera> Scene::MainCamera()
	{
		std::shared_ptr<Components::Camera> mainCamera = NULL;
		
		if (_cameraList.size() > 0)
			mainCamera = _cameraList[0].lock();

		return mainCamera;
	}

	std::vector<std::weak_ptr<Components::Light>> Scene::Lights() { return _lightList; }
	std::shared_ptr<Engine::Core> Scene::Core() { return _core.lock(); }
	std::shared_ptr<ResourceManagement::SkyboxMaterial>& Scene::Skybox() { return _skyboxMaterial; }
}