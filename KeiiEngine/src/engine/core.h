#include <memory>
#include <vector>

namespace Engine
{
	struct Entity;
	struct Core
	{
	private:
		std::vector<std::shared_ptr<Entity>> entityList;

		int targetUpdatesPerSecond;
		bool running;

		void MainLoop();

		void Update();
		void PhysicsUpdate();

	public:
		static std::shared_ptr<Core> Initialise();

		void Start();
		void Stop();

		std::shared_ptr<Entity> AddEntity();
	};
}