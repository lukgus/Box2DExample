#ifndef INPUT_MANAGER_HG
#define INPUT_MANAGER_HG

const int NUM_KEYS = 256;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void StartUp();
	void Shutdown();

	void Update();

	void PressKey(unsigned char key);
	void ReleaseKey(unsigned char key);

	void SetMousePosition(int x, int y);

	bool IsKeyPressed(unsigned char key);
	bool IsKeyHeldDown(unsigned char key);

private:
	bool mKeys[NUM_KEYS];
	bool mPrevKeys[NUM_KEYS];

	int mMouseX;
	int mMouseY;
};

#endif
