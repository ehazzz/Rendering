#include "Timer.h"

#include "../../Platform/Windows/Windows.h"

#include <chrono>
#include <thread>


NAMESPACE_BEGIN(Engine)
static SizeType CurrentSystemTime()
{
#if defined(PLATFORM_WINDOWS)
	static Float64 period = -1.0;
	if (period < 0)
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		period = 1.0 / frequency.QuadPart * 1000;
	}

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	return Cast<SizeType>(period * counter.QuadPart);
#else
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
#endif
}

Void Sleep(SizeType milliseconds)
{
#if defined(PLATFORM_WINDOWS)
	::Sleep(milliseconds);
#else
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#endif
}


Timer::Timer()
{
	Reset();
}

RealType Timer::Elapsed() const
{
	return ElapsedMilliseconds() / 1000.0f;
}

SizeType Timer::ElapsedMilliseconds() const
{
	return CurrentSystemTime() - start;
}

Void Timer::Reset()
{
	start = CurrentSystemTime();
}
NAMESPACE_END(Engine)