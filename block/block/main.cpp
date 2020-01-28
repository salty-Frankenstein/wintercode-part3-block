#include "resources.h"
#include "block.h"

bool Display();

Wnd *myWnd = new Wnd(655, 520, Display, _T("Block"));

HWND hwnd;
extern GFactory *myGFactory = new GFactory(hwnd);


void Init() {
	myGFactory->Create();
	myText.Create();
	myTextW.Create();
	myGFactory->CreateBrush(blackBrush, _COLOR(Black));
	GameInit();
}

extern GameState gameState;

bool Display() {
	keyboard(gameState);
	myGFactory->BeginDraw();
	myGFactory->Clear(_COLOR(Gray));

	gameTimer++;
	switch (gameState)
	{
	case MENU:
		menuUI_Pool.Update();
		menuUI_Pool.Show();
		MenuUI_Update();
		break;
	case HISCORE:
		break;
	case GAME:

		pool.Update();
		pool.Show();
		break;
	case QUIT:
		break;
	default:
		break;
	}
	myTextW.SetRect(10.f + x, 10.f + y, 300.f + x, 150.f + y);

	//myGFactory->WriteW(myTextW, blackBrush, L"½ñÈÕ¤â¤¤¤¤ÌìšÝ¡î");
	/*
	textOut = "Position:\nx="
		+ std::to_string(int(50 + x))
		+ "\ny="
		+ std::to_string(int(50 + y))
		+ "\ntime:"
		+ std::to_string(gameTimer / 60)
		//+ "\nisHit:"
		//+ std::to_string(isHit(board, borderLeft) || isHit(board, borderRight))
		;

	
	myGFactory->Write(myText, blackBrush, textOut);
*/
	return myGFactory->EndDraw();
}

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();
	Init();
	return myWnd->Run();
}
