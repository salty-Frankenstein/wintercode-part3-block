#include "win.h"
Wnd::Wnd() {
	height = 800;
	width = 600;
	name = _T("Test");
}

Wnd::Wnd(int _height, int _width, bool(*callback)(), LPCSTR _name = _T("Test")) {
	height = _height;
	width = _width;
	Display = callback;
	name = _name;
}


bool Wnd::Create(HINSTANCE instanceHandle, int show) {
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = _T("BasicWndClass");

	if (!RegisterClass(&wc)) {
		MessageBox(0, _T("RegisterClass FAILED"), 0, 0);
		return false;
	}

	hwnd = CreateWindow(
		_T("BasicWndClass"),
		name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		height,
		width,
		0,
		0,
		instanceHandle,
		0
	);

	if (hwnd == 0) {
		MessageBox(0, _T("CreateWindow FAILED"), 0, 0);
		return false;
	}

	ShowWindow(hwnd, show);
	UpdateWindow(hwnd);

	return true;
}

int Wnd::Run() {
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Display();	//此处为回调函数
		}
	}
	return (int)msg.wParam;
}

HWND Wnd::GetHandle() {
	return hwnd;
}


/*
//Example main function:
//Display和WndProc暂时不为回调函数，须自己定义
//会修改

bool FrWnd::Display() {
keyboard();
DrawRectangle();
return true;
}


FrWnd *myWnd = new FrWnd(800, 600, "hello");
int WINAPI WinMain(WINPARAMETERS) {
if (!myWnd->Create(INITPARAMETERS))
return 0;
hwnd = myWnd->GetHandle();

D2DInit();
WICBmpInit();
D2DBmpInit();

return myWnd->Run();
}
*/