#include <iostream>

#include "Transform.h"

Engine::Transform::Transform()
{
	position = glm::vec3{ 0, 0, 0 };
	rotation = glm::vec4{ 1, 0, 0, 0 };
	scale = glm::vec3{ 1, 1, 1 };
}

void Engine::Transform::Update()
{
	std::cout << "Transform:" << std::endl;
	std::cout << "		 - Position:	{" << position.x << ", " << position.y << ", " << position.z << "}" << std::endl;
	std::cout << "		 - Rotation:	{" << rotation.x << ", " << rotation.y << ", " << rotation.z << ", " << rotation.w << "}" << std::endl;
	std::cout << "		 - Scale:	{" << scale.x << ", " << scale.y << ", " << scale.z << "}" << std::endl;
}

void Engine::Transform::PhysicsUpdate()
{

}