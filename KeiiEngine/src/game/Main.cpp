#include <iostream>

#include "engine/KeiiEngine.h"

int main()
{
	std::shared_ptr<Core> core = Core::Initialise();

	std::cout << "Shader Test" << std::endl;
	std::shared_ptr<ResourceManagement::ShaderProgram> shader = core->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/shaderprogram.glsl");
	std::cout << " - ShaderID: " << shader->GetShaderID() << std::endl;

	std::cout << "Model Test" << std::endl;
	std::shared_ptr<ResourceManagement::Model> model = core->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/shulk.fbx");
	std::cout << " - Total Model Vertex Count: " << model->TotalVertexCount() << std::endl;

	for (int i = 0; i < model->TotalMaterialGroups(); i++)
	{
		std::cout << "	 - Model Material Group ("<< i << ") Vertex Count : " << model->GetPolygonMaterialGroup(i)->VertexCount() << std::endl;
	}

	//std::shared_ptr<Entity> entity = core->AddEntity();
	//std::shared_ptr<Components::Camera> component = entity->AddComponent<Components::Camera>();

	//core->Start();

	return 0;
}