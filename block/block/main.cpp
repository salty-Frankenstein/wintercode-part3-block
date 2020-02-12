﻿#include "resources.h"
#include "block.h"
#include "menu.h"
#include "game.h"
#include "background.h"
#include "timer.h"
#include <thread>

bool Display();

Wnd *myWnd = new Wnd(655, 520-1, Display, _T("東方靈異伝～For WinterCode 2020"));

HWND hwnd;
extern GFactory *myGFactory = new GFactory(hwnd);
extern Layer myLayer;

bool loadComplete = false;
void GameInit() {
	
	static bool loaded = false;
	if (!loaded) {
		LoadImages();
		LoadSound();
		LoadMenuUI();
		LoadGame();
		gamePool.Sort();
		//FileInit();
		loaded = true;
	}
	
	loadComplete = true;
}

GameString *fpsStr = new GameString(520, 460, 0.48, 5);
Timer sysTimer;
void Init() {
	sysTimer.SetTime();
	myGFactory->Create();
	myGFactory->CreateLayer(myLayer);
	myGFactory->GetHandle()->GetTransform(&oriTransMat);
	
	//myGFactory->CreateBrush(blackBrush, _COLOR(Black));
	//GameInit();
	
}

extern GameState gameState;


std::thread* loadThread;
Bitmap loadingImg(L"./src/loading.png");
Bitmap shoujoImg(L"./src/shoujo.png");
Sprite* shoujo = new Sprite(460, 420, shoujoImg, DefaultShow, DefaultUpdate, 211 * 0.8, 58 * 0.8);
void LoadLoad() {
	static bool loaded = false;
	if (!loaded) {
		BmpInit(loadingImg);
		BmpInit(shoujoImg);
		loadThread = new std::thread(GameInit);
		//loadThread->join();
		loaded = true;
	}
}

void LoadShow() {
	myGFactory->DrawBitmap(loadingImg, 0, 0, 640, 480);
	if (gameTimer / 60 % 2)
		shoujo->opacity += 0.015;
	else 
		shoujo->opacity -= 0.015;
	shoujo->Show();
	if (loadComplete) {
		gameState = MENU;
		gameTimer = 0;
	}
}


bool Display() {

	keyboard(gameState);
	myGFactory->BeginDraw();
	myGFactory->Clear(_COLOR(Black));

	gameTimer++;
	switch (gameState)
	{
	case LOAD:
		LoadLoad();
		LoadShow();
		
		break;
	case MENU:
		MenuUI_Load();
		menuUI_Pool.Update();
		menuUI_Pool.Show();
		MenuUI_Update();
		
		break;
	case SELECT:
	//	OptionLoad();
		gameState = GAME;
		break;
	case HISCORE:
		break;
	case GAME:
		//objNumStr->str = std::to_string(gamePool.Size());
		objNumStr->str = std::to_string(stageNow->BlockNum());
		GameLoad();
		GameUpdate();
		myBackground.Show();
		if (gameProcess != GAME_PAUSE) {
			//myGFactory->Clear(_COLOR(Gray));
			stageNow->Update();
			gamePool.Update();
			myBackground.Update();
		}
		stageNow->Show();
		gamePool.Show();
		if (!stageNow->textPtr->IsOver() && gameProcess != GAME_PAUSE)
			stageNow->textPtr->Show();
		if (gameProcess == GAME_PAUSE) {
			titleBgm->Pause();
			mokouMidBgm->Pause();
			mokouBgm->Pause();
			pachiMidBgm->Pause();
			pachiBgm->Pause();
			utsuhoMidBgm->Pause();
			utsuhoBgm->Pause();
		}
		else {
			titleBgm->Play();
			mokouMidBgm->Play();
			mokouBgm->Play();
			pachiMidBgm->Play();
			pachiBgm->Play();
			utsuhoMidBgm->Play();
			utsuhoBgm->Play();
		}
		break;
	case QUIT:
		break;
	default:
		break;
	}

	if (gameState != LOAD) {
		static long long t;	//每60帧计算一次fps
		if (gameTimer % 60 == 0) {
			sysTimer.Update();
			t = sysTimer.GetIntervalMilli();
			sysTimer.SetTime();
			fpsStr->str = std::to_string((60000.0 / t));
			for (int i = 1; i <= 4; i++)
				fpsStr->str.pop_back();
			fpsStr->str += "fps";
		}
		fpsStr->Show();
	}
	
	return myGFactory->EndDraw();
}

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();
	Init();
	return myWnd->Run();
}
