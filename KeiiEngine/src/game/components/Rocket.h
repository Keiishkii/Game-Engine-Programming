#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Components
	{
		struct Rocket : Engine::Components::Component
		{
		private:
			float _lifeTime = 10.0f;
			glm::vec3 _flightVector = glm::vec3(0);
		public:


		private:
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			virtual void Update() override;
			void SetFlightVector(glm::vec3 flightVector);
		};
	}
}