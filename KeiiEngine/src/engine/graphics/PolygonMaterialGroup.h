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
		struct PolygonMaterialGroup
		{
			friend ResourceManagement::Model;

		private:
			int _vertexCount = 0;
		public:
			std::shared_ptr<VertexBuffer> vertexPositions;
			std::shared_ptr<VertexBuffer> vertexNormals;
			std::shared_ptr<VertexBuffer> textureUVs;


		private:
		public:
			PolygonMaterialGroup();
			int VertexCount();
		};
	}
}