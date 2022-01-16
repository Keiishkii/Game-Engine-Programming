#include "PostProcessorEffects.h"

namespace Game
{
	namespace Components
	{		
		void PostProcessorEffects::Start()
		{
			_postProcessingShaders.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/- Post Processing/buffer_shader_shader.glsl"));
			_postProcessingShaders.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/- Post Processing/buffer_shader_shader_inverted.glsl"));

			Core()->GraphicsManager()->SetPostProcessingShader(_postProcessingShaders[_selectedShaderIndex]);
		}

		void PostProcessorEffects::Update()
		{
			std::shared_ptr<Inputs> inputs = Input();

			if (inputs->KeyDown(inputs->P))
			{
				_selectedShaderIndex = (_selectedShaderIndex + 1 >= _postProcessingShaders.size()) ? (0) : (_selectedShaderIndex + 1);
				Core()->GraphicsManager()->SetPostProcessingShader(_postProcessingShaders[_selectedShaderIndex]);
			}
		}
	}
}