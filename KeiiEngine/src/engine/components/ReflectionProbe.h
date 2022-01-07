#include "Component.h"

namespace Engine
{
	namespace ResourceManagement { struct TextureCubeMap; }
	namespace Components
	{
		struct ReflectionProbe : Component
		{
		private:
			std::shared_ptr<ResourceManagement::TextureCubeMap> _reflectionCubeMap;
		public:


		private:
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			~ReflectionProbe();

			void ReGenerateReflectionCubeMap();
			std::shared_ptr<ResourceManagement::TextureCubeMap> ReflectionCubeMap();
		};
	}
}