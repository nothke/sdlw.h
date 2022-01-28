A little C++ wrapper for SDL2.

To get you going in seconds!

This wrapper is not feature-full, this is just a helper to simplify a few important calls. For anything that is not included in the wrapper you will still need to call `SDL_` functions. Actually, it's the best if you used it as an example to learn how to start with SDL and/or make your own wrapper!

## Some features
* Handles SDL startup and destruction in RAII way. Just create the object and .Init() it;
* Only one function to run a loop: `while(IsRunning()) {}` !!!
* Detects keys with Unity-like GetKey(), GetKeyDown() and GetKeyUp();
* Query mouse position with mouseX() and mouseY();
* SetColor01() can provide r, g, b in 0-1 floats;
* DrawRect(), DrawLine(), DrawRay();

## Example
Simple example:

``` cpp
#include "sdlw.h"

int main(int argc, char* argv[]) {

	SDLW sdlw;
	sdlw.Init("My SDLW App", 800, 600);

	while (sdlw.IsRunning())
	{
		while (sdlw.PopEvent())
		{
			// Put your event-based input here
			if (sdlw.GetKeyDown(SDLK_ESCAPE))
				sdlw.Close();
		}

		// Draw a red square
		sdlw.SetColor01(1, 0, 0);
		sdlw.DrawRect(
			sdlw.getScreenWidth() / 2 - 50,
			sdlw.getScreenHeight() / 2 - 50,
			100, 100);
	}

	return 0;
}
```

For a more complex example see example.cpp.

Note: You MUST have `int argc, char* argv[]` as the main argumentst otherwise you will get an "SDL unresolved external".

## Installation
Just drop sdlw.h in your source files and `#include "sdlw.h"` in your main cpp (for example).

## Requirements
You'll need [SDL2](https://www.libsdl.org/download-2.0.php) linked to your project. There's plenty of tutorials online on how to do that. 

But here's a quick one if you use Visual Studio:
1. Download a development package from [here](https://www.libsdl.org/download-2.0.php);
2. Make a folder in your project like `MyProject\deps\sdl` for example;
3. Put include and libs from the pack you downloaded into that folder;
4. In Visual Studio, open project properties - right click in Solution Explorer on your project (should have ++ icon in vs2019) and select Properties;
5. In _C/C++ > General > Additional Include Directories_ add your include folder, which is in my example `$(ProjectDir)deps\sdl\include;` (don't forget to delimit with `;`);
6. In _Linker > General > Additional Library Directories_ add `$(ProjectDir)deps\sdl\lib\x86` (if 32 bit project) or `\x64` (if 64 bit project);`
7. In _Linker > Input > Additional Dependencies_ add `SDL2.lib;SDL2main.lib;`
8. Build your project. If you run it, it SHOULD tell you that SDL2.dll is missing;
9. Now take `SDL2.dll` from your package (found in lib\x86 or lib\x64) and put it in your binary folder. By default that should be ProjectFolder\Debug or ProjectFolder\Release (you'll need to add to the binary folder of each of your configurations once you build them);
10. Now when you run it, it should work!
