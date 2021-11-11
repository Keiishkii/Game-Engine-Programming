#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Component.h"

namespace Engine
{
	struct Core;
	namespace Components
	{
		struct Camera : Component
		{
			friend Core;

		private:
		public:


		private:
			virtual void Update();
			virtual void PhysicsUpdate();
		public:
			virtual void Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr) override;
		};
	}
}