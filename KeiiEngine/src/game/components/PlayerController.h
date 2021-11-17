#include "engine/KeiiEngine.h"

namespace Game
{
	struct PlayerController : Engine::Components::Component
	{
	private:
		glm::vec3 _initialSpawnPosition;
	public:

		
	private:
	public:
		virtual void Start() override;
		virtual void Update() override;
	};
}