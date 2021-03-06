#include <memory>

namespace Engine
{
	namespace ResourceManagement
	{
		struct Model;
		struct ShaderProgram;
	}

	namespace Graphics
	{
		struct VertexBuffer;
		struct VertexArray;

		/**	The PolygonMaterialGroup acts a collection for a given VAO and the material designated to it, each one is unique to an indevidual model and material.  	*/
		struct PolygonMaterialGroup
		{
			friend ResourceManagement::Model;

		private:
			int _vertexCount = 0;

			std::shared_ptr<VertexArray> _materialGroupVertexArray;

			std::shared_ptr<VertexBuffer> _vertexPositionBuffer;
			std::shared_ptr<VertexBuffer> _vertexNormalBuffer;
			std::shared_ptr<VertexBuffer> _textureUVBuffer;
		public:


		private:
		public:
			PolygonMaterialGroup();

			std::shared_ptr<VertexBuffer>& VertexPositionBuffer();
			std::shared_ptr<VertexBuffer>& VertexNormalBuffer();
			std::shared_ptr<VertexBuffer>& TextureUVBuffer();

			GLuint VertexArrayID(std::shared_ptr<ResourceManagement::ShaderProgram> shaderProgram);
			int VertexCount();
		};
	}
}