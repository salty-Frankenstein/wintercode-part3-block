#include "resources.h"
#include "block.h"
#include "menu.h"
#include "game.h"
#include "timer.h"

bool Display();

Wnd *myWnd = new Wnd(655, 520-1, Display, _T("東方靈異伝～For WinterCode 2020"));

HWND hwnd;
extern GFactory *myGFactory = new GFactory(hwnd);
extern Layer myLayer;

void GameInit() {
	LoadImages();
	LoadMenuUI();
	LoadGame();
}

GameString *fpsStr = new GameString(520, 460, 0.48);
Timer sysTimer;
void Init() {
	sysTimer.SetTime();
	//fpsStr->str = "6000";
	myGFactory->Create();
	myGFactory->CreateLayer(myLayer);
	/*
	myText.Create();
	myTextW.Create();
	*/
	myGFactory->CreateBrush(blackBrush, _COLOR(Black));
	
	GameInit();
}

void DrawEffect() {
	static double opacity = 1;
	if (gameTimer <= 100) {
		opacity -= 0.01;
	}
	else opacity = 0;
	myLayer.layerParameters.opacity = opacity;
	//myLayer.layerParameters.opacityBrush = blackBrush.GetBrush();
	myGFactory->PushLayer(myLayer);
	myGFactory->FillRectangle(blackBrush, 0, 0, 640, 480);

	myGFactory->PopLayer();
}

extern GameState gameState;

bool Display() {

	keyboard(gameState);
	myGFactory->BeginDraw();
	

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
		if (gameProcess != GAME_PAUSE) {
			myGFactory->Clear(_COLOR(Gray));
			gamePool.Update();
			gamePool.Show();
		}
		
		GameUpdate();
		break;
	case QUIT:
		break;
	default:
		break;
	}
	/*
	myTextW.SetRect(10.f + x, 10.f + y, 300.f + x, 150.f + y);

	myGFactory->WriteW(myTextW, blackBrush, L"今日もいい天気☆");
	
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
	static long long t;	//每60帧计算一次fps
	if (gameTimer % 60 == 0) {
		sysTimer.Update();
		t = sysTimer.GetIntervalMilli();
		sysTimer.SetTime();
		fpsStr->str = std::to_string(int(60000.0/t)) + '.' 
			+ std::to_string(int(6000000.0 / t)%100) + "fps";
	}
	fpsStr->Show();
	//DrawEffect();
	
	return myGFactory->EndDraw();
}

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();
	Init();
	return myWnd->Run();
}
