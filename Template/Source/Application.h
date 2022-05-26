#pragma once
#include "Engine.h"

using namespace Engine;


Void OnAppInit();
Void OnAppResize(SizeType width, SizeType height);
Bool OnAppQuit();

Void OnUpdate(Float32 deltaTime);
Void OnRender(Void* RenderTarget);