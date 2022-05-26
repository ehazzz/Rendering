#pragma once
#include "../../Core/System/Memory.h"


NAMESPACE_BEGIN(Engine)
class ENGINE_API Window
{
public:
	NOT_COPYABLE(Window);


	Window();


	/**
	*	Create a Windows window and display it
	*/
	Void Create(const WChar* title = L"Default Window", SizeType width = 1280, UInt32 height = 720);
	/**
	*	Poll events from operating system
	*/
	Void Update();

	template<typename Callback> Void BindEventCallback(Callback Fn);
	/**
	*	Handling insterested messages
	* 
	*	Note:
	*		This function is invoked auto by Engine
	*/
	Bool EventHandler(UInt32 message, UInt32 wordParam, UInt64 longParam);

	
	SizeType GetWidth() const;
	SizeType GetHeight() const;
	SizeType IsRunning() const;
	Handle GetHandle() const;
private:
	using CreateCallback	= Action<>;
	using ResizeCallback	= Action<SizeType, SizeType>;
	using QuitCallback		= Function<Bool>;

	CreateCallback OnCreated;
	ResizeCallback OnResized;
	QuitCallback WantToQuit;


	/**
	*	The width of window
	*/
	SizeType width;
	/**
	*	The height of window
	*/
	SizeType height;
	/**
	*	Flag:
	*		To confirm if the window should be displayed on screen
	*/
	Bool running;
	/**
	*	Native Windows window handle
	*/
	Handle handle;
};


template<typename Callback> Void Window::BindEventCallback(Callback Fn)
{
	if constexpr (TypesAreSame<Callback, CreateCallback>::Value)
		OnCreated = Fn;

	if constexpr (TypesAreSame<Callback, ResizeCallback>::Value)
		OnResized = Fn;

	if constexpr (TypesAreSame<Callback, QuitCallback>::Value)
		WantToQuit = Fn;
}
NAMESPACE_END(Engine)