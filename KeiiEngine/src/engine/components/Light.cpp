#include "Light.h"

#include "engine/Core.h"
#include "engine/Entity.h"
#include "engine/resources/ResourceManager.h"
#include "engine/resources/Texture.h"
#include "engine/error-handling/Exception.h"
#include "Gizmo.h"

namespace Engine
{
	namespace Components
	{
		void Light::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			Core()->_lightList.push_back(std::dynamic_pointer_cast<Light>(self));
			Entity()->AddComponent<Gizmo>(Core()->ResourceManager()->FindAsset<ResourceManagement::Texture>("- textures/gizmo/point_light.png"));
		}

		glm::vec3& Light::Colour() { return _colour; };
		float& Light::Intensity() { return _intensity; }
	}
}