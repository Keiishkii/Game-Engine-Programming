#include <iostream>

#include "engine/KeiiEngine.h"


int main()
{
	std::shared_ptr<Core> core = Core::Initialise();
	core->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("shaderprogram.glsl");
	
	std::shared_ptr<ResourceManagement::ShaderProgram> shader = core->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("shaderprogram.glsl");
	std::cout << " - ShaderID: " << shader->GetShaderID() << std::endl;

	//std::shared_ptr<Entity> entity = core->AddEntity();
	//std::shared_ptr<Component> component = entity->AddComponent<Component>();

	core->Start();

	return 0;
}