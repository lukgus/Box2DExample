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

	b2Body* CreateBody(const b2BodyDef* def);
	void DestroyBody(b2Body* body);

private:
	b2Vec2 mGravity;
	b2World* mPhysicsWorld;

	int32 mVelocityIterations;
	int32 mPositionIterations;
};

#endif
