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
  ESCAPE,
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
    bool getCloseButtonPressed() const;

    double getMouseX() const;
    double getMouseY() const;

    void pollInput();

    static InputManager* im;
    static InputManager& getReference();

  private:
    bool* keyPressed;
    bool* keyPressedPrev;

    bool closeButtonPressed;

    double mouseX;
    double mouseY;

  friend void glfw_key_callback   (GLFWwindow*, int, int, int, int);
  friend void glfw_mouse_callback (GLFWwindow*, double, double);
  friend void glfw_resize_callback(GLFWwindow*, int, int);
  friend void glfw_close_callback (GLFWwindow*);
};
