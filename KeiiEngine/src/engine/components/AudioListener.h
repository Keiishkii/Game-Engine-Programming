#include <memory>
#include <al.h>
#include <alc.h>

#include "Component.h"

namespace Engine
{
	namespace Components
	{
		/**	The AudioListener is a child of Component, its existance is required in the scene for audio to be heard. Each frame the position of the AudioListner component is given to OpenAL to use for its 3D audio system.  	*/
		struct AudioListener : Component
		{
		private:
		public:


		private:
			virtual void Update() override;
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			~AudioListener();
		};
	}
}