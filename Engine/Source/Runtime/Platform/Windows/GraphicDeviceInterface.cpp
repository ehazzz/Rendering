#include "GraphicDeviceInterface.h"

#include "Windows.h"


NAMESPACE_BEGIN(Engine)
GraphicDeviceInterface::GraphicDeviceInterface(Handle nativeWindowsWindowHandle)
{
	HDC targetDC = GetDC((HWND)nativeWindowsWindowHandle);
	HDC memoryDC = CreateCompatibleDC(targetDC);

	this->handle	= nativeWindowsWindowHandle;
	this->targetDC	= targetDC;
	this->memoryDC	= memoryDC;
}

GraphicDeviceInterface::~GraphicDeviceInterface()
{
	HWND handle		= (HWND)this->handle;
	HDC targetDC	= (HDC)this->targetDC;
	HDC memoryDC	= (HDC)this->memoryDC;

	if (!handle)
		return;

	if (targetDC)
		ReleaseDC(handle, targetDC);

	if (memoryDC)
		ReleaseDC(handle, memoryDC);
}

Void GraphicDeviceInterface::Present(SizeType width, SizeType height, RenderCallback Callback)
{
	HDC targetDC = (HDC)this->targetDC;
	HDC memoryDC = (HDC)this->memoryDC;


	Void* RenderTarget	= nullptr;
	HBITMAP hBitmap		= nullptr;
	{
		BITMAPINFO bitmapInfo;
		SizeType size = sizeof(BITMAPINFO);
		Memory::Clear(&bitmapInfo, size);

		bitmapInfo.bmiHeader.biSize		= size;
		bitmapInfo.bmiHeader.biBitCount = 4 * 8;
		bitmapInfo.bmiHeader.biPlanes	= 1;
		bitmapInfo.bmiHeader.biWidth	= width;
		bitmapInfo.bmiHeader.biHeight	= height;

		hBitmap = CreateDIBSection(memoryDC, &bitmapInfo, DIB_PAL_COLORS, &RenderTarget, 0, 0);
	}

	if (Callback) Callback(RenderTarget);

	if (hBitmap)
	{
		SelectObject(memoryDC, hBitmap);
		BitBlt(targetDC, 0, 0, width, height, memoryDC, 0, 0, SRCCOPY);
		DeleteObject(hBitmap);
	}
}
NAMESPACE_END(Engine)
