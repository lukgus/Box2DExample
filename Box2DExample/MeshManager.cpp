#include "MeshManager.h"

#include <assert.h>

#include <iostream>

#include "LOpenGL.h"
#include "vertex_defs.h"

/**
 * Default Constructor
 */
MeshManager::MeshManager()
	: mBaseFilePath("Assets/Models/")
{
	// do nothing.
}

/**
 * Default Destructor
 */
MeshManager::~MeshManager()
{
	// do nothing.
}

/**
 * StartUp
 * Act as constructor. Initialize everything.
 */
void MeshManager::StartUp()
{
}

/**
 * Shutdown
 * Act as destructor. Destroy everything.
 */
void MeshManager::Shutdown()
{
	// TODO: Delete everything
}

/**
 * SetBaseFilePath
 * Sets the base file path to the provided on
 * @param path - the new base file path
 */
void MeshManager::SetBaseFilePath(const std::string& path)
{
	this->mBaseFilePath = path;
}

/**
 * GetBaseFilePath
 * Returns the current base file path
 * @return - the current base file path
 */
const std::string& MeshManager::GetBaseFilePath()
{
	return this->mBaseFilePath;
}

/**
 * LoadMeshFromFile
 * Loads a mesh from the provided filename
 * @param filename - the name of the file to load from
 * @return int - 0 if successful, anything else if fail
 */
int MeshManager::LoadMeshFromFile(const std::string& filename)
{
	unsigned int flags = aiProcess_Triangulate;

	const aiScene* pScene = mImporter.ReadFile(mBaseFilePath + filename.c_str(), flags);

	if (pScene == 0)
	{
		return 1;
	}

	unsigned int numMeshes = pScene->mNumMeshes;

	for (unsigned int meshIndex = 0; meshIndex < numMeshes; meshIndex++)
	{
		LoadMesh(pScene->mMeshes[meshIndex]);
	}

	return 0;
}

void MeshManager::LoadMesh(aiMesh* mesh)
{
	std::string meshName(mesh->mName.data, mesh->mName.length);

	if (mNameToMeshId.find(meshName) != mNameToMeshId.end()) return;

	std::vector<aiVector3D> vec_vertices;
	std::vector<aiVector3D> vec_normals;

	unsigned int numVerticesInVertArray = mesh->mNumVertices;
	unsigned int numIndicesInIndexArray = mesh->mNumFaces * 3;

	sVertex_p4t4n4* pTempVertArray = new sVertex_p4t4n4[numIndicesInIndexArray * 2];
	GLuint* pIndexArrayLocal = new GLuint[numIndicesInIndexArray * 2];

	unsigned int numFaces = mesh->mNumFaces;
	unsigned int vertArrayIndex = 0;

	for (unsigned int faceIndex = 0; faceIndex != numFaces; faceIndex++)
	{
		aiFace currentFace = mesh->mFaces[faceIndex];

		unsigned int numIndices = currentFace.mNumIndices;
		for (unsigned int index = 0; index < numIndices; index++)
		{
			unsigned int currentIndex = currentFace.mIndices[index];

			pTempVertArray[vertArrayIndex].Pos.x = mesh->mVertices[currentIndex].x;
			pTempVertArray[vertArrayIndex].Pos.y = mesh->mVertices[currentIndex].y;
			pTempVertArray[vertArrayIndex].Pos.z = mesh->mVertices[currentIndex].z;
			pTempVertArray[vertArrayIndex].Pos.w = 1.0f;		// MUST BE 1.0f

			if (mesh->HasTextureCoords(0))
			{
				pTempVertArray[vertArrayIndex].TexUVx2.x = mesh->mTextureCoords[0][currentIndex].x;
				pTempVertArray[vertArrayIndex].TexUVx2.y = mesh->mTextureCoords[0][currentIndex].y;
			}
			else
			{
				pTempVertArray[vertArrayIndex].TexUVx2.x = 0.0f;
				pTempVertArray[vertArrayIndex].TexUVx2.y = 0.0f;
			}

			pTempVertArray[vertArrayIndex].TexUVx2.z = 0.0f;	// Free to use
			pTempVertArray[vertArrayIndex].TexUVx2.w = 0.0f;	// Free to use

			pTempVertArray[vertArrayIndex].Normal.x = mesh->mNormals[currentIndex].x;
			pTempVertArray[vertArrayIndex].Normal.y = mesh->mNormals[currentIndex].y;
			pTempVertArray[vertArrayIndex].Normal.z = mesh->mNormals[currentIndex].z;
			pTempVertArray[vertArrayIndex].Normal.w = 0.0f;		// MUST BE 0.0f

			pIndexArrayLocal[vertArrayIndex] = vertArrayIndex;

			vertArrayIndex++;
		}
	}

	Mesh* newMesh = new Mesh();

	glGenVertexArrays(1, &(newMesh->VAO));
	glBindVertexArray(newMesh->VAO);
	CheckGLError();

	glGenBuffers(1, &newMesh->VBO);
	glGenBuffers(1, &newMesh->EBO);
	CheckGLError();

	glBindBuffer(GL_ARRAY_BUFFER, newMesh->VBO);
	CheckGLError();

	unsigned int totalVertBufferSizeBYTES = numIndicesInIndexArray * sizeof(sVertex_p4t4n4); ;
	glBufferData(GL_ARRAY_BUFFER, totalVertBufferSizeBYTES, pTempVertArray, GL_STATIC_DRAW);
	CheckGLError();

	unsigned int bytesInOneVertex = sizeof(sVertex_p4t4n4);
	unsigned int byteOffsetToPosition = offsetof(sVertex_p4t4n4, Pos);
	unsigned int byteOffsetToUVCoords = offsetof(sVertex_p4t4n4, TexUVx2);
	unsigned int byteOffsetToNormal = offsetof(sVertex_p4t4n4, Normal);

	glEnableVertexAttribArray(0);		// Position
	glEnableVertexAttribArray(1);		// TexCoord
	glEnableVertexAttribArray(2);		// Normal

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, bytesInOneVertex, (GLvoid*)byteOffsetToPosition);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, bytesInOneVertex, (GLvoid*)byteOffsetToUVCoords);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, bytesInOneVertex, (GLvoid*)byteOffsetToNormal);
	CheckGLError();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newMesh->EBO);
	CheckGLError();

	unsigned int sizeOfIndexArrayInBytes = numIndicesInIndexArray * sizeof(GLuint);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndexArrayInBytes, pIndexArrayLocal, GL_STATIC_DRAW);
	CheckGLError();

	glBindVertexArray(0);
	CheckGLError();

	delete[] pTempVertArray;
	delete[] pIndexArrayLocal;

	newMesh->IndexId = mMeshes.size();
	newMesh->NumTriangles = mesh->mNumFaces;

	mNameToMeshId[meshName] = mMeshes.size();

	mMeshes.push_back(newMesh);
}

/**
 * GetMeshDataById
 * Retrieves the numTriangles and vbo of a mesh from the provided id
 * @param meshId - the id of the mesh
 * @param numTriangles - the number of triangles in the mesh
 * @param vbo - the vbo of the mesh
 * @return int - the 0 SUCCESS, anything else FAIL
 */
int MeshManager::GetMeshDataById(unsigned int meshId, unsigned int& numTriangles, GLuint& vbo)
{
	if (meshId >= mMeshes.size()) return 1;

	numTriangles = mMeshes[meshId]->NumTriangles;

	vbo = mMeshes[meshId]->VBO;

	return 0;
}

/**
* GetMeshIDByName
* Finds the id from the mesh map.
* @param name - the name of the mesh to find
* @param id - the id of the mesh to return
* @return TRUE if found, FALSE if does not exist
*/
int MeshManager::GetMeshIdByName(const std::string &name, unsigned int &id)
{
	std::map<std::string, unsigned int>::iterator it = mNameToMeshId.find(name);

	if (it == mNameToMeshId.end()) return 1;

	id = it->second;

	return 0;
}