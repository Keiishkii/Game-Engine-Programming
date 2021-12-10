#include "engine/KeiiEngine.h"

namespace Game
{
	struct CustomScene : Engine::Scene
	{
	private:
	public:

		
	private:
		std::shared_ptr<Entity> CreateDebuggingEntity();
		std::shared_ptr<Entity> CreateCameraEntity();
		std::shared_ptr<Entity> CreatePlayerEntity();
		std::shared_ptr<Entity> CreateMapEntity();
		std::shared_ptr<Entity> CreateLightEntity();
	public:
		virtual void LoadScene() override;
	};
}