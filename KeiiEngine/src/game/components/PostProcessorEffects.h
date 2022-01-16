#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Components
	{
		struct PostProcessorEffects : Engine::Components::Component
		{
		private:
			int _selectedShaderIndex = 0;
			std::vector<std::shared_ptr<Engine::ResourceManagement::ShaderProgram>> _postProcessingShaders;
		public:


		private:
		public:
			virtual void Start() override;
			virtual void Update() override;
		};
	}
}