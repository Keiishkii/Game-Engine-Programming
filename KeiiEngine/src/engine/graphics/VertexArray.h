#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <map>
#include <string>
#include <memory>

namespace Engine
{
	namespace Graphics
	{
		struct VertexBuffer;
		struct VertexArray
		{
		private:
			bool dirty = false;

			int vertexCount = 0;
			GLuint id = 0;

			std::shared_ptr<VertexBuffer> vertexPositions;
			std::shared_ptr<VertexBuffer> textureUVs;
			std::shared_ptr<VertexBuffer> vertexNormals;
			std::shared_ptr<VertexBuffer> vertexTangents;
			std::shared_ptr<VertexBuffer> vertexBitangents;
		public:


		private:
		public:
			VertexArray();

			GLuint getID();
			int getVertexCount() { return vertexCount; }
			std::shared_ptr<VertexBuffer> getVertexList() { return vertexPositions; }
			std::shared_ptr<VertexBuffer> getTextureUVList() { return textureUVs; }

			void setVertexCount(int _vertexCount);
			void setBuffer(std::string _buffer, std::shared_ptr<VertexBuffer> _content);
		};
	}
}