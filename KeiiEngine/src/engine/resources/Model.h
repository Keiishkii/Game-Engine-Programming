#include <fbxsdk.h>
#include <map>
#include <vector>
#include <glm/vec3.hpp>

#include "Resource.h"

namespace Engine
{
	namespace Graphics { struct PolygonMaterialGroup; }
	namespace Graphics { struct VertexBuffer; }

	namespace ResourceManagement
	{
		struct ResourceManager;

		struct Model : Resource
		{
		private:
			std::shared_ptr<FbxManager*> _fbxManager;

			int _totalVertexCount;
			std::map<int, std::shared_ptr<Graphics::PolygonMaterialGroup>> _polygonMaterialGroups;
		public:


		private:
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);
			void ProbeNode(FbxNode* node, Graphics::VertexBuffer& positionBuffer, Graphics::VertexBuffer& normalBuffer);

			void UnpackMesh(FbxMesh* mesh, Graphics::VertexBuffer& positionBuffer, Graphics::VertexBuffer& normalBuffer);
			int GetPolygonMaterial(FbxMesh* mesh, int polygonIndex);
			void AddToPolygonMaterialGroup(FbxMesh* mesh, int polygonIndex, int materialID, Graphics::VertexBuffer& positionBuffer, Graphics::VertexBuffer& normalBuffer);

		public:
			virtual void Initialise(std::weak_ptr<ResourceManager> resourceManager) override;
			virtual void Load(std::string path) override;

			int TotalVertexCount();
			int TotalMaterialGroups();
			std::shared_ptr<Graphics::PolygonMaterialGroup> GetPolygonMaterialGroup(int materialIndex);
		};
	}
}