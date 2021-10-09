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
		std::vector<std::shared_ptr<Component>> componentList;

	private:
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