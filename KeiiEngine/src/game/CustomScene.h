#include "engine/KeiiEngine.h"

namespace Game
{
	struct CustomScene : Engine::Scene
	{
	private:
	public:

		
	private:
		void CreateMapEntity();

		void CreateCameraEntity();
		void CreatePlayerEntity();

		void CreateLights();
		void CreateReflectionProbes();

		void CreateDebuggingEntity();
	public:
		virtual void LoadScene() override;
	};
}