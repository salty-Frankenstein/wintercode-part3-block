#include "engine.h"

bool Display();

HWND hwnd;
Wnd *myWnd = new Wnd(800, 600, Display, _T("Block"));
GFactory *myGFactory = new GFactory(hwnd);
Brush blackBrush, blueBrush;
Text myText, myTextW;
std::string textOut;
float oriX = 0, oriY = 0, size = 25;

float x = 100, y = 100;
extern bool getKey[256];
void keyboard() {
	if (getKey[VK_LEFT])
		x -= 5;
	if (getKey[VK_RIGHT])
		x += 5;
	if (getKey[VK_UP])
		y -= 5;
	if (getKey[VK_DOWN])
		y += 5;
}


bool Init() {
	myGFactory->Create();
	myText.Create();
	myTextW.Create();

	myGFactory->CreateBrush(blackBrush, _COLOR(Black));
	return true;
}

bool Display() {
	keyboard();
	myGFactory->BeginDraw();
	myGFactory->Clear(_COLOR(Gray));


	myTextW.SetRect(10.f + x, 10.f + y, 300.f + x, 150.f + y);

	
	myGFactory->WriteW(myTextW, blackBrush, L"½ñÈÕ¤â¤¤¤¤ÌìšÝ¡î");

	textOut = "Position:\nx="
	+ std::to_string(int(50 + x))
	+ "\ny="
	+ std::to_string(int(50 + y));
	myGFactory->Write(myText, blackBrush, textOut);
	

	return myGFactory->EndDraw();
}

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();
	Init();
	return myWnd->Run();
}
