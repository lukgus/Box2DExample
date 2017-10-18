#include "PhysicsManager.h"

#include "DebugLogger.h"

/**
 * Default constructor
 */
PhysicsManager::PhysicsManager()
	: mGravity(b2Vec2(0.0f, -10.0f))
	, mVelocityIterations(6)
	, mPositionIterations(2)
{
}

/**
 * Destructor
 */
PhysicsManager::~PhysicsManager()					  
{
}

/**
 * StartUp
 * Initialize everything
 * Acts as constructor
 */
void PhysicsManager::StartUp()						  
{
	DebugLogger::LogMessage("PhysicsManager.StartUp()");
	DebugLogger::LogSubMessage("Creating Physics World...");

	mPhysicsWorld = new b2World(mGravity);
}

/**
 * Shutdown
 * Acts as destructor
 * Delete everything
 */
void PhysicsManager::Shutdown()						  
{
	DebugLogger::LogMessage("PhysicsManager.Shutdown()");
}

/**
 * Update
 * Calls step on the physics world
 * @param dt - the elapsed time since last update.
 */
void PhysicsManager::Update(float dt)				  
{
	mPhysicsWorld->Step(dt, mVelocityIterations, mPositionIterations);
}

/**
 * SetGravity
 * Sets the gravity for the physics world
 * @param gravity - the gravity
 */
void PhysicsManager::SetGravity(b2Vec2 gravity)
{
	mGravity = gravity;
}

/**
 * CreateBody
 * Creates a Box2D body from the provided def
 * @param def - the Box2D body defs
 * @return b2Body - the created body
 */
b2Body* PhysicsManager::CreateBody(const b2BodyDef* def)
{
	return mPhysicsWorld->CreateBody(def);
}

/**
 * DestroyBody
 * Destroys the provided body from teh world
 * @param body - the body to destroy
 */
void PhysicsManager::DestroyBody(b2Body* body)
{
	mPhysicsWorld->DestroyBody(body);
}