#include <memory>
#include <al.h>
#include <alc.h>

#include "Component.h"

namespace Engine
{
	namespace Components
	{
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