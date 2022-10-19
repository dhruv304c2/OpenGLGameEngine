#include <OGLGE/Game/OGame.h>
#include <OGLGE/Window/OWindow.h>
#include <Windows.h>

OGame::OGame()
{
	m_display = new OWindow();
}

OGame::~OGame()
{
	delete m_display;
}

void OGame::run()
{
	MSG msg;
	while (m_isRunning && !m_display->isClosed())
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) 
		{
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
