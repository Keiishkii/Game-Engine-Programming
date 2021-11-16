#include <memory>
#include <vector>

namespace Engine
{
	struct Core;
	namespace Components
	{
		struct Component;
		struct Camera;
		struct Transform;
	}
	
	struct Entity
	{
		friend Engine::Core;

	private:
		std::weak_ptr<Entity> _self;
		std::weak_ptr<Components::Transform> _transform;

		std::vector<std::shared_ptr<Components::Component>> componentList;

	public:
		std::weak_ptr<Engine::Core> corePtr;

	private:
		static std::shared_ptr<Entity> Initialise(std::weak_ptr<Core> corePtr);

		void Update();
		void Render(std::weak_ptr<Components::Camera>& activeCamera);
		void PhysicsUpdate();

	public:
		std::weak_ptr<Components::Transform> Transform();

		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			component->Initialise(component, _self);

			componentList.push_back(component);

			return component;
		}

		template <typename T, typename A>
		std::shared_ptr<T> AddComponent(A parameter)
		{
			std::shared_ptr<T> component = std::make_shared<T>(parameter);
			component->Initialise(component, _self);

			componentList.push_back(component);

			return component;
		}
	};
}