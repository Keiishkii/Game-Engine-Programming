#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Scenes
	{
		/**	Scene defines the currently loaded enviroment, within which all Entitys are listed.  	*/
		struct Scene_3 : Engine::Scene
		{
		private:
		public:


		private:
			void CreateEntity_SceneManager();

			void CreateEntity_Player();
			void CreateEntity_Camera();
		public:
			/** Overrides the base class load function and spawns the scenes Entity's.	*/
			virtual void LoadScene() override;
		};
	}
}