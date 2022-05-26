#pragma once
#include "../Base/Type.h"


NAMESPACE_BEGIN(Engine)
/**
*	Pause this thread for some milliseconds
*/
ENGINE_API Void Sleep(SizeType milliseconds);


class ENGINE_API Timer
{
public:
	Timer();


	/**
	*	Measure by seconds
	*/
	RealType Elapsed() const;
	/**
	*	Measure by milliseconds
	*/
	SizeType ElapsedMilliseconds() const;
	/**
	*	Record current system time
	*/
	Void Reset();
private:
	/**
	*	Time point
	* 
	*	Note:
	*		Unit is millisecond
	*/
	SizeType start;
};
NAMESPACE_END(Engine)