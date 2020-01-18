#include "engine.h"

bool Display() { return true; }

HWND hwnd;
Wnd *myWnd = new Wnd(800, 600, Display, _T("Block"));

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();

	return myWnd->Run();
}
