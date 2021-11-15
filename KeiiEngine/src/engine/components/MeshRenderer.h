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
			virtual void Update() override;
			virtual void PhysicsUpdate() override;
			virtual void Render() override;
		public:
			MeshRenderer(std::shared_ptr<ResourceManagement::Model> renderModel);
		};
	}
}