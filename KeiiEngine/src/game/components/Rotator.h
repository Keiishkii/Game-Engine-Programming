#include "engine/KeiiEngine.h"

namespace Game
{
	struct Rotator : Engine::Components::Component
	{
	private:
		int test = 500;

		glm::quat _startingRotation;
		glm::vec3 _eulerRotationSpeed;
	public:


	private:
	public:
		virtual void Start() override;
		virtual void Update() override;

		glm::vec3& EulerRotation();		
	};
}