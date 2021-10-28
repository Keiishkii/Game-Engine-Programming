#pragma once
#ifndef CAMERA
#define CAMERA
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Component.h"

namespace Engine
{
	struct Core;
	struct Camera : Component
	{
		friend Core;

	private:
		virtual void Update();
		virtual void PhysicsUpdate();

	public:
		Camera();
	};
}
#endif