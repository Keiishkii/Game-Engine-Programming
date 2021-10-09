#include <iostream>

#include "KeiiEngine.h"


template <typename T>
std::shared_ptr<T> AddComponent();

int main()
{
	std::shared_ptr<Core> core = Core::Initialise();

	std::shared_ptr<Entity> entity = core->AddEntity();
	std::shared_ptr<Component> component = entity->AddComponent<Component>();

	//core->Start();

	return 0;
}

template <typename T>
std::shared_ptr<T> AddComponent()
{
	std::shared_ptr<T> component = std::make_shared<T>();
	//componentList.push_back(component);

	std::cout << "Hi" << std::endl;

	return component;
}