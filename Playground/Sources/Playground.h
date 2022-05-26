#pragma once
#include "Engine.h"

using namespace Engine;


Void OnAppInit();
Void OnAppResize(SizeType width, SizeType height);
Bool OnAppQuit();

Void OnUpdate(RealType deltaTime);
Void OnRender(Void* RenderTarget);


Void DrawMaskBackground();
Void DrawImmediateModeUI();