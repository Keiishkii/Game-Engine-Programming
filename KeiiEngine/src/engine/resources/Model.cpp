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


namespace Engine
{
    namespace ResourceManagement
    {
		int Model::TotalVertexCount() { return _totalVertexCount; }
		int Model::TotalMaterialGroups() { return _polygonMaterialGroups.size(); }

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

        void Model::Initialise(std::weak_ptr<ResourceManager> resourceManager)
        {
            Resource::Initialise(resourceManager);

            _fbxManager = _resourceManager.lock()->FBXManager();
        }

        void Model::Load(std::string path)
        {
            FbxScene* fbxScene = FbxScene::Create(*_fbxManager, "Import Scene");

            if (!fbxScene)
            {
                throw ErrorHandling::Exception("Failed to create the FBX Import scene");
            }
            else
            {
                FbxString localFilePath = FbxString(path.c_str());

                if (!LoadScene(*_fbxManager, fbxScene, localFilePath.Buffer()))
                {
                    throw ErrorHandling::Exception("Failed to import the FBX model into the scene.");
                }
                else
                {
					FbxNode* routeNode = fbxScene->GetRootNode();

					if (!routeNode)
					{
						throw ErrorHandling::Exception("The scene does not contain a root node.");
					}
					else
					{
						Graphics::VertexBuffer positionBuffer;
						Graphics::VertexBuffer normalBuffer;
						//textureUVBuffer = std::make_shared<VertexBuffer>();

						ProbeNode(routeNode, positionBuffer, normalBuffer);

						int count = 0;
						for (std::map<int, std::shared_ptr<Graphics::PolygonMaterialGroup>>::iterator it = _polygonMaterialGroups.begin(); it != _polygonMaterialGroups.end(); it++)
						{
							std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup = it->second;
							int materialGroupID = it->first;

							std::cout << "Adding Material Group: " << materialGroupID << " to its VAO" << std::endl;

							polygonMaterialGroup->_materialGroupVertexArray->SetVertexCount(polygonMaterialGroup->VertexCount());

							polygonMaterialGroup->_materialGroupVertexArray->SetBuffer("Vertex Position Buffer", positionBuffer);
							//polygonMaterialGroup->_materialGroupVertexArray->SetBuffer("Vertex Normal Buffer", polygonMaterialGroup->vertexNormalBuffer);
							//polygonMaterialGroup->_materialGroupVertexArray->SetBuffer("Texture UV Buffer", polygonMaterialGroup->textureUVBuffer);


							std::cout << "Material Group Polygon Count: " << polygonMaterialGroup->VertexCount() << std::endl;
							count += polygonMaterialGroup->VertexCount();
						}

						std::cout << count << ", " << _totalVertexCount << std::endl;
					}
                }
            }
        }

		void Model::ProbeNode(FbxNode* node, Graphics::VertexBuffer& positionBuffer, Graphics::VertexBuffer& normalBuffer)
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
								UnpackMesh(mesh, positionBuffer, normalBuffer);
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
					ProbeNode(((*node).GetChild(i)), positionBuffer, normalBuffer);
				}
			}
		}

		void Model::UnpackMesh(FbxMesh* mesh, Graphics::VertexBuffer& positionBuffer, Graphics::VertexBuffer& normalBuffer)
		{
			int polygonCount = mesh->GetPolygonCount();
			for (int i = 0; i < polygonCount; i++)
			{
				int materialIndex = GetPolygonMaterial(mesh, i);

				AddToPolygonMaterialGroup(mesh, i, materialIndex, positionBuffer, normalBuffer);
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

		void Model::AddToPolygonMaterialGroup(FbxMesh* mesh, int polygonIndex, int materialIndex, Graphics::VertexBuffer& positionBuffer, Graphics::VertexBuffer& normalBuffer)
		{
			int* vertciesArray = mesh->GetPolygonVertices();
			for (int v = 0; v < mesh->GetPolygonSize(polygonIndex); v++)
			{
				std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup = GetPolygonMaterialGroup(materialIndex);

				FbxVector4 normal, controlPoint = mesh->GetControlPointAt(vertciesArray[v + (polygonIndex * mesh->GetPolygonSize(polygonIndex))]);
				mesh->GetPolygonVertexNormal(polygonIndex, v, normal);

				glm::vec3 vertexPosition(controlPoint.mData[0], controlPoint.mData[1], controlPoint.mData[2]);
				positionBuffer.Add(vertexPosition);

				glm::vec3 vertexNormal(normal.mData[0], normal.mData[1], normal.mData[2]);
				normalBuffer.Add(vertexNormal);

				_totalVertexCount++;
				polygonMaterialGroup->_vertexCount++;
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
    }
}