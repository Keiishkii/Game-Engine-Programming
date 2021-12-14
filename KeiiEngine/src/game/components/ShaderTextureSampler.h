#include "engine/KeiiEngine.h"
#include <vector>

namespace Game
{
	struct ShaderTextureSampler : Engine::Components::Component
	{
	private:
		int activeProperty;
		std::vector<std::string> _propertyNames;

		int activeMaterialSelection;
		std::vector<std::shared_ptr<ResourceManagement::Material>> _materials;

		int activeShader;
		std::vector<std::shared_ptr<ResourceManagement::ShaderProgram>> _shaders;
	public:


	private:
	public:
		virtual void Start() override;
		virtual void Update() override;

		void Hello();
	};
}