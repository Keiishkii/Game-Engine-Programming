#pragma once
#ifndef ENTITY
#define ENTITY
	#include <memory>
	#include <vector>

namespace Engine
{
	struct Core;
	struct Component;
	struct Transform;
	struct Entity
	{
		friend Engine::Core;

	private:
		std::weak_ptr<Entity> _self;
		std::weak_ptr<Transform> _transform;

		std::vector<std::shared_ptr<Component>> componentList;

	public:
		std::weak_ptr<Engine::Core> corePtr;

	private:
		static std::shared_ptr<Entity> Initialise(std::weak_ptr<Core> corePtr);

		void Update();
		void Render();
		void PhysicsUpdate();

	public:
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = std::make_shared<T>();
			component->Initialise(component, _self);

			componentList.push_back(component);

			return component;
		}
	};
}

#endif