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
			MeshRenderer(std::shared_ptr<ResourceManagement::Model> renderModel);
		};
	}
}