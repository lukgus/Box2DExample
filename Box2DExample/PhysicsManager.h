#ifndef PHYSICS_MANAGER_HG
#define PHYSICS_MANAGER_HG

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void StartUp();
	void Shutdown();

	void Update(float dt);

private:

};

#endif
