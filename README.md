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

## Installation
Just drop sdlw.h in your source files and `#include "sdlw.h"` in your main cpp (for example).

## Requirements
You'll need [SDL2](https://www.libsdl.org/download-2.0.php) linked to your project. There's plenty of tutorials online on how to do that. 

But here's a quick one if you use Visual Studio:
1. Download a development package from [here](https://www.libsdl.org/download-2.0.php);
2. Make a folder in your project like `MyProject\deps\sdl` for example;
3. Put include and libs from the pack you downloaded into that folder;
4. In Visual Studio, open project properties - right click in Solution Explorer on your project (should have ++ icon in vs2019) and select Properties;
5. In `C/C++ > General > Additional Include Directories` add your include folder, which is in my example `$(ProjectDir)deps\sdl\include;` (don't forget to delimit with `;`);
6. In `Linker > General > Additional Library Directories` add `$(ProjectDir)deps\sdl\lib\x64;`
7. In `Linker > Input > Additional Dependencies` add `SDL2.lib;SDL2main.lib;`
8. Build your project. If you run it, it SHOULD tell you that SDL2.dll is missing;
9. Now take SDL2.dll from your package and put it in your binary folder. By default that should be ProjectFolder\Debug or ProjectFolder\Release (you'll need to add to both if you switch configurations);
10. Now when you run it, it should work!
