#include <OGLGE/Game/OGame.h>
#include <OGLGE/Window/OWindow.h>
#include <OGLGE/Graphics/OGraphicsEngine.h>
#include <Windows.h>

OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>();
	m_display = std::make_unique<OWindow>();
}

OGame::~OGame()
{
}

void OGame::run()
{
	MSG msg;
	while (m_isRunning)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) 
		{
			if (msg.message == WM_QUIT) 
			{
				m_isRunning = false;
				continue;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(1);
	}
}

void OGame::quit()
{
	m_isRunning = false;
}
