// This example draws a rectangle and you can use A and D to move it left and right

#include "sdlw.h"

int main(int argc, char *argv[])
{
    SDLW sdl;
    if (sdl.Init("My Awesome Game!", 800, 600))
        return EXIT_FAILURE;

    float rectPosX = 100;

    bool quit = false;
    while (!quit)
    {
        // This is needed to be able to use GetKey();
        sdl.pollEvents();

        while (sdl.popEvent())
        {
            // in getKeyUp and getKeyDown you should use SDLK_* ..
            if (sdl.getKeyDown(SDLK_ESCAPE))
                quit = true;
        }

        // ..while in getKey() you must use SDL_SCANCODE_*
        rectPosX += sdl.getKey(SDL_SCANCODE_A) ? -1 : (sdl.getKey(SDL_SCANCODE_D) ? 1 : 0);

        // Clear the screen to black
        sdl.Clear();

        // Draw a red square
        sdl.SetColor01(1, 0, 0);
        sdl.drawRect(rectPosX, 100, 100, 100);

        sdl.Render();
    }

    return EXIT_SUCCESS;
}