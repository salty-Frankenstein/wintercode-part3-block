﻿#include "resources.h"
#include "block.h"
#include "menu.h"
#include "game.h"
#include "timer.h"

bool Display();

Wnd *myWnd = new Wnd(655, 520-1, Display, _T("東方靈異伝～For WinterCode 2020"));

HWND hwnd;
extern GFactory *myGFactory = new GFactory(hwnd);

void GameInit() {
	LoadImages();
	LoadMenuUI();
	LoadObject();
}

GameString *fpsStr = new GameString(540, 460, 0.48);
Timer sysTimer;
void Init() {
	sysTimer.SetTime();
	fpsStr->str = "6000";
	myGFactory->Create();
	/*
	myText.Create();
	myTextW.Create();
	myGFactory->CreateBrush(blackBrush, _COLOR(Black));
	*/
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
		gamePool.Update();
		gamePool.Show();

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
		fpsStr->str = std::to_string(int(6000000.0/t));
	}
	fpsStr->Show();

	return myGFactory->EndDraw();
}

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();
	Init();
	return myWnd->Run();
}
