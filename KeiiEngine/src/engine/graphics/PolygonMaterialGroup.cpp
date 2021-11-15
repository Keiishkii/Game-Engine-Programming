#include "VertexBuffer.h"
#include "PolygonMaterialGroup.h"

namespace Engine
{
	namespace Graphics
	{
		PolygonMaterialGroup::PolygonMaterialGroup()
		{
			_vertexCount = 0;

			vertexPositions = std::make_shared<VertexBuffer>();
			vertexNormals = std::make_shared<VertexBuffer>();
			textureUVs = std::make_shared<VertexBuffer>();
		}

		int PolygonMaterialGroup::VertexCount() { return _vertexCount; }
	}
}