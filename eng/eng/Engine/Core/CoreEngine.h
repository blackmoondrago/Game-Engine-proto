#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>

#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "../Rendering/3D/GameObject.h"
#include "../../Game/Scene/Scene.h"
#include "..//Graphics/ShaderHandler.h"
#include "..//Graphics/TextureHandler.h"
#include "..//Camera/Camera.h"
#include "..\\Events\MouseEventListener.h"
#include "..//Events/EventListener.h"
#include "..//Rendering/SceneGraphs.h"


class CoreEngine {
public:
	//Singleton
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;


	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning() const;
	void SetIsRunning(bool isRunning_);
	void SetGameInstance(GameInterface* gameInterface_);
	int GetCurrentScene() const;
	void SetCurrentScene(int currentScene_);
	glm::vec2 GetScreenSize() const;

	void NotifyOfMousePressed(int x_, int y_);
	void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
	void NotifyOfMouseMove(int x_, int y_);
	void NotifyOfMouseScroll(int y_);

	void ExitGame();

	void SetCamera(Camera* camera_);
	Camera* GetCamera();

	//Singleton
	static CoreEngine* GetInstance();


private:
	CoreEngine();
	~CoreEngine();

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	Window* window;
	Timer timer;
	GameInterface* gameInterface;
	Camera* camera;

	bool isRunning;
	unsigned int fps;
	int currentScene;

	//Instance / Singleton
	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;
};

#endif //!COREENGINE_H