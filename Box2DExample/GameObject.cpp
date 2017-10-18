#include "GameObject.h"

#include "DebugLogger.h"

GameObject::GameObject(void)
	: position(glm::vec3(0.0f, 0.0f, 0.0f))
	, scale(glm::vec3(1.0f, 1.0f, 1.0f))
	, orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
	, colour(glm::vec3(1.0f, 1.0f, 1.0f))
	, bIsActive(true)
	, MeshId(0)
	, PhysicsBody(0)
	, name("noname")
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

void GameObject::BeginContact(GameObject* other)
{
	DebugLogger::LogNotification(name, "Contact started with ", other->name);
}

void GameObject::EndContact(GameObject* other)
{
	DebugLogger::LogNotification(name, "Contact ended with ", other->name);
}