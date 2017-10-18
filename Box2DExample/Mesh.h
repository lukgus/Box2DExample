#ifndef MESH_HG
#define MESH_HG

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	std::string type;
};

class Mesh
{
public:
	Mesh(void);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	unsigned int IndexId;
	unsigned int NumTriangles;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

private:

	void SetupMesh(void);
};

#endif
