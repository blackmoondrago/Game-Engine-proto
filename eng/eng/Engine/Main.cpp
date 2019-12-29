
#include "Core/CoreEngine.h"
#include "../Game/Game1.h"

int main(int argc, char* argv[])
{
	CoreEngine::GetInstance()->SetGameInstance(new Game1());

	if (!CoreEngine::GetInstance()->OnCreate("GAME301 Engine", 800, 600))
	{
		std::cout << "Engine creation failed" << std::endl;
		Debug::FatalError("Engine Creation Failed", "Main.cpp", __LINE__);
	return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}