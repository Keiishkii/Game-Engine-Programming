#include <fbxsdk.h>
#include <map>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Resource.h"

namespace Engine
{
	namespace Graphics { struct PolygonMaterialGroup; }
	namespace Graphics { struct VertexBuffer; }

	namespace ResourceManagement
	{
		struct ResourceManager;
		struct Material;

		struct Model : Resource
		{
		private:
			std::shared_ptr<FbxManager*> _fbxManager;

			int _totalVertexCount;
			std::map<int, std::shared_ptr<Graphics::PolygonMaterialGroup>> _polygonMaterialGroups;
			std::map<int, std::shared_ptr<Material>> _materials;
		public:


		private:
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);
			void LoadUVInformation(FbxMesh* mesh, std::vector<glm::vec2>& textureUVs);

			void ProbeNode(FbxNode* node);

			void UnpackMesh(FbxMesh* mesh);
			int GetPolygonMaterial(FbxMesh* mesh, int polygonIndex);
			void AddToPolygonMaterialGroup(FbxMesh* mesh, int polygonIndex, int materialIndex, std::vector<glm::vec2>& textureUVs);
		public:
			virtual void Initialise(std::weak_ptr<ResourceManager> resourceManager) override;
			virtual void Load(std::string path) override;

			int TotalVertexCount();
			int TotalMaterialGroups();
			std::shared_ptr<Graphics::PolygonMaterialGroup> GetPolygonMaterialGroup(int materialIndex);
			std::shared_ptr<Material> GetMaterial(int materialIndex);
			void SetMaterial(int materialIndex, std::shared_ptr<Material> material);
		};
	}
}