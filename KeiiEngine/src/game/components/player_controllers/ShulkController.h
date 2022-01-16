#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Components
	{
		/**	A Component class used to control the player character Shulk.  	*/
		struct ShulkController : Engine::Components::Component
		{
		private:
			std::shared_ptr<Engine::Components::Transform> _cameraTransform;
			float _movementSpeed = 1.0f;
		public:


		private:
			virtual void Start() override;
			virtual void Update() override;

			void MovementControls(std::shared_ptr<Inputs> inputs);
		public:
			void SetMovementSpeed(float speed);
		};
	}
}