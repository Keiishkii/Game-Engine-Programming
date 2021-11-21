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

			_vertexPositionBuffer = std::make_shared<VertexBuffer>();
			_vertexNormalBuffer = std::make_shared<VertexBuffer>();
			_textureUVBuffer = std::make_shared<VertexBuffer>();
		}

		int PolygonMaterialGroup::VertexCount() { return _vertexCount; }
		std::shared_ptr<VertexBuffer>& PolygonMaterialGroup::VertexPositionBuffer() { return _vertexPositionBuffer; }
		std::shared_ptr<VertexBuffer>& PolygonMaterialGroup::VertexNormalBuffer() { return _vertexNormalBuffer; }
		std::shared_ptr<VertexBuffer>& PolygonMaterialGroup::TextureUVBuffer() { return _textureUVBuffer; }
		GLuint PolygonMaterialGroup::VertexArrayID() { return _materialGroupVertexArray->GetID(); }
	}
}