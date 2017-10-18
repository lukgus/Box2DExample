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
	// TODO: Detect user input, and handle it
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
	GameObject* platform = new GameObject();
	platform->position.y = -10.0f;
	platform->scale.x *= 10.0f;
	platform->scale.z *= 10.0f;
	platform->MeshId = 1;
	mGameObjects.push_back(platform);

	GameObject* sphere = new GameObject();
	sphere->position.y = 10.0f;
	sphere->MeshId = 0;
	mGameObjects.push_back(sphere);

	return 0;
}