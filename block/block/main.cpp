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
Bitmap boardImg(L"./src/reimu.png");
Bitmap bgImg(L"./src/bg.png");
Bitmap ballRedImg(L"./src/ballred.png");
Bitmap ballBlueImg(L"./src/ballblue.png");
Bitmap ballPurpleImg(L"./src/ballpurple.png");



void LoadImages() {
	testImg.Create();
	boardImg.Create();
	bgImg.Create();
	ballRedImg.Create();
	ballBlueImg.Create();
	ballPurpleImg.Create();
	myGFactory->CreateBitmap(testImg);
	myGFactory->CreateBitmap(boardImg);
	myGFactory->CreateBitmap(bgImg);
	myGFactory->CreateBitmap(ballRedImg);
	myGFactory->CreateBitmap(ballBlueImg);
	myGFactory->CreateBitmap(ballPurpleImg);
}

auto DefaultShow = [](Sprite* t) {
	myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height);
	
};

auto DefaultUpdate = [](Sprite* t) {};



void BallUpdate(Sprite* t);
void BoardUpdate(Sprite* t);
Sprite *background = new Sprite(0, 0, bgImg, DefaultShow, [](Sprite* t) {}, 640, 480);


Sprite *board = new Sprite(400, 400, boardImg, DefaultShow, BoardUpdate, 100, 80);
Sprite *test = new Sprite(0, 0, testImg, DefaultShow, [](Sprite* t) {t->x = x; t->y = y; }, 30, 30);

Sprite *borderLeft = new Sprite(30, 15, boardImg, DefaultShow, DefaultUpdate, 2, 450);
Sprite *borderRight = new Sprite(415, 15, boardImg, DefaultShow, DefaultUpdate, 2, 450);
Sprite *borderUp = new Sprite(30, 15, boardImg, DefaultShow, DefaultUpdate, 385, 2);
Sprite *borderDown = new Sprite(30, 465, boardImg, DefaultShow, DefaultUpdate, 385, 2);

void BoardUpdate(Sprite* t) {
	hitLeft = isHit(t, borderLeft);
	hitRight = isHit(t, borderRight);
	t->x = x * 2;
}

double ballSpeed = 1;
double tSpeed = -0.4;
Point ballVelocity(tSpeed, sqrt(1 - tSpeed * tSpeed));

void BallUpdate(Sprite* t) {

	
	if (int(t->x + t->y)/40 % 2 == 0)
	t->image = &ballBlueImg;
	else t->image = &ballRedImg;
	
	if (isHit(t, borderLeft) || isHit(t, borderRight))ballVelocity.x = -ballVelocity.x;
	if (isHit(t, borderDown) || isHit(t, borderUp))ballVelocity.y = -ballVelocity.y;

	if (isHit(t, board)) {
		ballVelocity.y = -ballVelocity.y;
	}
	t->x += ballSpeed * ballVelocity.x;
	t->y += ballSpeed * ballVelocity.y;
}
/*
void BallShow(Sprite* t) {
	myGFactory->GetHandle()->FillGeometry();
}
*/
Rotatable *ball = new Rotatable(100, 100, ballRedImg, DefaultShow, BallUpdate, 20, 20);


void LoadObject() {
	
	
	pool.AddSon(test);
	pool.AddSon(board);
	
	pool.AddSon(borderLeft);
	pool.AddSon(borderRight);
	pool.AddSon(borderUp);
	pool.AddSon(borderDown);

	pool.AddSon(ball);
	pool.AddSon(background);
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
	+ std::to_string(int(50 + y))
	+ "\nisHit:"
	+ std::to_string(isHit(board, borderLeft) || isHit(board, borderRight))
	;
	myGFactory->Write(myText, blackBrush, textOut);
	
	
	return myGFactory->EndDraw();
}

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();
	Init();
	return myWnd->Run();
}
