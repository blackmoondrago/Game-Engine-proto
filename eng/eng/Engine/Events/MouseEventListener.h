#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

class CoreEngine;

class MouseEventListener
{
public:

	MouseEventListener() = delete;
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	~MouseEventListener();

	static void RegisterEngineObject(CoreEngine* engine_);
	static void Update(SDL_Event e_);
	static void NorifyOfMousePressed(int buttonType_);
	static void NotifyOfMouseRelesed(int buttonType_);
	static void NotifyOfMouseMover();
	static void NotifyOfMouseScroll(int y_);

	static glm::vec2 GetPreviousMousePosition();
	static glm::vec2 GetMousePos();
	static glm::vec2 GetMouseOffSet();

private:
	static CoreEngine* engineInstance;
	static int mouseX, mouseY, prevmouseX, prevMouseY;
	static bool firstUpdate;
	static void UpdateMousePosition();
};

