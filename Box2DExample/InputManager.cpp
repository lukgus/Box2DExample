#include "InputManager.h"

#include <string.h>

InputManager::InputManager()
{
}

InputManager::~InputManager()						  
{
}

void InputManager::StartUp()						  
{
	for (int i = 0; i < NUM_KEYS; i++)
	{
		mKeys[i] = false;
		mPrevKeys[i] = false;
	}
}

void InputManager::Shutdown()						  
{

}

/**
 * Update
 * Copies current keys to previous keys
 * Clears current keys
 */
void InputManager::Update()							  
{
	memcpy(mPrevKeys, mKeys, sizeof(bool) * NUM_KEYS);
}

void InputManager::PressKey(unsigned char key)		  
{
	mKeys[key] = true;
}

void InputManager::ReleaseKey(unsigned char key)	  
{
	mKeys[key] = false;
}

void InputManager::SetMousePosition(int x, int y)	  
{
	mMouseX = x;
	mMouseY = y;
}

bool InputManager::IsKeyPressed(unsigned char key)
{
	return mKeys[key] && !mPrevKeys[key];
}

bool InputManager::IsKeyHeldDown(unsigned char key)
{
	return mKeys[key] && mPrevKeys[key];
}
