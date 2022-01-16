#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Scenes
	{
		struct Scene_1 : Engine::Scene
		{
		private:
		public:


		private:
			void CreateEntity_SceneManager();

			void CreateEntity_Player();
			void CreateEntity_Camera();

			void CreateEntity_Lighting();
			void CreateEntity_Enviroment();
		public:
			virtual void LoadScene() override;
		};
	}
}