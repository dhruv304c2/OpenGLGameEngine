#pragma once
#include <memory>

class OWindow;
class OGraphicsEngine;
class OGame
{
public:
	OGame();
	~OGame();

	void run();
	void quit();
protected:
	bool m_isRunning = true;
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
	std::unique_ptr<OWindow> m_display;
};

