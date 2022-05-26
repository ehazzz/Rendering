#pragma once
/**
*	Windows GDI Wrapper
*/
#include "../../Core/System/Memory.h"


NAMESPACE_BEGIN(Engine)
class ENGINE_API GraphicDeviceInterface
{
public:
	NOT_COPYABLE(GraphicDeviceInterface);


	using RenderCallback = Action<Void*>;


	GraphicDeviceInterface(Handle nativeWindowsWindowHandle);
	~GraphicDeviceInterface();


	/**
	*	Overwrite RenderTarget by Callback to update the client area of Windows window
	* 
	*	Note:
	*		The size in bytes of RenderTarget point to memory block is width * height * 4
	*		Pixel format of RenderTarget is B8G8R8A8
	*/
	Void Present(SizeType width, SizeType height, RenderCallback Callback);
private:
	Handle handle;
	/**
	*	Target device context
	*/
	Handle targetDC;
	/**
	*	Memory device context
	*/
	Handle memoryDC;
};
NAMESPACE_END(Engine)