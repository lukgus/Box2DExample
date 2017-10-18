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
