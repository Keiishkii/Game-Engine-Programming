#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Components
	{
		/**	A Component class used to control the player character Samus Aran.  	*/
		struct SamusController : Engine::Components::Component
		{
		private:
			std::shared_ptr<Engine::Components::Transform> _cameraTransform;

			std::shared_ptr<Engine::Components::AudioSource> _rocketAudioSource;
			std::shared_ptr<Engine::Components::AudioSource> _superRocketAudioSource;

			float _movementSpeed = 1.0f;
		public:


		private:
			virtual void Start() override;
			virtual void Update() override;

			void WeaponControls(std::shared_ptr<Inputs> inputs);
			void MovementControls(std::shared_ptr<Inputs> inputs);

			void SpawnRocket();
			void SpawnSuperRocket();
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			void SetMovementSpeed(float speed);
		};
	}
}