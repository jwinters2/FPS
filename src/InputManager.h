#pragma once

enum KeyCodes
{
  ZERO = 0,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ENTER,
  SPACE,
  LSHIFT,
  RSHIFT,
  LCTRL,
  RCTRL,
  KeyCount
};

class GLFWwindow;

class InputManager
{
  public:
    InputManager();
    ~InputManager();

    bool getKeyPressed(KeyCodes) const;
    bool getKeyClicked(KeyCodes) const;
    bool getKeyReleased(KeyCodes) const;

    int getMouseX() const;
    int getMouseY() const;

    void pollInput();

    static InputManager* im;
    static InputManager& getReference();

  private:
    bool* keyPressed;
    bool* keyPressedPrev;

    int mouseX;
    int mouxeY;

  friend void glfw_key_callback(GLFWwindow*, int, int, int, int);
};
