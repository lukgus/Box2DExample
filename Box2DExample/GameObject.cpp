#include "GameObject.h"

GameObject::GameObject(void)
	: position(glm::vec3(0.0f, 0.0f, 0.0f))
	, scale(glm::vec3(1.0f, 1.0f, 1.0f))
	, orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
	, colour(glm::vec3(1.0f, 1.0f, 1.0f))
	, bIsActive(true)
	, MeshId(0)
	, PhysicsBody(0)
{
}

GameObject::~GameObject(void)
{
}

bool GameObject::IsActive(void)
{
	return bIsActive;
}

void GameObject::SetActive(bool show)
{
	bIsActive = show;
}
