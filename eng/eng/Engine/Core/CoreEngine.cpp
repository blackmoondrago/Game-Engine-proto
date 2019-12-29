#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine()
{
	window = nullptr;
	isRunning = false;
	fps = 120;
	gameInterface = nullptr;
	camera = nullptr;
	currentScene = 0;
}

CoreEngine::~CoreEngine()
{
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	if (!window->OnCreate(name_, width_, height_))
	{
		//std::cout << "Window creation failed" << std::endl;
		Debug::FatalError("Window Creation Failed", "CoreEngine.cpp", __LINE__);
		return isRunning = false;
	}
	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/colourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("BasicShader", "Engine/Shaders/TexVertexShader.glsl", "Engine/Shaders/texFragShader.glsl");

	if (!gameInterface->OnCreate()) {
		//DEBUG LINE
		Debug::FatalError("Game Interface Creation Failed", "CoreEngine.cpp", __LINE__);
		return isRunning = false;
	}

	Debug::Info("CORE ENGINE STARTED", "CoreEngine.cpp", __LINE__);
	timer.Start();

	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning) {
		EventListener::Update();
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const
{
	return false;
}

void CoreEngine::SetIsRunning(bool isRunning_)
{
	isRunning = isRunning_;
}

void CoreEngine::SetGameInstance(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

int CoreEngine::GetCurrentScene() const
{
	return currentScene;
}

void CoreEngine::SetCurrentScene(int currentScene_)
{
	currentScene = currentScene_;
}

glm::vec2 CoreEngine::GetScreenSize() const
{
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

void CoreEngine::NotifyOfMousePressed(int x_, int y_)
{
}

void CoreEngine::NotifyOfMouseReleased(int x_, int y_, int buttonType_)
{
	CollisionHandler::GetInstance()->Update(glm::vec2(x_, y_), buttonType_);
}

void CoreEngine::NotifyOfMouseMove(int x_, int y_)
{
	if (camera)
	{
		camera->ProcessMouseMovemnet(MouseEventListener::GetMouseOffSet().x, MouseEventListener::GetMouseOffSet().y);
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_)
{
	if (camera)
	{
		camera->ProcessMouseZoom(y_);
	}
}

void CoreEngine::ExitGame()
{
	isRunning = false;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

Camera* CoreEngine::GetCamera()
{
	return camera;
}

void CoreEngine::Update(const float deltaTime_)
{
	//DEBUG ?
	//	std::cout << "Delta time is : " << deltaTime_ << std::endl;

	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render()
{

	glClearColor(0.0f, 5.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//GAME RENDER
	if (gameInterface)
		gameInterface->Render();

	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	delete camera;
	camera = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}

CoreEngine* CoreEngine::GetInstance() 
{
	if (engineInstance.get() == nullptr)
	{
		engineInstance.reset(new CoreEngine);
	}

	return engineInstance.get();
}