#include "CameraController.h"

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

namespace Game
{
	void CameraController::Start()
	{
		if (Scene()->FindEntity("Player"))
			_orbitTarget = Scene()->FindEntity("Player")->Transform();
	}

	void CameraController::Update()
	{
		if (_orbitTarget)
		{
			glm::vec2 mouseDelta = Input()->MousePosition();
			float scrollDelta = Input()->MouseScrollDelta();

			_xValue -= (mouseDelta.x * _orbitSpinSpeedMulitplier), _yValue += (mouseDelta.y * _orbitSpinSpeedMulitplier);
			_yValue = std::max(-1.0f, std::min(_yValue, 1.0f));

			_orbitDistanceTarget += (scrollDelta * _orbitZoomSpeedMulitplier);
			_orbitDistanceTarget = std::max(1.5f, std::min(_orbitDistanceTarget, 8.0f));
			_orbitDistance = Lerp(_orbitDistance, _orbitDistanceTarget, 0.075f);


			glm::vec3 positionOfPlayer = _orbitTarget->Position();
			glm::vec3 position = positionOfPlayer + _orbitOffset + glm::vec3(
				sin(_xValue) * cos(_yValue) * _orbitDistance,
				sin(_yValue) * _orbitDistance,
				cos(_xValue) * cos(_yValue) * _orbitDistance);


			Transform()->Position() = Lerp(Transform()->Position(), position, 0.075f);
			Transform()->Rotation() = glm::identity<glm::quat>() * glm::quatLookAt(glm::normalize(positionOfPlayer + _orbitOffset - Transform()->Position()), glm::vec3(0, 1, 0));
		}
	}

	void CameraController::SetOrbitTarget(std::shared_ptr<Engine::Components::Transform> transform)
	{
		_orbitTarget = transform;
	}

	glm::vec3 CameraController::Lerp(glm::vec3 x, glm::vec3 y, float t) 
	{
		return x * (1.f - t) + y * t;
	}

	float CameraController::Lerp(float x, float y, float t)
	{
		return x * (1.f - t) + y * t;
	}
}