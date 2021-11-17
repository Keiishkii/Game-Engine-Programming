#include "VertexBuffer.h"
#include "VertexArray.h"
#include "PolygonMaterialGroup.h"

namespace Engine
{
	namespace Graphics
	{
		GLuint PolygonMaterialGroup::VertexArrayID()
		{
			return _materialGroupVertexArray->GetID();
		}

		PolygonMaterialGroup::PolygonMaterialGroup()
		{
			_vertexCount = 0;
			_materialGroupVertexArray = std::make_shared<VertexArray>();
		}

		int PolygonMaterialGroup::VertexCount() { return _vertexCount; }
	}
}