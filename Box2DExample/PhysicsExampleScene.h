#ifndef PHYSICS_EXAMPLE_SCENE_HG
#define PHYSICS_EXAMPLE_SCENE_HG

#include <vector>

#include "GameObject.h"

class PhysicsExampleScene
{
public:
	PhysicsExampleScene();
	~PhysicsExampleScene();

	bool Initialize();
	void Destroy();

	void Update(float dt);
	void Render();

private:
	int LoadMeshes();
	int LoadShaders();
	int LoadScene();

	void HandleUserInput();
	void HandleCollisions();

	std::vector<GameObject*> mGameObjects;
	GameObject* mRightWall;
	GameObject* mPlatform;
	GameObject* mSphere;
};

#endif
