#ifndef GAMEOBJECT_HG
#define GAMEOBJECT_HG

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <Box2D\Box2D.h>

#include "LOpenGL.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	bool IsActive(void);
	void SetActive(bool show);

	glm::vec3 position;
	glm::vec3 scale;
	glm::quat orientation;

	glm::vec3 colour;

	std::string tag;

	unsigned int MeshId;

	b2Body* PhysicsBody;

private:
	bool bIsActive;

};

#endif
