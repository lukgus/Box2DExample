#ifndef PHYSICS_CONTACT_LISTENER_HG
#define PHYSICS_CONTACT_LISTENER_HG

#include <Box2D\Box2D.h>

class PhysicsContactListener : public b2ContactListener
{
public:
	PhysicsContactListener();
	~PhysicsContactListener();

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
};

#endif
