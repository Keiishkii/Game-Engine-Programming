#include "engine/KeiiEngine.h"

namespace Game
{
	struct ShaderTextureSampler : Engine::Components::Component
	{
	private:
		std::shared_ptr<ResourceManagement::Material> _material;
	public:


	private:
	public:
		virtual void Start() override;
		virtual void Update() override;

		void Hello();
	};
}