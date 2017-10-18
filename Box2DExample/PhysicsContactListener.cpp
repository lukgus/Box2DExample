#include "PhysicsContactListener.h"

#include "DebugLogger.h"

#include "GameObject.h"

PhysicsContactListener::PhysicsContactListener()
{
}

PhysicsContactListener::~PhysicsContactListener()
{
}

/**
 * BeginContact
 * Called when there is a new contact between two
 * physics bodies
 * @param contact - the two bodies contacting (Fixtures)
 */
void PhysicsContactListener::BeginContact(b2Contact* contact)
{
	DebugLogger::LogNotification("PhysicsContactListener", "Start Physics Contact!");
	GameObject* goA = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* goB = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	goA->BeginContact(goB);
	goB->BeginContact(goA);
}

/**
 * EndContact
 * Called when a contact has ended between two 
 * physics bodies
 * @param contact - the two bodies ending a contact
 */
void PhysicsContactListener::EndContact(b2Contact* contact)
{
	DebugLogger::LogNotification("PhysicsContactListener", "End Physics Contact!");
	GameObject* goA = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* goB = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	goA->EndContact(goB);
	goB->EndContact(goA);
}