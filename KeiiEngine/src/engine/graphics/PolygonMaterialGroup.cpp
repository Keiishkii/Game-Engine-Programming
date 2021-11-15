#include "VertexBuffer.h"
#include "VertexArray.h"
#include "PolygonMaterialGroup.h"

namespace Engine
{
	namespace Graphics
	{
		PolygonMaterialGroup::PolygonMaterialGroup()
		{
			_vertexCount = 0;
			_materialGroupVertexArray = std::make_shared<VertexArray>();

			vertexPositionBuffer = std::make_shared<VertexBuffer>();
			vertexNormalBuffer = std::make_shared<VertexBuffer>();
			textureUVBuffer = std::make_shared<VertexBuffer>();
		}

		int PolygonMaterialGroup::VertexCount() { return _vertexCount; }
	}
}