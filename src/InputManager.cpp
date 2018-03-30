#include "InputManager.h"
#include "GraphicsManager.h"

#include <GLFW/glfw3.h>

#include <iostream>

InputManager* InputManager::im = nullptr;

void glfw_key_callback(GLFWwindow* window, int key, int scancode, 
                                           int action, int mods)
{
  // the key in the array
  int keyIndex = -1;

  if(key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
  {
    // key is A-Z
    keyIndex = key - GLFW_KEY_A + KeyCodes::A;
  }
  else if(key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
  {
    // key is a digit
    keyIndex = key - GLFW_KEY_0 + KeyCodes::ZERO;
  }
  else
  {
    // key is something else
    switch(key)
    {
      // arrow keys
      case GLFW_KEY_UP:    keyIndex = KeyCodes::UP;    break;
      case GLFW_KEY_DOWN:  keyIndex = KeyCodes::DOWN;  break;
      case GLFW_KEY_LEFT:  keyIndex = KeyCodes::LEFT;  break;
      case GLFW_KEY_RIGHT: keyIndex = KeyCodes::RIGHT; break;

      // shift / ctrl
      case GLFW_KEY_LEFT_SHIFT:     keyIndex = KeyCodes::LSHIFT; break;
      case GLFW_KEY_RIGHT_SHIFT:    keyIndex = KeyCodes::RSHIFT; break;
      case GLFW_KEY_LEFT_CONTROL:   keyIndex = KeyCodes::LCTRL;  break;
      case GLFW_KEY_RIGHT_CONTROL:  keyIndex = KeyCodes::RCTRL;  break;

      // enter
      case GLFW_KEY_ENTER: keyIndex = KeyCodes::ENTER; break;
      case GLFW_KEY_SPACE: keyIndex = KeyCodes::SPACE; break;

      // International 1 and 2 (they're different for some reason)
      case GLFW_KEY_WORLD_1: keyIndex = KeyCodes::ONE; break;
      case GLFW_KEY_WORLD_2: keyIndex = KeyCodes::TWO; break;
    }
  }

  InputManager& im = InputManager::getReference();
  if(keyIndex != -1 && action == GLFW_PRESS)
  {
    im.keyPressed[keyIndex] = true;
  }
  if(keyIndex != -1 && action == GLFW_RELEASE)
  {
    im.keyPressed[keyIndex] = false;
  }
}

InputManager::InputManager()
{
  if(im == nullptr)
  {
    im = this;
  }

  keyPressed = new bool[KeyCodes::KeyCount];
  keyPressedPrev = new bool[KeyCodes::KeyCount];

  for(int i=0; i<KeyCodes::KeyCount; i++)
  {
    keyPressed[i] = false;
    keyPressedPrev[i] = false;
  }

  GraphicsManager& gm = GraphicsManager::getReference();
  glfwSetKeyCallback(gm.getWindow(), glfw_key_callback);
  glfwSetInputMode(gm.getWindow(), GLFW_STICKY_KEYS, 1);
}

InputManager::~InputManager()
{
  delete [] keyPressed;
  delete [] keyPressedPrev;
}

InputManager& InputManager::getReference()
{
  return *im;
}

void InputManager::pollInput()
{
  for(int i=0; i<KeyCodes::KeyCount; i++)
  {
    keyPressedPrev[i] = keyPressed[i];
  }
  glfwPollEvents(); 
}

bool InputManager::getKeyPressed(KeyCodes k) const
{
  return keyPressed[k]; 
}

bool InputManager::getKeyClicked(KeyCodes k) const
{
  return keyPressed[k] && !keyPressedPrev[k];
}

bool InputManager::getKeyReleased(KeyCodes k) const
{
  return !keyPressed[k] && keyPressedPrev[k];
}
