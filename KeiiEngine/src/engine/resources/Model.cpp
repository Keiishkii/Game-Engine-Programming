#include <iostream>
#include <glm/vec3.hpp>

#include "Model.h"
#include "engine/graphics/VertexArray.h"
#include "ResourceManager.h"
#include "engine/graphics/PolygonMaterialGroup.h"
#include "engine/graphics/VertexBuffer.h"
#include "engine/error-handling/Exception.h"


#undef  IOS_REF
#define IOS_REF (*(pManager->GetIOSettings()))

using Engine::ErrorHandling::Exception;

namespace Engine
{
    namespace ResourceManagement
    {
        void Model::Initialise(const std::shared_ptr<ResourceManager>& resourceManager)
        {
            _fbxManager = resourceManager->FBXManager();
        }

        void Model::Load(const std::string& path)
        {
            FbxScene* fbxScene = FbxScene::Create(*FBXManager(), "Import Scene");

            if (!fbxScene)
            {
                throw Exception("Failed to create the FBX Import scene");
            }
            else
            {
                FbxString localFilePath = FbxString(path.c_str());

                if (!LoadScene(*FBXManager(), fbxScene, localFilePath.Buffer()))
                {
                    throw Exception("Failed to import the FBX model into the scene.");
                }
                else
                {
					FbxNode* routeNode = fbxScene->GetRootNode();

					if (!routeNode)
					{
						throw Exception("The scene does not contain a root node.");
					}
					else
					{
						ProbeNode(routeNode);

						int count = 0;
						for (std::map<int, std::shared_ptr<Graphics::PolygonMaterialGroup>>::iterator it = _polygonMaterialGroups.begin(); it != _polygonMaterialGroups.end(); it++)
						{
							std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup = it->second;
							int materialGroupID = it->first;
							
							polygonMaterialGroup->_materialGroupVertexArray->SetBuffer("Vertex Position Buffer", polygonMaterialGroup->VertexPositionBuffer());
							polygonMaterialGroup->_materialGroupVertexArray->SetBuffer("Vertex Normal Buffer", polygonMaterialGroup->VertexNormalBuffer());
							polygonMaterialGroup->_materialGroupVertexArray->SetBuffer("Texture UV Buffer", polygonMaterialGroup->TextureUVBuffer());
							
							count += polygonMaterialGroup->VertexCount();
						}
					}
                }
            }
        }

		void Model::ProbeNode(FbxNode* node)
		{
			if (!((*node).GetNodeAttribute() == NULL))
			{
				int attributeCount = (*node).GetNodeAttributeCount();
				for (int i = 0; i < attributeCount; i++)
				{
					FbxNodeAttribute::EType lAttributeType;
					lAttributeType = ((*node).GetNodeAttributeByIndex(i)->GetAttributeType());

					switch (lAttributeType)
					{
						case FbxNodeAttribute::eSkeleton:
						{
							FbxSkeleton* skeleton = (FbxSkeleton*)node->GetNodeAttribute();
							if (skeleton != NULL)
							{

							}
						} break;
						case FbxNodeAttribute::eMesh:
						{
							FbxMesh* mesh = (*node).GetMesh();
							if (mesh != NULL)
							{
								UnpackMesh(mesh);
							}
						} break;
					}
				}
			}

			int children = (*node).GetChildCount();

			if (children > 0)
			{
				for (int i = 0; i < children; i++)
				{
					ProbeNode(((*node).GetChild(i)));
				}
			}
		}

		void Model::UnpackMesh(FbxMesh* mesh)
		{
			std::vector<glm::vec2> textureUVs;
			LoadUVInformation(mesh, textureUVs);

			int polygonCount = mesh->GetPolygonCount();
			for (int i = 0; i < polygonCount; i++)
			{
				int materialIndex = GetPolygonMaterial(mesh, i);

				AddToPolygonMaterialGroup(mesh, i, materialIndex, textureUVs);
			}
		}

		int Model::GetPolygonMaterial(FbxMesh* mesh, int polygonIndex)
		{
			int polygonMaterialIndex = -1;
			for (int j = 0; j < mesh->GetElementMaterialCount(); j++)
			{
				FbxGeometryElementMaterial* lMaterialElement = mesh->GetElementMaterial(j);
				FbxSurfaceMaterial* lMaterial = NULL;

				polygonMaterialIndex = lMaterialElement->GetIndexArray().GetAt(polygonIndex);
			}

			return polygonMaterialIndex;
		}

		void Model::AddToPolygonMaterialGroup(FbxMesh* mesh, int polygonIndex, int materialIndex, const std::vector<glm::vec2>& textureUVs)
		{
			int* vertciesArray = mesh->GetPolygonVertices();
			for (int v = 0; v < mesh->GetPolygonSize(polygonIndex); v++)
			{
				int vertexIndex = v + (polygonIndex * mesh->GetPolygonSize(polygonIndex));

				std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup = GetPolygonMaterialGroup(materialIndex);

				FbxVector4 normal, controlPoint = mesh->GetControlPointAt(vertciesArray[vertexIndex]);
				mesh->GetPolygonVertexNormal(polygonIndex, v, normal);

				glm::vec3 vertexPosition(controlPoint.mData[0], controlPoint.mData[1], controlPoint.mData[2]);
				polygonMaterialGroup->VertexPositionBuffer()->Add(vertexPosition);

				glm::vec3 vertexNormal(normal.mData[0], normal.mData[1], normal.mData[2]);
				polygonMaterialGroup->VertexNormalBuffer()->Add(vertexNormal);

				polygonMaterialGroup->TextureUVBuffer()->Add(textureUVs[vertexIndex]);

				_totalVertexCount++;
				polygonMaterialGroup->_vertexCount++;
			}
		}

		std::shared_ptr<Graphics::PolygonMaterialGroup> Model::GetPolygonMaterialGroup(int materialIndex)
		{
			std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup = NULL;
			if (_polygonMaterialGroups.count(materialIndex))
			{
				polygonMaterialGroup = _polygonMaterialGroups[materialIndex];
			}
			else
			{
				polygonMaterialGroup = std::make_shared<Graphics::PolygonMaterialGroup>();
				_polygonMaterialGroups.insert(std::pair<int, std::shared_ptr<Graphics::PolygonMaterialGroup>>(materialIndex, polygonMaterialGroup));
			}

			return polygonMaterialGroup;
		}

		std::shared_ptr<Material> Model::GetMaterial(int materialIndex)
		{
			std::shared_ptr<Material> material;
			if (_materials.count(materialIndex))
			{
				material = _materials[materialIndex];
			}

			return material;
		}

		void Model::SetMaterial(int materialIndex, const std::shared_ptr<Material>& material)
		{
			if (_materials.count(materialIndex))
			{
				_materials[materialIndex] = material;
			}
			else
			{
				_materials.insert(std::pair<int, std::shared_ptr<Material>>(materialIndex, material));
			}
		}
				 
		void Model::LoadUVInformation(const FbxMesh* mesh, std::vector<glm::vec2>& textureUVs)
		{
			//get all UV set names
			FbxStringList lUVSetNameList;
			mesh->GetUVSetNames(lUVSetNameList);

			//iterating over all uv sets
			for (int lUVSetIndex = 0; lUVSetIndex < lUVSetNameList.GetCount(); lUVSetIndex++)
			{
				//get lUVSetIndex-th uv set
				const char* lUVSetName = lUVSetNameList.GetStringAt(lUVSetIndex);
				const FbxGeometryElementUV* lUVElement = mesh->GetElementUV(lUVSetName);

				if (!lUVElement)
					continue;

				// only support mapping mode eByPolygonVertex and eByControlPoint
				if (lUVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
					lUVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
					return;

				//index array, where holds the index referenced to the uv data
				const bool lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
				const int lIndexCount = (lUseIndex) ? lUVElement->GetIndexArray().GetCount() : 0;

				//iterating through the data by polygon
				const int lPolyCount = mesh->GetPolygonCount();

				if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
				{
					for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
					{
						// build the max index array that we need to pass into MakePoly
						const int lPolySize = mesh->GetPolygonSize(lPolyIndex);
						for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
						{
							FbxVector2 lUVValue;

							//get the index of the current vertex in control points array
							int lPolyVertIndex = mesh->GetPolygonVertex(lPolyIndex, lVertIndex);

							//the UV index depends on the reference mode
							int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyVertIndex) : lPolyVertIndex;

							lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

							//User TODO:
							//Print out the value of UV(lUVValue) or log it to a file
						}
					}
				}
				else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					int lPolyIndexCounter = 0;
					for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
					{
						// build the max index array that we need to pass into MakePoly
						const int lPolySize = mesh->GetPolygonSize(lPolyIndex);
						for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
						{
							if (lPolyIndexCounter < lIndexCount)
							{
								FbxVector2 lUVValue;

								//the UV index depends on the reference mode
								int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyIndexCounter) : lPolyIndexCounter;

								lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

								glm::vec2 vertexPosition(lUVValue.mData[0], lUVValue.mData[1]);
								textureUVs.push_back(vertexPosition);

								lPolyIndexCounter++;
							}
						}
					}
				}
			}
		}

        // Import function from the FBXSDK sample code
        bool Model::LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename)
		{
			int lFileMajor, lFileMinor, lFileRevision;
			int lSDKMajor, lSDKMinor, lSDKRevision;
			//int lFileFormat = -1;
			int i, lAnimStackCount;
			bool lStatus;
			char lPassword[1024];

			// Get the file version number generate by the FBX SDK.
			FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

			// Create an importer.
			FbxImporter* lImporter = FbxImporter::Create(pManager, "");

			// Initialize the importer by providing a filename.
			const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());
			lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

			if (!lImportStatus)
			{
				FbxString error = lImporter->GetStatus().GetErrorString();
				FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
				FBXSDK_printf("Error returned: %s\n\n", error.Buffer());

				if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
				{
					FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
					FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
				}

				return false;
			}

			//FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

			if (lImporter->IsFBX())
			{
				//FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

				// From this point, it is possible to access animation stack information without
				// the expense of loading the entire file.

				//FBXSDK_printf("Animation Stack Information\n");

				lAnimStackCount = lImporter->GetAnimStackCount();

				//FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
				//FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
				//FBXSDK_printf("\n");

				for (i = 0; i < lAnimStackCount; i++)
				{
					FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

					//FBXSDK_printf("    Animation Stack %d\n", i);
					//FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
					//FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

					// Change the value of the import name if the animation stack should be imported 
					// under a different name.
					//FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

					// Set the value of the import state to false if the animation stack should be not
					// be imported. 
					//FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
					//FBXSDK_printf("\n");
				}

				// Set the import states. By default, the import states are always set to 
				// true. The code below shows how to change these states.
				IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
				IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
				IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
				IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
				IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
				IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
				IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
			}

			// Import the scene.
			lStatus = lImporter->Import(pScene);

			if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
			{
				FBXSDK_printf("Please enter password: ");

				lPassword[0] = '\0';

				FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
					scanf("%s", lPassword);
				FBXSDK_CRT_SECURE_NO_WARNING_END

					FbxString lString(lPassword);

				IOS_REF.SetStringProp(IMP_FBX_PASSWORD, lString);
				IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

				lStatus = lImporter->Import(pScene);

				if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
				{
					FBXSDK_printf("\nPassword is wrong, import aborted.\n");
				}
			}

			// Destroy the importer.
			lImporter->Destroy();

			return lStatus;
		}

		int Model::TotalVertexCount() { return _totalVertexCount; }
		int Model::TotalMaterialGroups() { return _polygonMaterialGroups.size(); }
		std::shared_ptr<FbxManager*> Model::FBXManager() { return _fbxManager.lock(); }
    }
}