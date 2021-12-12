#include <iostream>
#include <glew.h>

#include "Camera.h"
#include "Gizmo.h"
#include "engine/Core.h"
#include "engine/Scene.h"
#include "Transform.h"
#include "engine/entity.h"
#include "engine/resources/SkyboxMaterial.h"
#include "engine/resources/Model.h"
#include "engine/resources/Texture.h"
#include "engine/resources/TextureCubeMap.h"
#include "engine/resources/ShaderProgram.h"
#include "engine/resources/ResourceManager.h"
#include "engine/graphics/PolygonMaterialGroup.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace Components
	{
		void Camera::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			Scene()->_cameraList.push_back(std::dynamic_pointer_cast<Camera>(self));
			Entity()->AddComponent<Gizmo>(Core()->ResourceManager()->FindAsset<ResourceManagement::Texture>("- textures/gizmo/camera.png"));
		}
	
		void Camera::GenerateNewProjectionMatrix(float windowWidth, float windowHeight, float fieldOfView)
		{
			_projectionMatrix = glm::perspective(glm::radians(fieldOfView), (float)windowWidth / (float)windowHeight, 0.25f, 5000.f);
		}

		glm::mat4x4& Camera::ProjectionMatrix() { return _projectionMatrix; }
	}
}