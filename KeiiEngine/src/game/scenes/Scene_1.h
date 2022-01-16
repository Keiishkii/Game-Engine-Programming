#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Scenes
	{
		/**	Scene defines the currently loaded enviroment, within which all Entitys are listed.  	*/
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
			/** Overrides the base class load function and spawns the scenes Entity's.	*/
			virtual void LoadScene() override;
		};
	}
}