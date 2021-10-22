#include <memory>
#include <vector>

namespace Engine
{
	struct Debugger;
	struct Entity;
	struct Core
	{
	private:
		std::weak_ptr<Core> _self;

		std::shared_ptr<Debugger> _debugger;
		std::vector<std::shared_ptr<Entity>> _entityList;

		int targetUpdatesPerSecond;
		bool running;

	private:
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