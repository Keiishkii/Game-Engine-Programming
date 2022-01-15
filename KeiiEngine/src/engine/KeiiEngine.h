#ifndef ENGINE_KEIIENGINE
	#define ENGINE_KEIIENGINE
	#define _USE_MATH_DEFINES

	#include "PhysX-4.1/include/PxPhysicsAPI.h"

	#include "Core.h"
	#include "Entity.h"
	
// Scenes
	#include "Scene.h"

// Maths
	#include "engine-maths/Maths.h"

// Time
	#include "time/TimeManager.h"

// Inputs
	#include "input/InputManager.h"
	#include "input/Inputs.h"

// Error Handling
	#include "error-handling/Debugger.h"
	#include "error-handling/Exception.h"

// Resournce Management
	#include "resources/ResourceManager.h"
	#include "resources/Resource.h"
	#include "resources/ShaderProgram.h"
	#include "resources/Model.h"
	#include "resources/AudioClip.h"
	#include "resources/Material.h"
	#include "resources/SkyboxMaterial.h"
	#include "resources/Texture.h"
	#include "resources/TextureCubeMap.h"

// Components
	#include "components/Component.h"
	#include "components/RigidBody.h"
	#include "components/Collider.h"
	#include "components/CapsuleCollider.h"
	#include "components/AudioListener.h"
	#include "components/AudioSource.h"
	#include "components/Transform.h"
	#include "components/Camera.h"
	#include "components/ReflectionProbe.h"
	#include "components/Light.h"
	#include "components/Gizmo.h"
	#include "components/MeshRenderer.h"

// Physics
#include "physics/PhysicsManager.h"

// Audio
	#include "audio/AudioManager.h"
	#include "audio/AudioBuffer.h"

// Graphics
	#include "graphics/GraphicsManager.h"
	#include "graphics/PolygonMaterialGroup.h"
	#include "graphics/VertexBuffer.h"
	#include "graphics/VertexArray.h"

	using namespace Engine;
#endif // !ENGINE_KEIIENGINE
