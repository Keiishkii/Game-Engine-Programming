#include <iostream>

#include "KeiiEngine.h"



int main()
{
	std::shared_ptr<Core> core = Core::Initialise();

	std::shared_ptr<Entity> entity = core->AddEntity();
	std::shared_ptr<Component> component = entity->AddComponent<Component>();

	core->Start();

	return 0;
}