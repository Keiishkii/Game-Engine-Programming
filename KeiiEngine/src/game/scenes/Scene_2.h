#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Scenes
	{
		/**	Scene defines the currently loaded enviroment, within which all Entitys are listed.  	*/
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
			/** Overrides the base class load function and spawns the scenes Entity's.	*/
			virtual void LoadScene() override;
		};
	}
}