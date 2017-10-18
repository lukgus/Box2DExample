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

	std::vector<GameObject*> mGameObjects;
};

#endif
