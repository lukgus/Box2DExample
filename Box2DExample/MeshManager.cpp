#include "MeshManager.h"

#include <assert.h>

/**
 * Default Constructor
 */
MeshManager::MeshManager()
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
 * Loads a mesh from a file using assimp
 * @param filename - the file to load as mesh
 * @return int - the id of the mesh, or -1 if error
 */
int MeshManager::LoadMeshFromFile(const std::string& filename)
{
	// TODO: Load mesh from Assimp
}

/**
 * GetMeshByName
 * Use this to get a mesh from the name
 * @param name - the name of the mesh
 * @param mesh - the mesh that is found
 * @return - the id of the mesh, -1 if error
 */
int MeshManager::GetMeshByName(const std::string& name, cMesh **mesh)
{
	mesh_map_iterator itMeshMap = this->mMeshMap.find(name);

	if (itMeshMap == this->mMeshMap.end()) return -1;

	assert(this->mMeshes.size() < itMeshMap->second);

	mesh = &this->mMeshes[itMeshMap->second];
}

/**
 * GetMeshById
 * Finds a mesh from the provided id.
 * @param id - the id of the mesh
 * @param mesh - the mesh that is fond
 * @return - -1 if fail, 0 if success
 */
int MeshManager::GetMeshById(unsigned int id, cMesh **mesh)
{
	assert(this->mMeshes.size() < id);

	mesh = &this->mMeshes[id];
}