#include "glm/stb_image.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "TextureCubeMap.h"
#include "Texture.h"
#include "engine/error-handling/Exception.h"
#include <iostream>
#include <vector>

#include "engine/Core.h"
#include "engine/Scene.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void TextureCubeMap::Load(const std::string& resourcesDirectory, const std::string& subPath)
		{
			std::string path = resourcesDirectory + subPath;

			std::string pathWithoutExtension = path.substr(0, path.size() - 4);
			std::string pathExtension = path.substr(path.size() - 4);
			

			std::string subPathWithoutExtension = subPath.substr(0, subPath.size() - 4);
			std::string subPathExtension = subPath.substr(subPath.size() - 4);



			_rightTexture =  ResourceManager()->FindAsset<Texture>(subPathWithoutExtension + _faceSuffexes[0] + subPathExtension);
			if (!_rightTexture)
				throw ErrorHandling::Exception("Failed to load right texture of cube map");

			_leftTexture =   ResourceManager()->FindAsset<Texture>(subPathWithoutExtension + _faceSuffexes[1] + subPathExtension);
			if (!_leftTexture)
				throw ErrorHandling::Exception("Failed to load left texture of cube map");

			_topTexture =	 ResourceManager()->FindAsset<Texture>(subPathWithoutExtension + _faceSuffexes[2] + subPathExtension);
			if (!_topTexture)
				throw ErrorHandling::Exception("Failed to load top texture of cube map");

			_bottomTexture = ResourceManager()->FindAsset<Texture>(subPathWithoutExtension + _faceSuffexes[3] + subPathExtension);
			if (!_bottomTexture)
				throw ErrorHandling::Exception("Failed to load bottom texture of cube map");

			_frontTexture =  ResourceManager()->FindAsset<Texture>(subPathWithoutExtension + _faceSuffexes[4] + subPathExtension);
			if (!_frontTexture)
				throw ErrorHandling::Exception("Failed to load front texture of cube map");

			_backTexture =	 ResourceManager()->FindAsset<Texture>(subPathWithoutExtension + _faceSuffexes[5] + subPathExtension);
			if (!_backTexture)
				throw ErrorHandling::Exception("Failed to load back texture of cube map");
		}

		void TextureCubeMap::GenerateCubeMap(glm::vec3 position)
		{
			glm::mat4x4 projectionMatrix = glm::perspective(glm::radians(90.0f), 1.0f, 0.25f, 5000.f);

			glm::mat4x4 scaleMatrix = glm::scale(glm::identity<glm::mat4x4>(), glm::vec3(1, 1, 1));
			glm::mat4x4 translationMatrix = glm::translate(glm::identity<glm::mat4x4>(), position);

			glm::mat4x4 rightTransformationMatrix;
			{
				glm::mat4x4 rotationMatrix = glm::mat4_cast(glm::quat(glm::vec3(M_PI, (M_PI / 2), 0)));
				rightTransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			}

			glm::mat4x4 leftTransformationMatrix;
			{
				glm::mat4x4 rotationMatrix = glm::mat4_cast(glm::quat(glm::vec3(M_PI, -(M_PI / 2), 0)));
				leftTransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			}

			glm::mat4x4 topTransformationMatrix;
			{
				glm::mat4x4 rotationMatrix = glm::mat4_cast(glm::quat(glm::vec3((M_PI / 2), 0, 0)));
				topTransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			}

			glm::mat4x4 bottomTransformationMatrix;
			{
				glm::mat4x4 rotationMatrix = glm::mat4_cast(glm::quat(glm::vec3(-(M_PI / 2), 0, 0)));
				bottomTransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			}

			glm::mat4x4 frontTransformationMatrix;
			{
				glm::mat4x4 rotationMatrix = glm::mat4_cast(glm::quat(glm::vec3(M_PI, 0, 0)));
				frontTransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			}

			glm::mat4x4 backTransformationMatrix;
			{
				glm::mat4x4 rotationMatrix = glm::mat4_cast(glm::quat(glm::vec3(M_PI, M_PI, 0)));
				backTransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			}


			std::shared_ptr<Scene> scene = Core()->ActiveScene();


			_rightTexture = scene->RenderSceneToTexture(rightTransformationMatrix, projectionMatrix, 1024, 1024);
			_leftTexture = scene->RenderSceneToTexture(leftTransformationMatrix, projectionMatrix, 1024, 1024);

			_topTexture = scene->RenderSceneToTexture(topTransformationMatrix, projectionMatrix, 1024, 1024);
			_bottomTexture = scene->RenderSceneToTexture(bottomTransformationMatrix, projectionMatrix, 1024, 1024);

			_frontTexture = scene->RenderSceneToTexture(frontTransformationMatrix, projectionMatrix, 1024, 1024);
			_backTexture = scene->RenderSceneToTexture(backTransformationMatrix, projectionMatrix, 1024, 1024);
		}

		void TextureCubeMap::GenerateCubeMapConvolution()
		{
			/*
			if (!_textureConvolutionID)
			{
				glGenTextures(1, &_textureConvolutionID);
			}

			glBindTexture(GL_TEXTURE_CUBE_MAP, _textureConvolutionID);

			int width = 1024, height = 1024;
			for (unsigned int i = 0; i < 6; ++i)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);



			GLuint framebufferID;
			glGenFramebuffers(1, &framebufferID);

			glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
			glBindRenderbuffer(GL_RENDERBUFFER, framebufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

			std::shared_ptr<ResourceManagement::ShaderProgram> convolutionShader = Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/- PBR/shader_program_CubeMapConvolution.glsl");

			convolutionShader->UseShader();

			irradianceShader.setInt("environmentMap", 0);
			GLint projectionMatrixID = glGetUniformLocation(programID, "in_Projection");
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

			glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
			glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
			for (unsigned int i = 0; i < 6; ++i)
			{
				irradianceShader.setMat4("view", captureViews[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				renderCube();
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);



			glDeleteFramebuffers(1, &framebufferID);*/
		}

		GLuint TextureCubeMap::GetCubeMapConvolutionTextureID()
		{
			if (!_textureConvolutionID)
			{
				GenerateCubeMapConvolution();
			}

			return _textureConvolutionID;
		}

		GLuint TextureCubeMap::GetCubeMapTextureID()
		{
			if (!_textureID)
			{
				glGenTextures(1, &_textureID);

				if (!_textureID)
				{
					throw ErrorHandling::Exception("Failed to create a texture ID for the albedo texture.");
				}
				else
				{
					glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);



					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, _rightTexture->Width(),  _rightTexture->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,  _rightTexture->TextureData());
					glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, _leftTexture->Width(),   _leftTexture->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,   _leftTexture->TextureData());

					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, _topTexture->Width(),    _topTexture->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,    _topTexture->TextureData());
					glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, _bottomTexture->Width(), _bottomTexture->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _bottomTexture->TextureData());

					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, _frontTexture->Width(),  _frontTexture->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,  _frontTexture->TextureData());
					glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, _backTexture->Width(),   _backTexture->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,   _backTexture->TextureData());
					


					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				}
			}

			return _textureID;
		}

		TextureCubeMap::~TextureCubeMap()
		{
			if (_textureID)
				glDeleteTextures(1, &_textureID);
		}

		std::shared_ptr<Texture>& TextureCubeMap::RightTexture() { return _rightTexture; }
		std::shared_ptr<Texture>& TextureCubeMap::LeftTexture() { return _leftTexture; }
		std::shared_ptr<Texture>& TextureCubeMap::TopTexture() { return _topTexture; }
		std::shared_ptr<Texture>& TextureCubeMap::BottomTexture() { return _bottomTexture; }
		std::shared_ptr<Texture>& TextureCubeMap::FrontTexture() { return _frontTexture; }
		std::shared_ptr<Texture>& TextureCubeMap::BackTexture() { return _backTexture; }
	}
}																	