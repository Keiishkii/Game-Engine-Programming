#include <memory>
#include <vector>


namespace Engine
{
	struct Core;
	struct Component;
	struct Entity
	{
		friend Engine::Core;
	private:
		std::weak_ptr<Entity> _self;

		std::vector<std::shared_ptr<Component>> componentList;

	public:
		std::weak_ptr<Engine::Core> corePtr;

	private:
		static std::shared_ptr<Entity> Initialise(std::weak_ptr<Core> corePtr);
		
		void Update();
		void PhysicsUpdate();

	public:
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			componentList.push_back(component);

			return component;
		}
	};
}