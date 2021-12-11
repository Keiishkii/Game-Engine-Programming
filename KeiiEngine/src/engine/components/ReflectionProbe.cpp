#include "ReflectionProbe.h"
#include "Transform.h"
#include "engine/core.h"
#include "engine/Scene.h"
#include "engine/Entity.h"
#include "engine/resources/ResourceManager.h"
#include "engine/resources/TextureCubeMap.h"
#include "engine/resources/Texture.h"
#include "engine/error-handling/Exception.h"
#include "Gizmo.h"

namespace Engine
{
	namespace Components
	{
		void ReflectionProbe::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			Scene()->_reflectionProbeList.push_back(std::dynamic_pointer_cast<ReflectionProbe>(self));
			Entity()->AddComponent<Gizmo>(Core()->ResourceManager()->FindAsset<ResourceManagement::Texture>("- textures/gizmo/reflection_probe.png"));
		}

		void ReflectionProbe::ReGenerateReflectionCubeMap()
		{
			if (!_reflectionCubeMap) _reflectionCubeMap = Core()->ResourceManager()->Create<ResourceManagement::TextureCubeMap>();

			_reflectionCubeMap->GenerateCubeMap(Transform()->Position());
		}

		std::shared_ptr<ResourceManagement::TextureCubeMap> ReflectionProbe::ReflectionCubeMap() 
		{ 
			if (!_reflectionCubeMap) [[unlikely]]
			{
				ReGenerateReflectionCubeMap();
			}

			return _reflectionCubeMap;
		}
	}
}