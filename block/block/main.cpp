#include "block.h"
#include <iostream>
#include <fstream>
bool Display();

Wnd *myWnd = new Wnd(655, 520, Display, _T("Block"));

HWND hwnd;
GFactory *myGFactory = new GFactory(hwnd);
Brush blackBrush, blueBrush;
Text myText, myTextW;
Text scoreTxt;
std::string textOut;
//float oriX = 0, oriY = 0, size = 25;


Bitmap testImg(L"./src/block2.png");
Bitmap boardImg(L"./src/reimu.png");
Bitmap bgImg(L"./src/bg.png");
Bitmap ballRedImg(L"./src/ballred.png");
Bitmap ballBlueImg(L"./src/ballblue.png");
Bitmap ballPurpleImg(L"./src/ballpurple.png");

Bitmap blockImg[5];

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

	for (int i = 1; i <= 4; i++) {
		std::string path;
		path = "./src/block" + std::to_string(i) + ".png";
		blockImg[i] = Bitmap(stringToLPCWSTR(path));
		blockImg[i].Create();
		myGFactory->CreateBitmap(blockImg[i]);
		Block::img[i] = &blockImg[i];
	}
}

auto DefaultShow = [](Sprite* t) {
	myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height);
	
};

auto DefaultUpdate = [](Sprite* t) {};


void BallUpdate(Rotatable* t);
void BoardUpdate(Sprite* t);
Sprite *background = new Sprite(0, 0, bgImg, DefaultShow, [](Sprite* t) {}, 640, 480);

Sprite *board = new Sprite(400, 410, boardImg, DefaultShow, BoardUpdate, 640/6.0, 433/6.0);
Sprite *test = new Sprite(0, 0, testImg, DefaultShow, [](Sprite* t) {t->x = x; t->y = y; }, 30, 30);

Sprite *borderLeft = new Sprite(30-100, 15, boardImg, DefaultShow, DefaultUpdate, 100, 450);
Sprite *borderRight = new Sprite(415, 15, boardImg, DefaultShow, DefaultUpdate, 100, 450);
Sprite *borderUp = new Sprite(30, 15-100, boardImg, DefaultShow, DefaultUpdate, 385, 100);
Sprite *borderDown = new Sprite(30, 465, boardImg, DefaultShow, DefaultUpdate, 385, 2);


void BlockShow(Block* t) {
	if (t->rank > 0) {
		t->image = Block::img[t->rank];
		DefaultShow(t);
	}
	
}

void BlockUpdate(Block *t) {
	if (t->rank <= 0)t->del = true;
}

Block *block1 = new Block(100, 50, BlockShow, BlockUpdate, 4, 100,100);
std::list<Block*> blocks;

double ballSpeed = 5;
double tSpeed = -0.4;
Vec2 ballVelocity(tSpeed, sqrt(1 - tSpeed * tSpeed));//which is always an unit vector
void BallUpdate(Rotatable* t) {
	//update the image for showing
	if (int(t->x + t->y)/40 % 2 == 0)
	t->image = &ballBlueImg;
	else t->image = &ballRedImg;
	
	//hitting the border
	if (isHit(t, borderLeft) || isHit(t, borderRight))ballVelocity.x = -ballVelocity.x;
	if (isHit(t, borderDown) || isHit(t, borderUp))ballVelocity.y = -ballVelocity.y;
	while (isHit(t, borderLeft))t->x += 1;
	while (isHit(t, borderRight))t->x -= 1;

	//hitting the block
	for (auto i = blocks.begin(); i != blocks.end(); i++) 
		if (isHitCircle(t, (*i))) {
			Vec2 normal(Vec2(t->x + 0.5*t->width, t->y + 0.5*t->width)
				- Vec2((*i)->x + 0.5*(*i)->width, (*i)->y + 0.5*(*i)->width));
			Unitize(normal);
			ballVelocity = ballVelocity - 2 * (ballVelocity * normal) * normal;
			while (isHitCircle(t, (*i))) {
				t->x += normal.x;
				t->y += normal.y;
			}
			(*i)->rank--;
			break;
		}
		
	
	

	//hitting the board
	if (isHitCircle(t, board)) {
		Vec2 normal(Vec2(t->x+0.5*t->width,t->y+0.5*t->width)
					- Vec2(board->x+0.5*board->width, board->y+0.5*board->width));
		Unitize(normal);
		ballVelocity = ballVelocity - 2 * (ballVelocity * normal) * normal;
		while (isHitCircle(t, board)) {
			t->x += normal.x;
			t->y += normal.y;
		}
		//ballVelocity.y = -ballVelocity.y;

	}
	
	t->x += ballSpeed * ballVelocity.x;
	t->y += ballSpeed * ballVelocity.y;
	/*
	t->brush->SetTransform(
		D2D1::Matrix3x2F::Translation(x, y)*
		D2D1::Matrix3x2F::Rotation(t->angle, 
			D2D1::Point2F((t->rec1.right + t->rec1.left) / 2 + x, 
			(t->rec1.top + t->rec1.bottom) / 2 + y)));
	HRESULT	hr = myGFactory->GetFactory()->CreateTransformedGeometry(
		t->Grec,
		D2D1::Matrix3x2F::Translation(x, y)*
		D2D1::Matrix3x2F::Rotation(t->angle, 
			D2D1::Point2F((t->rec1.right + t->rec1.left) / 2 + x, 
			(t->rec1.top + t->rec1.bottom) / 2 + y)),
		//D2D1::Point2F(0, 0)),
		&t->Grec2
	);
	*/
}

void BallShow(Rotatable* t) {
	myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height);
	//myGFactory->GetHandle()->FillGeometry(t->Grec2, t->brush);
}

Rotatable *ball = new Rotatable(100, 400, ballRedImg, BallShow, BallUpdate, 20, 20);

void BoardUpdate(Sprite* t) {
	hitLeft = isHit(t, borderLeft);
	hitRight = isHit(t, borderRight);
	t->x = x * 2;
}

void LoadObject() {
	//pool.AddSon(test);
	pool.AddSon(board);
	
	pool.AddSon(borderLeft);
	pool.AddSon(borderRight);
	pool.AddSon(borderUp);
	pool.AddSon(borderDown);

	//pool.AddSon(block1);
	
	std::ifstream in(L"./data/1.blk");
	int num;
	in >> num;
	for (int i = 1; i <= num; i++) {
		float tx, ty;
		int rank;
		in >> tx >> ty >> rank;
		blocks.push_back(new Block(tx, ty, BlockShow, BlockUpdate, rank));
		pool.AddSon(blocks.back());
	}
	

	myGFactory->GetHandle()->CreateBitmapBrush(ball->image->GetBitmap(), &ball->brush);
	myGFactory->GetFactory()->CreateRectangleGeometry(ball->rec1, &(ball->Grec));
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

GameState gameState = GAME;
bool Display() {
	switch (gameState)
	{
	case MENU:

		break;
	case HISCORE:
		break;
	case GAME:
		keyboard();
		myGFactory->BeginDraw();
		myGFactory->Clear(_COLOR(Gray));

		pool.Update();
		pool.Show();
		myTextW.SetRect(10.f + x, 10.f + y, 300.f + x, 150.f + y);

		//myGFactory->WriteW(myTextW, blackBrush, L"½ñÈÕ¤â¤¤¤¤ÌìšÝ¡î");

		textOut = "Position:\nx="
			+ std::to_string(int(50 + x))
			+ "\ny="
			+ std::to_string(int(50 + y))
			+ "\nisHit:"
			+ std::to_string(isHit(board, borderLeft) || isHit(board, borderRight))
			;
		myGFactory->Write(myText, blackBrush, textOut);
		break;
	case QUIT:
		break;
	default:
		break;
	}
	
	return myGFactory->EndDraw();
}

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd->Create(INITPARAMETERS))return 0;
	hwnd = myWnd->GetHandle();
	Init();
	return myWnd->Run();
}
