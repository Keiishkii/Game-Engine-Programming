#include <iostream>

#include "engine/KeiiEngine.h"


int main()
{
	std::shared_ptr<Core> core = Core::Initialise();
	core->ResourceManager()->FindAsset("shaderprogram.shader");
	
	std::shared_ptr<ResourceManagement::ShaderProgram> shader = std::dynamic_pointer_cast<ResourceManagement::ShaderProgram>(core->ResourceManager()->FindAsset("shaderprogram.shader"));
	std::cout << " - ShaderID: " << shader->GetShaderID() << std::endl;

	//std::shared_ptr<Entity> entity = core->AddEntity();
	//std::shared_ptr<Component> component = entity->AddComponent<Component>();

	core->Start();

	return 0;
}