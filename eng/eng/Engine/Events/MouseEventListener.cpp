#include "..\\Core\CoreEngine.h"
#include "MouseEventListener.h"

CoreEngine* MouseEventListener::engineInstance;
int MouseEventListener::mouseX;
int MouseEventListener::mouseY; 
int MouseEventListener::prevmouseX;
int MouseEventListener::prevMouseY;
bool MouseEventListener::firstUpdate;

MouseEventListener::~MouseEventListener()
{
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)
{
	switch (e_.type) {
	case SDL_MOUSEBUTTONDOWN:
		UpdateMousePosition();
		NorifyOfMousePressed(e_.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		UpdateMousePosition();
		NotifyOfMouseRelesed(e_.button.button);
		break;
	case SDL_MOUSEMOTION:
		UpdateMousePosition();
		NotifyOfMouseMover();
		break;
	case SDL_MOUSEWHEEL:
		NotifyOfMouseScroll(e_.wheel.y);
		break;
	default:
		break;
	}
}

void MouseEventListener::NorifyOfMousePressed(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMousePressed(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyOfMouseRelesed(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseReleased(mouseX, mouseY, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMover()
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseMove(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return glm::vec2(prevmouseX, prevMouseY);
}

glm::vec2 MouseEventListener::GetMousePos()
{
	return glm::vec2(mouseX, mouseY);
}

glm::vec2 MouseEventListener::GetMouseOffSet()
{
	return glm::vec2(mouseX - prevmouseX, prevMouseY - mouseY);
}

void MouseEventListener::UpdateMousePosition()
{
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);
	tempY = engineInstance->GetScreenSize().y - tempY;
	if (firstUpdate)
	{
		prevmouseX = mouseX = tempX;
		prevMouseY = mouseY = tempY;
		firstUpdate = false;
	}
	else if (tempX != mouseX || tempY != mouseY)
	{
		prevmouseX = mouseX;
		prevMouseY = mouseY;
		mouseX = tempX;
		mouseY = tempY;
	}
}
