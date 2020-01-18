/*					*\
		win.h
	·â×°WindowsAPI
	2020 wintercode
	by id:191220017
\*					*/

#pragma once

#ifndef WINDOWS_INIT
#define WINDOWS_INIT

#include<windows.h>
#include<tchar.h>

#define WINPARAMETERS HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd
#define INITPARAMETERS hInstance, nShowCmd

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


class Wnd {
public:
	Wnd();
	Wnd(int _height, int _width, bool(*callback)(), LPCSTR _name);
	~Wnd() {}

	HWND GetHandle();
	bool Create(HINSTANCE instanceHandle, int show);
	int Run();
	//bool Display();
	bool(*Display)();
private:
	HWND hwnd;
	LPCSTR name;
	int height;
	int width;
};

#endif // WINDOWS_INIT