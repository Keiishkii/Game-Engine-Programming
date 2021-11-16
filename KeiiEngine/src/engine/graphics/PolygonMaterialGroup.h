#include <memory>

namespace Engine
{
	namespace ResourceManagement
	{
		struct Model;
	}

	namespace Graphics
	{
		struct VertexBuffer;
		struct VertexArray;
		struct PolygonMaterialGroup
		{
			friend ResourceManagement::Model;

		private:
			int _vertexCount = 0;

			std::shared_ptr<VertexArray> _materialGroupVertexArray;
		public:
			std::shared_ptr<VertexBuffer> vertexPositionBuffer;
			std::shared_ptr<VertexBuffer> vertexNormalBuffer;
			std::shared_ptr<VertexBuffer> textureUVBuffer;


		private:
		public:
			PolygonMaterialGroup();
			GLuint VertexArrayID();
			int VertexCount();
		};
	}
}