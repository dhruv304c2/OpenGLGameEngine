#include <OGLGE/Graphics/OGraphicsEngine.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"OGLGEDummyWindow";
	wc.lpfnWndProc = DefWindowProc;
	wc.style = CS_OWNDC;

	auto classId = RegisterClassEx(&wc);
	assert(classId);

	RECT rc = { 0,0, 1024, 768 };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	auto dummyWindow = CreateWindowEx(NULL, MAKEINTATOM(classId), L"", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,NULL, NULL, NULL, NULL);

	assert(dummyWindow);

	auto dummyDC = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
	pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion = 1;
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | LPD_DOUBLEBUFFER;
	pixelFormatDesc.cColorBits = 32;
	pixelFormatDesc.cAlphaBits = 8;
	pixelFormatDesc.cDepthBits = 24;
	pixelFormatDesc.cStencilBits = 8;
	pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

	auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);
	SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);

	auto dummyContext = wglCreateContext(dummyDC);
	assert(dummyContext);

	wglMakeCurrent(dummyDC, dummyContext);

	if (!gladLoadWGL(dummyDC))
		throw std::runtime_error("OGraphicsEngine - Error galdLoadWGL failed");
	if (!gladLoadGL())
		throw std::runtime_error("OGraphicsEngine - Error galdLoadGL failed");

	wglMakeCurrent(dummyDC, 0);
	wglDeleteContext(dummyContext);
	ReleaseDC(dummyWindow, dummyDC);
	DestroyWindow(dummyWindow);
}

OGraphicsEngine::~OGraphicsEngine()
{

}
