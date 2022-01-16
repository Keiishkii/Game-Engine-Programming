#include <memory>

#include "Component.h"

namespace Engine
{
	namespace ResourceManagement { struct Model; }
	namespace Components
	{
		/**	The MeshRenderer is a child of Component, when placed on an entity and supplied with a mesh, all triangles within said mesh are drawn at the position of the Entity's transform.  	*/
		struct MeshRenderer : Component
		{
		private:
			std::shared_ptr<ResourceManagement::Model> _renderModel;
		public:


		private:
			virtual void Render(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix) override;
		public:
			void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity, std::shared_ptr<ResourceManagement::Model> renderModel);
		};
	}
}