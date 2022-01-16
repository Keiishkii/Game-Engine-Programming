#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Scenes
	{
		struct Scene_2 : Engine::Scene
		{
		private:
		public:


		private:
			void CreateEntity_SceneManager();

			void CreateEntity_Samus();
			void CreateEntity_Kraid();
			void CreateEntity_Camera();

			void CreateEntity_Lighting();
			void CreateEntity_Enviroment();

			void PreLoadResources();
		public:
			virtual void LoadScene() override;
		};
	}
}