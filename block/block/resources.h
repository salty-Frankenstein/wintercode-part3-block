#pragma once
#ifndef RESOURCES_H
#define RESOURCES
#include "block.h"
#include <fstream>

extern GFactory *myGFactory;
extern bool keyDown;
ObjectBuffer pool;	//”Œœ∑∂‘œÛ≥ÿ
GameState gameState = MENU;


Bitmap buttonImg[5][2];
Bitmap titleImg(L"./src/menu/title.png");
Bitmap coverImg(L"./src/menu/cover.png");
Bitmap reimuImg(L"./src/menu/reimu.png");
Bitmap pressImg(L"./src/menu/press.png");

Bitmap testImg(L"./src/enemy1.png");
Bitmap boardImg(L"./src/reimu.png");
Bitmap bgImg(L"./src/bg.png");
Bitmap ballRedImg(L"./src/ballred.png");
Bitmap ballBlueImg(L"./src/ballblue.png");
Bitmap ballPurpleImg(L"./src/ballpurple.png");
Bitmap maskImg(L"./src/mask.png");

Bitmap blockImg[5][6];

void LoadImages() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 2; j++) {
			std::string path;
			path = "./src/button/" + std::to_string(i) + std::to_string(j) + ".png";
			buttonImg[i][j] = Bitmap(stringToLPCWSTR(path));
			buttonImg[i][j].Create();
			myGFactory->CreateBitmap(buttonImg[i][j]);
		}
	titleImg.Create();
	coverImg.Create();
	reimuImg.Create();
	pressImg.Create();
	myGFactory->CreateBitmap(titleImg);
	myGFactory->CreateBitmap(coverImg);
	myGFactory->CreateBitmap(reimuImg);
	myGFactory->CreateBitmap(pressImg);

	testImg.Create();
	boardImg.Create();
	bgImg.Create();
	ballRedImg.Create();
	ballBlueImg.Create();
	ballPurpleImg.Create();
	maskImg.Create();

	myGFactory->CreateBitmap(testImg);
	myGFactory->CreateBitmap(boardImg);
	myGFactory->CreateBitmap(bgImg);
	myGFactory->CreateBitmap(ballRedImg);
	myGFactory->CreateBitmap(ballBlueImg);
	myGFactory->CreateBitmap(ballPurpleImg);
	myGFactory->CreateBitmap(maskImg);

	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 5; j++) {
			std::string path;
			path = "./src/block" + std::to_string(i * 10 + j) + ".png";
			blockImg[i][j] = Bitmap(stringToLPCWSTR(path));
			blockImg[i][j].Create();
			myGFactory->CreateBitmap(blockImg[i][j]);
			Block::img[i][j] = &blockImg[i][j];
		}
}

Brush blackBrush, blueBrush;
Text myText, myTextW;
Text scoreTxt;
std::string textOut;


Sprite *cover = new Sprite(0, 0, coverImg, DefaultShow, DefaultUpdate, 640, 480);
Sprite *reimu = new Sprite(300, 0, reimuImg, DefaultShow, DefaultUpdate, 333, 457);
Sprite *title = new Sprite(100, 0, titleImg, DefaultShow, DefaultUpdate, 335 * 1.25, 91 * 1.25);
Sprite *press = new Sprite(200 + 15 * 0.5, 350, pressImg, DefaultShow, DefaultUpdate, 225, 27);

auto ButtonShow = [](Button* t) {
	if (t->is_on)myGFactory->DrawBitmap(*(t->onImage), t->x, t->y, t->x + t->width, t->y + t->height);
	else myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height);
};

void ButtonUpdate(Button* t) {
	if (!t->isActive)return;
	if (t->is_on) {
		if (!t->stop) {
			if (gameTimer - t->time <= 3)
				t->x -= 2;
			else if (gameTimer - t->time <= 6)
				t->x += 2;
			else if (gameTimer - t->time <= 8)
				t->x += 2;
			else if (gameTimer - t->time <= 10)
				t->x -= 3;
			else t->stop = true;
		}
	}
	else {
		t->x = 450;
		t->stop = false;
		t->time = gameTimer;
	}

}


enum MenuButton { B_GAME_START, B_PLAYER_DATA, B_MUSIC_ROOM, B_OPTION, B_QUIT };
Button *menuButtons[5];
/*
Button *gameStart = new Button(450 + 300, 200, buttonImg[0][0], buttonImg[0][1], ButtonShow, [](Button* t) {}, 143, 27);
Button *playerData = new Button(450 + 300, 235, buttonImg[1][0], buttonImg[1][1], ButtonShow, [](Button* t) {}, 140, 33);
Button *musicRoom = new Button(450 + 300, 270, buttonImg[2][0], buttonImg[2][1], ButtonShow, [](Button* t) {}, 150, 27);
Button *option = new Button(450 + 300, 305, buttonImg[3][0], buttonImg[3][1], ButtonShow, [](Button* t) {}, 89, 33);
Button *quit = new Button(450 + 300, 340, buttonImg[4][0], buttonImg[4][1], ButtonShow, [](Button* t) {}, 53, 30);
*/

void BallUpdate(Rotatable* t);
void BoardUpdate(Sprite* t);
Sprite *background = new Sprite(0, 0, bgImg, DefaultShow, [](Sprite* t) {}, 640, 480);

Sprite *board = new Sprite(400, 410, boardImg, DefaultShow, BoardUpdate, 640 / 6.0, 433 / 6.0);
Sprite *test = new Sprite(0, 0, testImg, DefaultShow, [](Sprite* t) {t->x = x; t->y = y; }, 30, 30);

Sprite *borderLeft = new Sprite(30 - 100, 15, boardImg, INVISIBLE_SHOW, DefaultUpdate, 100, 450);
Sprite *borderRight = new Sprite(415, 15, boardImg, INVISIBLE_SHOW, DefaultUpdate, 100, 450);
Sprite *borderUp = new Sprite(30, 15 - 100, boardImg, INVISIBLE_SHOW, DefaultUpdate, 385, 100);
Sprite *borderDown = new Sprite(30, 465, boardImg, INVISIBLE_SHOW, DefaultUpdate, 385, 2);

//Block *block1 = new Block(100, 50, BlockShow, BlockUpdate, 4, 100,100);
std::list<Block*> blocks;

double ballSpeed = 5;
double tSpeed = -0.4;
Vec2 ballVelocity(tSpeed, sqrt(1 - tSpeed * tSpeed));//which is always an unit vector
void BallUpdate(Rotatable* t) {
	//update the image for showing
	if ((gameTimer) / 10 % 2 == 0)
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
		Vec2 normal(Vec2(t->x + 0.5*t->width, t->y + 0.5*t->width)
			- Vec2(board->x + 0.5*board->width, board->y + 0.5*board->width));
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
	//pc0myGFactory->GetHandle()->FillGeometry(t->Grec, t->brush);
}

Rotatable *ball = new Rotatable(100, 400, ballRedImg, BallShow, BallUpdate, 20, 20);

void BoardUpdate(Sprite* t) {
	hitLeft = isHit(t, borderLeft);
	hitRight = isHit(t, borderRight);
	t->x = x * 2;
}

Sprite* mask = new Sprite(0, 0, maskImg, DefaultShow, DefaultUpdate, 600, 600);


ObjectBuffer menuUI_Pool;
void LoadMenuUI() {
	menuUI_Pool.AddSon(cover);
	menuUI_Pool.AddSon(reimu);
	menuUI_Pool.AddSon(title);
	menuUI_Pool.AddSon(press);
	/*
	menuUI_Pool.AddSon(gameStart);
	menuUI_Pool.AddSon(playerData);
	menuUI_Pool.AddSon(musicRoom);
	menuUI_Pool.AddSon(option);
	menuUI_Pool.AddSon(quit);
	*/
}

void LoadMenuButton() {
	menuButtons[B_GAME_START] = new Button(450 + 300, 200, buttonImg[0][0], buttonImg[0][1], ButtonShow, ButtonUpdate, 143, 27);
	menuButtons[B_PLAYER_DATA] = new Button(450 + 300, 235, buttonImg[1][0], buttonImg[1][1], ButtonShow, ButtonUpdate, 140, 33);
	menuButtons[B_MUSIC_ROOM] = new Button(450 + 300, 270, buttonImg[2][0], buttonImg[2][1], ButtonShow, ButtonUpdate, 150, 27);
	menuButtons[B_OPTION] = new Button(450 + 300, 305, buttonImg[3][0], buttonImg[3][1], ButtonShow, ButtonUpdate, 89, 33);
	menuButtons[B_QUIT] = new Button(450 + 300, 340, buttonImg[4][0], buttonImg[4][1], ButtonShow, ButtonUpdate, 53, 30);
	for (int i = 0; i <= 4; i++) {
		menuUI_Pool.AddSon(menuButtons[i]);
	}
}

extern int menuButtonOn;
extern bool pressedEnter;
void MenuUI_Update() {
	static bool pressed = false;
	static bool menu = false;
	static bool loaded = false;
	static unsigned long long pressTime = 0;
	if (!menu) {	//title
		if (gameTimer <= 60) {
			reimu->x -= 6 - gameTimer * 0.1;
			title->y += 6 - gameTimer * 0.1;
		}
		if (gameTimer / 30 % 2) {
			press->x += 0.5;
		}
		else {
			press->x -= 0.5;
		}

		if (gameTimer > 60 && keyDown) {
			pressed = true;
			press->del = true;
		}

		if(!pressed){
			pressTime = gameTimer;
		}
		else {
			if (!loaded) {
				LoadMenuButton();
				menuButtons[menuButtonOn]->is_on = true;
				//gameStart->is_on = true;
				loaded = true;
			}
			if (gameTimer - pressTime <= 30) {
				reimu->x -= (6 - (gameTimer - pressTime) * 0.1)*0.9;
				title->x -= (6 - (gameTimer - pressTime) * 0.1)*0.7;
				title->width -= 335 * 0.005;
				title->height -= 91 * 0.005;
				for (int i = 0; i <= 4; i++) {
					menuButtons[i]->x -= 10;
				}
			}
			else {
				for (int i = 0; i <= 4; i++) {
					menuButtons[i]->isActive = true;
				}
				menu = true;
			}
		}
			
	}
	else {	//menu
		for (int i = 0; i <= 4; i++) {
			if(i == menuButtonOn)
				menuButtons[i]->is_on = 1;
			else menuButtons[i]->is_on = 0;
		}
		if (pressedEnter) {
			switch (menuButtonOn)
			{
			case 0:
				gameState = GAME;
				break;
			case 4:
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}
	}
	
}

void LoadObject() {


	//pool.AddSon(test);
	pool.AddSon(mask);
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


	HRESULT t1 = myGFactory->GetHandle()->CreateBitmapBrush(ball->image->GetBitmap(), &ball->brush);
	HRESULT t2 = myGFactory->GetFactory()->CreateRectangleGeometry(ball->rec1, &(ball->Grec));
	//if (SUCCEEDED(t1) && SUCCEEDED(t2))
	pool.AddSon(background);
	pool.AddSon(ball);
}

void GameInit() {
	LoadImages();
	LoadMenuUI();
	LoadObject();
}


#endif // !RESOURCES_H
