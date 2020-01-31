#include "resources.h"
#include "block.h"
#include "menu.h"
#include "game.h"
#include "timer.h"
#include <thread>
#include <mutex>

bool Display();

Wnd *myWnd = new Wnd(655, 520-1, Display, _T("東方靈異伝～For WinterCode 2020"));

HWND hwnd;
extern GFactory *myGFactory = new GFactory(hwnd);
extern Layer myLayer;

std::mutex m;
bool loadComplete = false;
void GameInit() {
	
	static bool loaded = false;
	if (!loaded) {
		m.lock();
		LoadImages();
		LoadMenuUI();
		LoadGame();
		m.unlock();
		loaded = true;
	}
	
	loadComplete = true;
}

GameString *fpsStr = new GameString(520, 460, 0.48);
Timer sysTimer;
void Init() {
	sysTimer.SetTime();
	myGFactory->Create();
	myGFactory->CreateLayer(myLayer);
	/*
	myText.Create();
	myTextW.Create();
	*/
	myGFactory->CreateBrush(blackBrush, _COLOR(Black));
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
		loadThread->join();
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
	if (loadComplete && gameTimer >= 60 * 3) {
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
