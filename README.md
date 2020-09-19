A little C++ wrapper for SDL2.

For easier start-up, and to get you going in seconds!

This wrapper is not feature-full, it's MEANT to be changed by YOU and you should add new features as you need them. Actually, it's the best if you used it as an example to learn how to start with SDL and/or make your own wrapper!

## Some features
* Handles SDL startup and destruction in RAII way. Just create the object and .Init() it;
* Wraps a few SDL functions for more logical access:
    * Detects keys with Unity-like GetKey(), GetKeyDown() and GetKeyUp();
    * SetColor01() can provide r, g, b in 0-1 floats;
    * DrawRect(), DrawLine(), DrawRay();
    * Query mouse position with mouseX() and mouseY();

## Example
See example.cpp on how to use it to draw a rectangle

## Requirements
You'll need SDL2 installed.


