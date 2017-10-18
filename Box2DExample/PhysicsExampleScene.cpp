#include "PhysicsExampleScene.h"

#include "DebugLogger.h"

#include "LManagers.h"

/**
 * Default constructor
 */
PhysicsExampleScene::PhysicsExampleScene()
{
}

/**
 * Destructor
 */
PhysicsExampleScene::~PhysicsExampleScene()
{
}

/**
 * Initialize
 * Called to initialize the scene
 * @return bool - TRUE if successful, FALSE otherwise
 */
bool PhysicsExampleScene::Initialize()
{
	DebugLogger::LogMessage("Initializing PhysicsExampleScene...");

	DebugLogger::LogMessage("Loading Meshes...");
	if (LoadMeshes() != 0)
	{
		DebugLogger::LogError("Failed to load meshes!");
		return false;
	}

	DebugLogger::LogMessage("Loading Shaders...");
	if (LoadShaders() != 0)
	{
		DebugLogger::LogError("Failed to load shaders!");
		return false;
	}

	DebugLogger::LogMessage("Creating Scene...");
	if (LoadScene() != 0)
	{
		DebugLogger::LogError("Failed to load scene!");
		return false;
	}

	DebugLogger::LogMessage("Initialization successful!");
	return true;
}

/**
 * Destroy
 * Destroys the scene, deletes everything, and sets up
 * for closing.
 */
void PhysicsExampleScene::Destroy()
{
}

/**
 * Update
 * Calls update on everything that needs to be updated
 * at the scene level.
 * @param dt - the delta time in ms
 */
void PhysicsExampleScene::Update(float dt)
{
	HandleUserInput();

	HandleCollisions();

	mRightWall->PhysicsBody->SetAngularVelocity(1.0f);

	GameObject* currentGo;
	b2Vec2 physicsPosition;
	float angle;
	for (unsigned int goId = 0; goId < mGameObjects.size(); goId++)
	{
		currentGo = mGameObjects[goId];
		if (currentGo->PhysicsBody != 0)
		{
			physicsPosition = currentGo->PhysicsBody->GetPosition();
			currentGo->position.x = physicsPosition.x;
			currentGo->position.y = physicsPosition.y;

			angle = currentGo->PhysicsBody->GetAngle();
			// Convert the angle retrieved as the z euler angle.
			// Use euler angles to rotate the object.
			currentGo->orientation = glm::quat(glm::vec3(0.0f, 0.0f, angle));
		}
	}
}

/**
 * Render
 * Renders the scene
 */
void PhysicsExampleScene::Render()
{
	// Call Render
	gRenderManager.RenderGameObjects(mGameObjects);

	int breakpoint = 0;
}

/**
 * LoadMeshes
 * Loads meshes into the mesh manager
 * @return int - 0 if success, anything else if fail
 */
int PhysicsExampleScene::LoadMeshes()
{
	DebugLogger::LogSubMessage("loading SphereMesh...");
	if (gMeshManager.LoadMeshFromFile("Sphere.fbx") != 0)
	{
		DebugLogger::LogError("Failed to load SphereMesh...");
		return 1;
	}

	DebugLogger::LogSubMessage("loading PlatformMesh...");
	if (gMeshManager.LoadMeshFromFile("Platform.fbx") != 0)
	{
		DebugLogger::LogError("Failed to load PlatformMesh...");
		return 1;
	}

	return 0;
}

/**
 * LoadShaders
 * Loads shaders into the shader manager
 * @return int - 0 if success, anything else if fail
 */
int PhysicsExampleScene::LoadShaders()
{
	DebugLogger::LogSubMessage("Loading SimpleShader...");
	if (gShaderManager.CreateShaderProgramFromSourceFiles("SimpleShader", "SimpleShader.vertex.glsl", "SimpleShader.fragment.glsl") == false)
	{
		DebugLogger::LogError("Failed to load SimpleShader!");
		return 1;
	}

	return 0;
}

/**
 * LoadScene
 * Creates all game objects for the scene
 * @return int - 0 if success, anything else if fail
 */
int PhysicsExampleScene::LoadScene()
{
	mPlatform = new GameObject();
	mPlatform->name = "Platform";
	mPlatform->position.y = -10.0f;
	mPlatform->scale.x *= 10.0f;
	mPlatform->scale.z *= 10.0f;
	mPlatform->MeshId = 1;
	mGameObjects.push_back(mPlatform);

	b2BodyDef platformBodyDef;
	platformBodyDef.position.Set(mPlatform->position.x, mPlatform->position.y);
	mPlatform->PhysicsBody = gPhysicsManager.CreateBody(&platformBodyDef);
	mPlatform->PhysicsBody->SetUserData(mPlatform);				// This sets the platform game object
																// as an accessible value so we can
																// use it in the physics collision listener

	b2PolygonShape platformShape;
	platformShape.SetAsBox(mPlatform->scale.x, mPlatform->scale.y);
	mPlatform->PhysicsBody->CreateFixture(&platformShape, 0.0f);


	// Create a wall on the right side
	mRightWall = new GameObject();
	mRightWall->name = "RightWall";
	mRightWall->position.y = 0.0f;
	mRightWall->position.x = 10.0f;
	mRightWall->scale.y *= 20.0f;
	mRightWall->scale.z *= 10.0f;
	mRightWall->MeshId = 1;
	mGameObjects.push_back(mRightWall);

	b2BodyDef rightWallBodyDef;
	rightWallBodyDef.type = b2_kinematicBody;					// This allows the object to be given forces/impulses
	rightWallBodyDef.position.Set(mRightWall->position.x, mRightWall->position.y);
	mRightWall->PhysicsBody = gPhysicsManager.CreateBody(&rightWallBodyDef);
	mRightWall->PhysicsBody->SetUserData(mRightWall);				

	b2PolygonShape rightWallShape;
	rightWallShape.SetAsBox(mRightWall->scale.x, mRightWall->scale.y);
	mRightWall->PhysicsBody->CreateFixture(&rightWallShape, 0.0f);



	mSphere = new GameObject();
	mSphere->name = "Sphere";
	mSphere->position.y = 10.0f;
	mSphere->MeshId = 0;
	mGameObjects.push_back(mSphere);

	b2BodyDef sphereBodyDef;
	sphereBodyDef.position.Set(mSphere->position.x, mSphere->position.y);
	sphereBodyDef.type = b2_dynamicBody;						// This allows the object to move
	mSphere->PhysicsBody = gPhysicsManager.CreateBody(&sphereBodyDef);
	mSphere->PhysicsBody->SetUserData(mSphere);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0.0f, 0.0f);							// See how the midpoint at 0, 0 works.
	circleShape.m_radius = mSphere->scale.x;

	mSphere->PhysicsBody->CreateFixture(&circleShape, 1.0f);

	return 0;
}

/**
 * HandleUserInput
 * Handles user input to control the sphere
 * by adding forces to it in a direction
 */
void PhysicsExampleScene::HandleUserInput()
{
	b2Vec2 inputForce(0.0f, 0.0f);

	if (gInputManager.IsKeyHeldDown('a') || gInputManager.IsKeyHeldDown('A'))
	{
		inputForce.x = -10.0f;
	}
	if (gInputManager.IsKeyHeldDown('d') || gInputManager.IsKeyHeldDown('D'))
	{
		inputForce.x = 10.0f;
	}

	mSphere->PhysicsBody->ApplyForceToCenter(inputForce, true);
}

/**
 * HandleCollisions
 * Checks the collision listener for collisions,
 * and handles the collisions.
 */
void PhysicsExampleScene::HandleCollisions()
{
	// TODO: Fill out
}