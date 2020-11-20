#pragma once
#include <SDL.h>
#include <unordered_map>

typedef void (*action)(bool down);
class InputManager {
private:
	SDL_Event ev;
	bool keys[128];
	bool pkeys[128];
	bool buttons[5];
	bool pbuttons[5];
public:
	bool hasQuit = false;
	float mouseX, mouseY;
	void pollEvents() {
		memcpy(pkeys, keys, sizeof(bool) * 128);
		memcpy(pbuttons, buttons, sizeof(bool) * 5);
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				keys[ev.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				keys[ev.key.keysym.scancode] = false;
				break;
			case SDL_QUIT:
				hasQuit = true;
				break;
			case SDL_MOUSEMOTION:
				mouseX = ev.motion.x;
				mouseY = -ev.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				buttons[ev.button.button] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				buttons[ev.button.button] = false;
				break;
			}
		}
	}
	bool getKey(SDL_Scancode key) {
		return keys[key];
	}
	bool getKeyDown(SDL_Scancode key) {
		return keys[key] && !pkeys[key];
	}
	bool getMouseDown(int button) {
		return buttons[button] && !pbuttons[button];
	}
	bool getMouse(int button) {
		return buttons[button];
	}
};