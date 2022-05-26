#include "FileDialog.h"

#include <Windows.h>


NAMESPACE_BEGIN(Engine)
using DialogCallback = BOOL(APIENTRY*)(OPENFILENAMEW*);

static auto Fn =
[](const WChar* filters, const WChar* initDirectory, const WChar* title, Handle owner, DialogCallback Callback) -> Path
{
	OPENFILENAME ofn;
	constexpr SizeType size = sizeof(OPENFILENAME);
	Memory::Clear(&ofn, size);

	constexpr SizeType maxFileNameLength = 260;
	WChar filePath[1024];
	Memory::Clear(filePath, sizeof(filePath));

	ofn.lStructSize		= size;
	ofn.lpstrFile		= filePath;
	ofn.nMaxFile		= maxFileNameLength;
	ofn.lpstrInitialDir = initDirectory;
	ofn.lpstrFilter		= filters;
	ofn.hwndOwner		= (HWND)owner;
	ofn.lpstrTitle		= title;
	ofn.Flags			= OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	Callback(&ofn);
	return filePath;
};


Path FileDialog::Open(const WChar* filters, const WChar* initDirectory, const WChar* title, Handle owner)
{
    return Fn(filters, initDirectory, title, owner, GetOpenFileNameW);
}

Path FileDialog::Save(const WChar* filters, const WChar* initDirectory, const WChar* title, Handle owner)
{
    return Fn(filters, initDirectory, title, owner, GetSaveFileNameW);
}
NAMESPACE_END(Engine)