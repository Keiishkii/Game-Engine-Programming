#include <memory>
#include <vector>
#include <string>

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
		std::string _name;

		std::weak_ptr<Entity> _self;
		std::weak_ptr<Engine::Core> _core;
		std::weak_ptr<Components::Transform> _transform;

		std::vector<std::shared_ptr<Components::Component>> _componentList;
	public:


	private:
		void Initialise(std::shared_ptr<Entity> self, std::shared_ptr<Engine::Core> core);

		void Update();
		void Render(const std::shared_ptr<Components::Camera>& activeCamera);
		void PhysicsUpdate();

		std::shared_ptr<Entity> Self();
	public:
		Entity(std::string name);

		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			std::shared_ptr<Entity> self = Self();

			component->Component::Initialise(component, self);
			component->Initialise(component, self);

			_componentList.push_back(component);

			return component;
		}

		template <typename T, typename A>
		std::shared_ptr<T> AddComponent(A parameter)
		{
			std::shared_ptr<T> component = std::make_shared<T>(parameter);
			std::shared_ptr<Entity> self = Self();

			component->Component::Initialise(component, self);
			component->Initialise(component, self);

			_componentList.push_back(component);

			return component;
		}

		std::string& Name();
		std::shared_ptr<Core> Core();
		std::shared_ptr<Components::Transform> Transform();
	};
}