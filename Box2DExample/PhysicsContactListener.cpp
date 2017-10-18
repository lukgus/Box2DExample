#include "PhysicsContactListener.h"

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

}

/**
 * EndContact
 * Called when a contact has ended between two 
 * physics bodies
 * @param contact - the two bodies ending a contact
 */
void PhysicsContactListener::EndContact(b2Contact* contact)
{

}