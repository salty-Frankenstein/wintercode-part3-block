#include "block.h"
bool Display();

Wnd *myWnd = new Wnd(655, 520, Display, _T("Block"));

HWND hwnd;
GFactory *myGFactory = new GFactory(hwnd);
Brush blackBrush, blueBrush;
Text myText, myTextW;
Text scoreTxt;
std::string textOut;
//float oriX = 0, oriY = 0, size = 25;


Bitmap testImg(L"./src/enemy1.png");
Bitmap boardImg(L"./src/board.png");
Bitmap bgImg(L"./src/bg.png");
void LoadImages() {
	testImg.Create();
	boardImg.Create();
	bgImg.Create();
	myGFactory->CreateBitmap(testImg);
	myGFactory->CreateBitmap(boardImg);
	myGFactory->CreateBitmap(bgImg);
}

auto DefaultShow = [](Sprite* t) {
	myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height); 
};



void BoardShow(Sprite* t) {

	t->x = x;
}



void LoadObject() {
	pool.AddSon(new Sprite(0, 0, bgImg, DefaultShow, [](Sprite* t) {}, 640, 480));
	pool.AddSon(new Sprite(0, 0, INVISIBLE_IMG, INVISIBLE_SHOW, [](Sprite* t) {t->x = x; }, 30, 30));
	pool.AddSon(new Sprite(400, 400, boardImg, DefaultShow, [](Sprite* t){t->x = x * 2;}, 100, 20));

}

void GameInit() {
	LoadImages();
	LoadObject();
}

void Init() {
	myGFactory->Create();
	myText.Create();
	myTextW.Create();
	myGFactory->CreateBrush(blackBrush, _COLOR(Black));
	GameInit();
}

bool Display() {
	keyboard();
	myGFactory->BeginDraw();
	myGFactory->Clear(_COLOR(Gray));
	
	pool.Update();
	pool.Show();
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
