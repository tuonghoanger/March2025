/*
	DirectX 11 3D Rendering 
*/

#include "App.h"
#include <sstream>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	try
	{
		return App{ lpCmdLine }.Go();
	}
	catch (const HoangException& e) // MB_TASKMODAL blocks all other windows from running until it is closed
	{
		//SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&DefWindowProc));
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_TASKMODAL | MB_OK | MB_ICONEXCLAMATION); 
	}

	catch (const std::exception& e)
	{
		//SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&DefWindowProc));
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_TASKMODAL | MB_OK | MB_ICONEXCLAMATION);
	}
	
	catch (...)
	{
		//SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&DefWindowProc));
		MessageBoxA(nullptr, "No details available", "Unknown Exception", MB_TASKMODAL | MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}