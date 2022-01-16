#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Scenes
	{
		struct Scene_3 : Engine::Scene
		{
		private:
		public:


		private:
			void CreateEntity_SceneManager();

			void CreateEntity_Player();
			void CreateEntity_Camera();
		public:
			virtual void LoadScene() override;
		};
	}
}