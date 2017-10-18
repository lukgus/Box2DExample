#ifndef PHYSICS_MANAGER_HG
#define PHYSICS_MANAGER_HG

#include <Box2D\Box2D.h>

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void StartUp();
	void Shutdown();

	void Update(float dt);

	void SetGravity(b2Vec2 gravity);

private:
	b2Vec2 mGravity;
	b2World* mPhysicsWorld;

	int32 mVelocityIterations;
	int32 mPositionIterations;
};

#endif
