#include "AudioListener.h"
#include "engine/Scene.h"
#include "engine/Entity.h"
#include "engine/resources/Texture.h"
#include "engine/resources/ResourceManager.h"
#include "engine/Core.h"
#include "Transform.h"
#include "Gizmo.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace Components
	{
		void AudioListener::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			Scene()->_audioListeners[_systemIndex] = std::dynamic_pointer_cast<AudioListener>(self);
			Entity()->AddComponent<Gizmo>(Core()->ResourceManager()->FindAsset<ResourceManagement::Texture>("- textures/gizmo/audio_listener.png"));
		}

		AudioListener::~AudioListener()
		{
			if (Scene())
			{
				Scene()->_audioListeners.erase(Scene()->_audioListeners.find(_systemIndex));
			}
		}

		void AudioListener::Update()
		{
			glm::vec3 position = Transform()->Position();
			alListener3f(AL_POSITION, position.x, position.y, position.z);
		}
	}
}