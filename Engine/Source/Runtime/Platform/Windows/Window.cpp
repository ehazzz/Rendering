#include "Window.h"

#include "WindowProcedure.h"


NAMESPACE_BEGIN(Engine)
Window::Window()
{
	OnCreated	= nullptr;
	OnResized	= nullptr;
	WantToQuit	= nullptr;

	width	= 0;
	height	= 0;
	running = true;
	handle	= nullptr;
}

Void Window::Create(const WChar* title, SizeType width, UInt32 height)
{
	HINSTANCE hInstance		= GetModuleHandleW(nullptr);
	const WChar* className	= L"Class Entry";

	// window style
	UInt32 style		= WS_OVERLAPPEDWINDOW;
	UInt32 extendStyle	= 0u;

	// register window class
	{
		WNDCLASSEXW windowClass;
		SizeType size = sizeof(windowClass);
		Memory::Clear(&windowClass, size);

		windowClass.cbSize			= size;
		windowClass.hInstance		= hInstance;
		windowClass.lpszClassName	= className;
		windowClass.lpfnWndProc		= WindowProcedure;

		RegisterClassExW(&windowClass);
	}

	// resized to expected size
	UInt32 realWidth, realHeight;
	{
		RECT rect = { 0, 0, width, height };
		AdjustWindowRectEx(&rect, style, 0, extendStyle);

		realWidth	= rect.right - rect.left;
		realHeight	= rect.bottom - rect.top;
	}

	// create and display
	{
		handle = CreateWindowExW(
			extendStyle,
			className,
			title,
			style,
			CW_USEDEFAULT, CW_USEDEFAULT, realWidth, realHeight,
			nullptr, 0, hInstance, nullptr
		);

		ShowWindow((HWND)handle, SW_SHOWDEFAULT);
	}
}

Void Window::Update()
{
	static MSG message;
	Memory::Clear(&message, sizeof(MSG));

	while (PeekMessageW(&message, (HWND)handle, 0, 0, PM_REMOVE))
		DispatchMessageW(&message);
}

Bool Window::EventHandler(UInt32 message, UInt32 wordParam, UInt64 longParam)
{
	Bool isHandled = true;
	switch (message)
	{
	case WM_CREATE:
		if (OnCreated) OnCreated();
		break;
	case WM_SIZE:
	{
		width	= longParam & 0xffff;
		height	= (longParam >> 16) & 0xffff;

		if (OnResized) OnResized(width, height);
	}
	break;
	case WM_DESTROY:
	case WM_CLOSE:
		running = WantToQuit ? !WantToQuit() : false;
		break;
	default:
		isHandled = false;
		break;
	}

	return isHandled;
}

SizeType Window::GetWidth() const
{
	return width;
}

SizeType Window::GetHeight() const
{
	return height;
}

SizeType Window::IsRunning() const
{
	return running;
}

Handle Window::GetHandle() const
{
	return handle;
}
NAMESPACE_END(Engine)