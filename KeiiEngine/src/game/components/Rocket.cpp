#include "Rocket.h"

namespace Game
{
	namespace Components
	{		
		void Rocket::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			std::shared_ptr<Engine::Components::AudioSource> rocketFlightAudioSource = Entity()->AddComponent<Engine::Components::AudioSource>();
			rocketFlightAudioSource->SetAudioClip(Core()->ResourceManager()->FindAsset<ResourceManagement::AudioClip>("- audio/sfx/samus/rocket_flight.ogg"));
			rocketFlightAudioSource->PlayOnStart(true);
			rocketFlightAudioSource->Looping(true);
		}

		void Rocket::Update()
		{
			float deltaTime = TimeManager()->DeltaTime();
			Transform()->Position() += _flightVector * deltaTime;

			_lifeTime -= deltaTime;
			if (_lifeTime <= 0)
			{
				Scene()->RemoveEntity(Entity());
			}
		}

		void Rocket::SetFlightVector(glm::vec3 flightVector)
		{
			_flightVector = flightVector;
		}
	}
}