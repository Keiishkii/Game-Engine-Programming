#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Component.h"

namespace Engine
{
	namespace Components
	{
		struct Transform : Component
		{
		private:
		public:
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scale;


		private:
			virtual void Update() override;
			virtual void PhysicsUpdate() override;
		public:
			Transform();
			virtual void Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPtr) override;

			glm::mat4x4 TransformationMatrix();
		};
	}
}