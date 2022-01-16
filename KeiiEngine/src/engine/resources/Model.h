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

		/**	The Model is a type of resource, it is used to load 3D geometry and the data required to colour it.  	*/
		struct Model : Resource
		{
		private:
			std::weak_ptr<FbxManager*> _fbxManager;

			std::map<int, std::shared_ptr<Graphics::PolygonMaterialGroup>> _polygonMaterialGroups;
			std::map<int, std::shared_ptr<Material>> _materials;
			int _totalVertexCount = 0;
		public:


		private:
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);
			void LoadUVInformation(const FbxMesh* mesh, std::vector<glm::vec2>& textureUVs);

			void ProbeNode(FbxNode* node);

			void UnpackMesh(FbxMesh* mesh);
			int GetPolygonMaterial(FbxMesh* mesh, int polygonIndex);
			void AddToPolygonMaterialGroup(FbxMesh* mesh, int polygonIndex, int materialIndex, const std::vector<glm::vec2>& textureUVs);

			std::shared_ptr<FbxManager*> FBXManager();
		public:
			virtual void Initialise(const std::shared_ptr<ResourceManagement::ResourceManager>& resourceManager) override;
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath) override;

			void SetMaterial(int materialIndex, const std::shared_ptr<Material>& material);

			int TotalVertexCount();
			int TotalMaterialGroups();
			std::shared_ptr<Graphics::PolygonMaterialGroup> GetPolygonMaterialGroup(int materialIndex);
			std::shared_ptr<Material> GetMaterial(int materialIndex);
		};
	}
}