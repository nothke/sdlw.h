#pragma once

#include <iostream>
#include <sdl/SDL.h>

struct SDLW
{
	SDL_Surface* winSurface{ nullptr };
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	SDL_Event event{};

private:
	bool inited{ false };

	bool wantsToClose{ false };

	int screenWidth{ 0 };
	int screenHeight{ 0 };

	float lastFrameTime{ 0 };
	float frame_dt{ 0 };

public:

	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }

	int Init(const std::string windowTitle = "SDL App", int windowWidth = 800, int windowHeight = 600, bool fullscreen = false) {
		using namespace std;

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			cout << "Error initializing SDL: " << SDL_GetError() << endl;
			system("pause");
			return EXIT_FAILURE;
		}

		int flags =
			SDL_WINDOW_SHOWN |
			(fullscreen ? SDL_WINDOW_FULLSCREEN : 0);

		if (fullscreen)
		{
			windowWidth = 0;
			windowHeight = 0;
		}

		window = SDL_CreateWindow(windowTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, flags);

		if (!window) {
			cout << "Error creating window: " << SDL_GetError() << endl;
			system("pause");
			return EXIT_FAILURE;
		}

		//SDL_GL_SetSwapInterval(1);

		winSurface = SDL_GetWindowSurface(window);

		if (!winSurface) {
			cout << "Error getting surface: " << SDL_GetError() << endl;
			system("pause");
			return EXIT_FAILURE;
		}

		int rendererFlags =
			SDL_RENDERER_PRESENTVSYNC |
			SDL_RENDERER_ACCELERATED;

		renderer = SDL_CreateRenderer(window, -1, rendererFlags);

		SDL_GetWindowSize(window, &screenWidth, &screenHeight);

		inited = true;

		Clear();

		return EXIT_SUCCESS;
	}

	const Uint8* keyState = nullptr;

	/// <summary>
	/// Called automatically by IsRunning()
	/// </summary>
	void UpdateDeltaTime()
	{
		double t = time();
		frame_dt = static_cast<float>(t - lastFrameTime);
		lastFrameTime = t;
	}

	/// <summary>
	/// Polls events, updates deltaTime and clears the screen
	/// </summary>
	bool IsRunning(bool clear = true, bool render = true)
	{
		if (render)
			Render();

		PollEvents();

		UpdateDeltaTime();

		if (clear)
			Clear();

		return !wantsToClose;
	}

	void Close()
	{
		wantsToClose = true;
	}

	/// <summary>
	/// Called automatically by IsRunning()
	/// </summary>
	void PollEvents()
	{
		keyState = SDL_GetKeyboardState(NULL);
	}

	/// <summary>
	/// Call this in a while(PopEvent()) {} to get individual input events.
	/// Then you can use sdlw.GetKeyDown() e.g. inside it.
	/// </summary>
	bool PopEvent()
	{
		return SDL_PollEvent(&event);
	}

#pragma warning(disable:26812) // disables enum class warning
	bool GetKeyDown(SDL_KeyCode key)
	{
		return event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == key;
	}

	bool GetKeyUp(SDL_KeyCode key)
	{
		return event.type == SDL_KEYUP &&
			event.key.keysym.sym == key;
	}

	bool GetKey(SDL_Scancode key)
	{
		return keyState[key];
	}

	bool GetMouseDown(int i)
	{
		return event.type == SDL_MOUSEBUTTONDOWN &&
			event.button.button == i;
	}
#pragma warning(default:26812)

	void Clear()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}

	void Render()
	{
		SDL_RenderPresent(renderer);
	}

	/// <summary>
	/// Time from start, in seconds.
	/// </summary>
	double time()
	{
		return SDL_GetTicks() * 0.001;
	}

	/// <summary>
	/// Time since the last frame.
	/// </summary>
	float deltaTime()
	{
		return frame_dt;
	}

	/// <summary>
	/// Called automatically by the destructor.
	/// </summary>
	void Destroy()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void SetColor(const SDL_Color& color)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	}

	void SetColor01(float r, float g, float b)
	{
		SDL_SetRenderDrawColor(renderer,
			static_cast<Uint8>(r * SDL_MAX_UINT8),
			static_cast<Uint8>(g * SDL_MAX_UINT8),
			static_cast<Uint8>(b * SDL_MAX_UINT8),
			SDL_MAX_UINT8);
	}

	void DrawLine(SDL_FPoint p1, SDL_FPoint p2)
	{
		SDL_RenderDrawLineF(renderer, p1.x, p1.y, p2.x, p2.y);
	}

	void DrawRay(SDL_FPoint pos, SDL_FPoint dir)
	{
		SDL_RenderDrawLineF(renderer, pos.x, pos.y, pos.x + dir.x, pos.y + dir.y);
	}

	void DrawRect(float x, float y, float w, float h)
	{
		SDL_FRect r = { x, y, w, h };
		SDL_RenderFillRectF(renderer, &r);
	}

	const int mouseX() {
		int x;
		SDL_GetMouseState(&x, nullptr);
		return x;
	}

	const int mouseY() {
		int y;
		SDL_GetMouseState(nullptr, &y);
		return y;
	}

	void mousePosition(int& x, int& y)
	{
		SDL_GetMouseState(&x, &y);
	}

	~SDLW()
	{
		if (inited)
		{
			Destroy();
		}
	}
};
