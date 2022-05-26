#include "Application.h"


Int32 EntryPoint()
{
	auto& window = runtimeContext.window;
	window.BindEventCallback(OnAppInit);
	window.BindEventCallback(OnAppResize);
	window.BindEventCallback(OnAppQuit);
	window.Create(L"Template(C++)", 1600, 900);

	auto gdi = GraphicDeviceInterface{ window.GetHandle() };

	auto& input = runtimeContext.input;

	while (window.IsRunning())
	{
		static Timer timer;
		static RealType timestep = 0.0f;
		{
			window.Update();
			input.Update();

			OnUpdate(timestep);
			gdi.Present(window.GetWidth(), window.GetHeight(), OnRender);

			input.Reset();
		}
		timestep = timer.Elapsed();
		timer.Reset();
	}


	return 0;
}


int main(int count, char** arguments)
{
	return EntryPoint();
}


#if defined(PLATFORM_WINDOWS)
#include <Windows.h>


int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
	return EntryPoint();
}
#endif