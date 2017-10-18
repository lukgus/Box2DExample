#ifndef MESH_MANAGER_HG
#define MESH_MANAGER_HG

#include <map>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class cMesh;
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
	int GetMeshByName(const std::string& name, cMesh **mesh);
	int GetMeshById(unsigned int id, cMesh **mesh);

private:
	std::string mBaseFilePath;									// The path where the meshes are stored
	std::map<std::string, unsigned int> mMeshMap;				// Map mesh name to mesh id
	std::vector<cMesh*> mMeshes;								// vector of meshes by id
	
	Assimp::Importer mImporter;
};

typedef std::map<std::string, unsigned int> mesh_map;
typedef std::map<std::string, unsigned int>::iterator mesh_map_iterator;
typedef std::vector<cMesh*> mesh_vec;
typedef std::vector<cMesh*>::iterator mesh_vec_iterator;

#endif
