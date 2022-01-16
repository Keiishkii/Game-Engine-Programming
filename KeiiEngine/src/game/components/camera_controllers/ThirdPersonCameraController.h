#include "engine/KeiiEngine.h"

namespace Game
{
	namespace Components
	{
		/**	A Component class that allows for the control of a camera, orbiting around a player entity.  	*/
		struct ThirdPersonCameraController : Engine::Components::Component
		{
		private:
			std::weak_ptr<Engine::Components::Transform> _orbitTarget;

			float _maxOrbitDistance = 8.0f, _minOrbitDistance = 0.5f;
			float _desiredOrbitDistance = 6.0f, _currentOrbitDistance = 6.0f;
			float _theta = 0, _phi = 0;

			float _orbitRotationSpeed = 0.0025f;
			float _orbitZoomSpeed = 0.5f;

			glm::vec3 _orbitOffset = glm::vec3(0, 0, 0);
		public:


		private:
			void RecalcualteOrbitAngle();
			void RecalcualteOrbitDistance();
		public:
			virtual void Start() override;
			virtual void Update() override;

			void SetOrbitTarget(std::shared_ptr<Engine::Components::Transform> transform);
			void SetOrbitTarget(std::shared_ptr<Engine::Entity> entity);
			void SetOrbitOffset(glm::vec3 offset);
		};
	}
}