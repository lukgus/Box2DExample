#ifndef MESH_MANAGER_HG
#define MESH_MANAGER_HG

#include <map>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	void StartUp();
	void Shutdown();

	void SetBaseFilePath(const std::string& path);
	const std::string& GetBaseFilePath();

	int LoadMeshFromFile(const std::string& filename);
	int GetMeshDataById(unsigned int meshId, unsigned int& numTriangles, GLuint& vbo);
	int GetMeshIdByName(const std::string &name, unsigned int &id);

private:
	void LoadMesh(aiMesh* mesh);

	std::string mBaseFilePath;									// The path where the meshes are stored
	std::map<std::string, unsigned int> mNameToMeshId;			// Map mesh name to mesh id
	std::vector<Mesh*> mMeshes;								// vector of meshes by id
	
	Assimp::Importer mImporter;
};

typedef std::map<std::string, unsigned int> mesh_map;
typedef std::map<std::string, unsigned int>::iterator mesh_map_iterator;
typedef std::vector<Mesh*> mesh_vec;
typedef std::vector<Mesh*>::iterator mesh_vec_iterator;

#endif
