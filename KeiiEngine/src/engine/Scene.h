#include <vector>
#include <map>
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
		struct AudioListener;
		struct ReflectionProbe;
	}

	struct Entity;
	struct Core;
	struct Scene
	{
		friend Core;
		friend Components::Camera;
		friend Components::AudioListener;
		friend Components::Light;
		friend Components::ReflectionProbe;

	private:
		bool _entityListDirty;
		std::map<unsigned int, std::shared_ptr<Entity>> _entitys;
		std::vector<std::shared_ptr<Entity>> _entityList;

		std::shared_ptr<ResourceManagement::SkyboxMaterial> _skyboxMaterial;

		std::map<unsigned int, std::weak_ptr<Components::Camera>> _cameras;
		std::weak_ptr<Components::Camera> _mainCamera;

		std::map<unsigned int, std::weak_ptr<Components::AudioListener>> _audioListeners;

		std::map<unsigned int, std::weak_ptr<Components::Light>> _lights;
		std::map<unsigned int, std::weak_ptr<Components::ReflectionProbe>> _reflectionProbes;

		std::weak_ptr<Engine::Core> _core;
	public:


	private:
		void Initialise(std::shared_ptr<Engine::Core> core);

		void Update();
		void PhysicsUpdate();

		void RenderScene(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix);
	public:
		virtual void LoadScene();
		void Destroy();

		std::shared_ptr<Entity> AddEntity(std::string name);
		void RemoveEntity(std::shared_ptr<Entity> entity);

		std::shared_ptr<Entity> FindEntity(std::string name);
		std::vector<std::shared_ptr<Entity>> Entitys();

		std::shared_ptr<ResourceManagement::Texture> RenderSceneToTexture(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix, int width, int height);
		GLuint RenderSceneToTextureBuffer(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix, int width, int height);

		std::vector<std::weak_ptr<Components::Light>> Lights();
		std::vector<std::weak_ptr<Components::Camera>> Cameras();
		std::shared_ptr<Components::Camera> MainCamera();
		std::shared_ptr<Engine::Core> Core();
		std::shared_ptr<ResourceManagement::SkyboxMaterial>& Skybox();
	};
}