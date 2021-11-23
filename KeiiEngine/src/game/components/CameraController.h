#include "engine/KeiiEngine.h"

namespace Game
{
	struct CameraController : Engine::Components::Component
	{
	private:
		std::shared_ptr<Engine::Components::Transform> _orbitTarget;

		float _orbitDistance = 6, _orbitDistanceTarget = 6;
		float _xValue = 0, _yValue = 0;

		float _orbitSpinSpeedMulitplier = 0.0025f;
		float _orbitZoomSpeedMulitplier = 0.5f;
		glm::vec3 _orbitOffset = glm::vec3(0, 1.5f, 0);
	public:


	private:
		float Lerp(float x, float y, float t);
		glm::vec3 Lerp(glm::vec3 x, glm::vec3 y, float t);
	public:
		virtual void Start() override;
		virtual void Update() override;

		void SetOrbitTarget(std::shared_ptr<Engine::Components::Transform> transform);
	};
}