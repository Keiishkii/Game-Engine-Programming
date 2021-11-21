#include "engine/KeiiEngine.h"

namespace Game
{
	struct PlayerController : Engine::Components::Component
	{
	private:
		std::shared_ptr<Engine::Components::Transform> _cameraTransform;

		float _movementSpeed = 5.0f;
	public:

		
	private:
	public:
		virtual void Start() override;
		virtual void Update() override;
	};
}