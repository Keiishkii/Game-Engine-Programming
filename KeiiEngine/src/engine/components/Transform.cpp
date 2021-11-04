#include <iostream>

#include "Transform.h"
#include "engine/entity.h"

Engine::Transform::Transform()
{
	position = glm::vec3{ 0, 0, 0 };
	rotation = glm::quat{ 1, 0, 0, 0 };
	scale = glm::vec3{ 1, 1, 1 };
}

void Engine::Transform::Initialise(std::weak_ptr<Component> self, std::weak_ptr<Entity> entityPointer)
{
	std::shared_ptr<Transform> transform = std::dynamic_pointer_cast<Transform>(self.lock());

	_self = self;
	entityPtr = entityPointer;
	corePtr = entityPointer.lock()->corePtr;
}

void Engine::Transform::Update()
{
	std::cout << "Transform:" << std::endl;
	std::cout << "		 - Position:	{" << position.x << ", " << position.y << ", " << position.z << "}" << std::endl;
	std::cout << "		 - Rotation:	{" << rotation.w << ", " << rotation.x << ", " << rotation.y << ", " << rotation.z << "}" << std::endl;
	std::cout << "		 - Scale:	{" << scale.x << ", " << scale.y << ", " << scale.z << "}" << std::endl;
}

void Engine::Transform::PhysicsUpdate()
{

}