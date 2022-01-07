#include <memory>
#include <vector>
#include <map>
#include <string>

namespace Engine
{
	namespace Components
	{
		struct Component;
		struct Camera;
		struct Transform;
	}
	
	struct Core;
	struct Scene;
	struct SystemIndexer;
	struct Entity
	{
		friend Engine::Scene;

	private:
		unsigned int _systemIndex = 0;

		std::string _name;

		std::weak_ptr<Entity> _self;
		std::weak_ptr<Engine::Core> _core;
		std::weak_ptr<Engine::SystemIndexer> _systemIndexer;
		std::weak_ptr<Components::Transform> _transform;

		bool _componentListDirty;
		std::map<unsigned int, std::shared_ptr<Components::Component>> _components;
		std::vector<std::shared_ptr<Components::Component>> _componentList;
	public:


	private:
		void Initialise(std::shared_ptr<Entity> self, std::shared_ptr<Engine::Core> core);

		void Update();
		void Render(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix);
		void PhysicsUpdate();

		std::shared_ptr<Entity> Self();
		std::vector<std::shared_ptr<Components::Component>> Components();
	public:
		Entity(std::string name);
		~Entity();

		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			std::shared_ptr<Entity> self = Self();

			component->Component::Initialise(component, self);
			component->Initialise(component, self);

			_components[component->_systemIndex] = component;
			_componentListDirty = true;

			return component;
		}

		template <typename T, typename A>
		std::shared_ptr<T> AddComponent(A parameter)
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			std::shared_ptr<Entity> self = Self();

			component->Component::Initialise(component, self);
			component->Initialise(component, self, parameter);

			_components[component->_systemIndex] = component;
			_componentListDirty = true;

			return component;
		}

		void RemoveComponent(std::shared_ptr<Components::Component> component);

		std::string& Name();
		std::shared_ptr<Core> Core();
		std::shared_ptr<SystemIndexer> SystemIndexer();
		std::shared_ptr<Components::Transform> Transform();
	};
}