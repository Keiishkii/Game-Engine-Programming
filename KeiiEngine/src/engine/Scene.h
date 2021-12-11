#include <vector>
#include <memory>
#include <string>
#include "glew.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace Engine
{
	namespace ResourceManagement 
	{ 
		struct SkyboxMaterial; 
		struct Texture;
	}
	namespace Components
	{
		struct Light;
		struct Camera;
		struct ReflectionProbe;
	}

	struct Entity;
	struct Core;
	struct Scene
	{
		friend Core;
		friend Components::Camera;
		friend Components::Light;
		friend Components::ReflectionProbe;

	private:
		std::vector<std::shared_ptr<Entity>> _entityList;

		std::shared_ptr<ResourceManagement::SkyboxMaterial> _skyboxMaterial;

		std::vector<std::weak_ptr<Components::Camera>> _cameraList;
		std::vector<std::weak_ptr<Components::Light>> _lightList;
		std::vector<std::weak_ptr<Components::ReflectionProbe>> _reflectionProbeList;

		std::weak_ptr<Engine::Core> _core;
	public:


	private:
		void Initialise(std::shared_ptr<Engine::Core> core);

		void Update();
		void PhysicsUpdate();

		void RenderScene(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix);
	public:
		virtual void LoadScene();

		std::shared_ptr<Entity> AddEntity(std::string name);
		std::shared_ptr<Entity> FindEntity(std::string name);

		std::shared_ptr<ResourceManagement::Texture> Scene::RenderSceneToTexture(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix, int width, int height);
		GLuint Scene::RenderSceneToTextureBuffer(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix, int width, int height);

		std::vector<std::weak_ptr<Components::Light>> Lights();
		std::shared_ptr<Components::Camera> MainCamera();
		std::shared_ptr<Engine::Core> Core();
		std::shared_ptr<ResourceManagement::SkyboxMaterial>& Skybox();
	};
}