#pragma once
/**
*	Used By Other C++ Project
*/


/**
*	Include "this" header file
*
*	Path(Visual Studio Micro):	$(SolutionDir)CPP/Engine/Source/Include
*/


/**
*	Link this dynamic link library
*
*	Path(Visual Studio Micro):	$(SolutionDir)Binary/CPP/$(Configuration)/$(Platform)
*/
#pragma comment(lib, "Engine")


/**
*	Import engine module
*/
#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API_IMPORTS
#endif


/* Core/Base */
#include "../Runtime/Core/Base/EnumClass.h"
#include "../Runtime/Core/Base/Micro.h"
#include "../Runtime/Core/Base/Type.h"
/* Core/IO */
#include "../Runtime/Core/IO/Directory.h"
#include "../Runtime/Core/IO/File.h"
#include "../Runtime/Core/IO/FileSystem.h"
#include "../Runtime/Core/IO/Path.h"
/* Core/Mathematics */
#include "../Runtime/Core/Mathematics/Color.h"
#include "../Runtime/Core/Mathematics/Math.h"
#include "../Runtime/Core/Mathematics/Matrix.h"
#include "../Runtime/Core/Mathematics/Matrix4F.h"
#include "../Runtime/Core/Mathematics/Triangle.h"
#include "../Runtime/Core/Mathematics/Vector.h"
/* Core/String */
#include "../Runtime/Core/String/Character.h"
/* Core/System */
#include "../Runtime/Core/System/Allocator.h"
#include "../Runtime/Core/System/Buffer.h"
#include "../Runtime/Core/System/Memory.h"
#include "../Runtime/Core/System/Timer.h"

/* Function/ImmediateModeUI */
#include "../Runtime/Function/ImmediateModeUI/AsciiGlyph.h"
#include "../Runtime/Function/ImmediateModeUI/Button.h"
/* Function/Render */
#include "../Runtime/Function/Render/Mesh.h"
#include "../Runtime/Function/Render/Renderer.h"
#include "../Runtime/Function/Render/RenderPipeline.h"
#include "../Runtime/Function/Render/Serface.h"
#include "../Runtime/Function/Render/Shader.h"
#include "../Runtime/Function/Render/Texture2D.h"

/* Global */
#include "../Runtime/Global/RuntimeContext.h"

/* Platform/Windows */
#include "../Runtime/Platform/Windows/FileDialog.h"
#include "../Runtime/Platform/Windows/GraphicDeviceInterface.h"
#include "../Runtime/Platform/Windows/Window.h"
/* Platform/Windows/Input */
#include "../Runtime/Platform/Windows/Input/InputManager.h"