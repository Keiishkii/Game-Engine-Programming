#ifndef ENGINE_KEIIENGINE
#define ENGINE_KEIIENGINE
#define _USE_MATH_DEFINES

	#include "Core.h"
	#include "TimeManager.h"
	#include "InputManager.h"
	#include "Inputs.h"

	#include "Scene.h"
	#include "Entity.h"

// Error Handling
	#include "error-handling/Debugger.h"
	#include "error-handling/Exception.h"

// Resournce Management
	#include "resources/ResourceManager.h"
	#include "resources/Resource.h"
	#include "resources/ShaderProgram.h"
	#include "resources/Model.h"
	#include "resources/Sound.h"
	#include "resources/Material.h"
	#include "resources/SkyboxMaterial.h"
	#include "resources/Texture.h"
	#include "resources/TextureCubeMap.h"

// Components
	#include "components/Component.h"
	#include "components/Transform.h"
	#include "components/Camera.h"
	#include "components/Light.h"
	#include "components/Gizmo.h"
	#include "components/MeshRenderer.h"

// Graphics
	#include "graphics/GraphicsManager.h"
	#include "graphics/PolygonMaterialGroup.h"
	#include "graphics/VertexBuffer.h"
	#include "graphics/VertexArray.h"

	using namespace Engine;
#endif // !ENGINE_KEIIENGINE
