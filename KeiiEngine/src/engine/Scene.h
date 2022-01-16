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

	namespace Physics
	{
		struct PhysicsManager;
	}

	struct Entity;
	struct Core;

	/**	Scene defines the currently loaded enviroment, within which all Entitys are listed.  	*/
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
		std::vector<unsigned int> _entitysMarkedForDelete;

		std::shared_ptr<ResourceManagement::SkyboxMaterial> _skyboxMaterial;

		std::weak_ptr<Engine::Physics::PhysicsManager> _physicsManager;
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
		void CleanEntityList();

		void PreDestructor();
	public:
		/** A virtual function used by child Scene classes to load there Entity's.	*/
		virtual void LoadScene();

		/** Creates an entity and adds it to the scene with the given name.
		@param name: the name given to the entity.
		@return Returns a pointer to the newly created entity	*/
		std::shared_ptr<Entity> AddEntity(std::string name);
		/** Removes the Entity from the scene.
		@param entity: a shared pointer to the Entity about to be removed.	*/
		void RemoveEntity(std::shared_ptr<Entity> entity);

		/** Searches the list of Entity's and returns the first that shares the same name as the given string.
		@param name: the name of the entity wanted.
		@return Returns a shared pointer to the entity with the same name.	*/
		std::shared_ptr<Entity> FindEntity(std::string name);
		/** Checks if the entity dictionary has changed, either returns or regenerates the entity list to match the dictionary.
		@return Returns a list of all Entity's.	*/
		std::vector<std::shared_ptr<Entity>> Entitys();

		/** Renders the scene from the perspective of the given matrices, then returns it as a texture resource.
		@param transformationMatrix: the matrix of the cameras transform.
		@param projectionMatrix: the projection matrix used by the camera.
		@param width: the width of the image.
		@param height: the height of the image.
		@return Returns a Texture of the rendered scene.	*/
		std::shared_ptr<ResourceManagement::Texture> RenderSceneToTexture(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix, int width, int height);
		/** Renders the scene from the perspective of the given matrices, then returns it in the form of a texture buffer.
		@param transformationMatrix: the matrix of the cameras transform.
		@param projectionMatrix: the projection matrix used by the camera.
		@param width: the width of the image.
		@param height: the height of the image.
		@return Returns a GLuint for the texture buffer that the scene is rendered too.	*/
		GLuint RenderSceneToTextureBuffer(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix, int width, int height);

		/** Get Function:
		@return Returns a vector list of all Light components in the scene.	*/
		std::vector<std::weak_ptr<Components::Light>> Lights();
		/** Get Function:
		@return Returns a vector list of all Camera components in the scene.	*/
		std::vector<std::weak_ptr<Components::Camera>> Cameras();
		/** Get Function:
		@return Returns returns a shared pointer of the Camera at index[0].	*/
		std::shared_ptr<Components::Camera> MainCamera();
		/** Get Function:
		@return Returns a shared pointer of Core.	*/
		std::shared_ptr<Engine::Core> Core();
		/** Get Function:
		@return Returns a shared pointer to the Cores's PhysicsManager.	*/
		std::shared_ptr<Engine::Physics::PhysicsManager> PhysicsManager();
		/** Get Function:
		@return Returns a shared pointer to the Scenes's SkyboxMaterial.	*/
		std::shared_ptr<ResourceManagement::SkyboxMaterial>& Skybox();
	};
}