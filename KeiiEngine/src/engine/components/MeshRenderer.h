#include <memory>

#include "Component.h"

namespace Engine
{
	namespace ResourceManagement { struct Model; }
	namespace Components
	{
		struct MeshRenderer : Component
		{
		private:
			std::shared_ptr<ResourceManagement::Model> _renderModel;
		public:


		private:
			virtual void Render(const std::shared_ptr<Components::Camera>& activeCamera) override;
		public:
			void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity, std::shared_ptr<ResourceManagement::Model> renderModel);
		};
	}
}