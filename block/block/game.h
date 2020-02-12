/*					*\
		game.h
	游戏界面相关代码
	2020 wintercode
	by id:191220017
\*					*/

#pragma once
#ifndef GAME_H
#define GAME_H

#include "resources.h"
#include "stage.h"
#include "background.h"

int hiScore = 0;
int gameScore = 0;
int gameLife;
int gameBomb;

extern bool ballActive;
Stage *stageNow = nullptr;
extern GameProcess gameProcess;
void keyboard(GameState &state) {
	static unsigned long long keyDownTime = 0;

	switch (state)
	{
	case MENU:
		if (!(getKey[VK_UP] || getKey[VK_DOWN] || getKey['Z']))keyDownTime = gameTimer;
		if ((gameTimer - keyDownTime) % 10 == 1) {
			if (getKey[VK_UP])
				menuButtonOn = (menuButtonOn + 4) % 5;
			if (getKey[VK_DOWN])
				menuButtonOn = (menuButtonOn + 1) % 5;
			if (getKey['Z'] && isMenu) pressedEnter = true;
		}
		break;
	case SELECT:
		break;
	case HISCORE:
		break;
	case GAME:
		if (gameLife < 0) {
			if (!(getKey[VK_UP] || getKey[VK_DOWN] || getKey['Z']))keyDownTime = gameTimer;
			if(pauseButtonOn == 0)pauseButtonOn = 1;
			if ((gameTimer - keyDownTime) % 10 == 1) {
				if (getKey[VK_UP] || getKey[VK_DOWN]) {
					if (pauseButtonOn == 1)pauseButtonOn = 2;
					else pauseButtonOn = 1;
				}
				if (getKey['Z']) pressedEnter = true;
			}
		}
		else if (gameProcess == GAME_PLAY) {
			if (getKey[VK_SPACE] && stageNow->textPtr->IsOver())
				ballActive = true;
			if (getKey[VK_ESCAPE]) {
				pauseSE->Play();
				gameProcess = GAME_PAUSE;
			}
		}
		else if (gameProcess == GAME_PAUSE) {
			if (!(getKey[VK_UP] || getKey[VK_DOWN] || getKey['Z']))keyDownTime = gameTimer;
			if ((gameTimer - keyDownTime) % 10 == 1) {
				if (getKey[VK_UP])
					pauseButtonOn = (pauseButtonOn + 2) % 3;
				if (getKey[VK_DOWN])
					pauseButtonOn = (pauseButtonOn + 1) % 3;
				if (getKey['Z']) pressedEnter = true;
			}
		}
		
		break;
	case QUIT:
		break;
	default:
		break;
	}

}

GameString* hiScoreStr = new GameString(500, 30, 0.48, 5);
GameString* gameScoreStr = new GameString(500, 55, 0.48, 5);
GameString* gameLifeStr = new GameString(500, 102, 0.48, 5, 5);
GameString* gameBombStr = new GameString(500, 127, 0.48, 5, 5);
GameString* objNumStr = new GameString(0, 0, 0.48, 5);

void BallUpdate(Rotatable* t);
void BoardUpdate(Sprite* t);
Sprite *background = new Sprite(0, 0, bgImg, DefaultShow, [](Sprite* t) {}, 640, 480, 3);

Sprite *board = new Sprite(400, 410, boardImg, DefaultShow, BoardUpdate, 640 / 6.0, 433 / 6.0);
Sprite *test = new Sprite(0, 0, testImg, DefaultShow, [](Sprite* t) {t->x = x; t->y = y; }, 30, 30);

Sprite *borderLeft = new Sprite(30 - 100, 15, boardImg, INVISIBLE_SHOW, DefaultUpdate, 100, 450);
Sprite *borderRight = new Sprite(415, 15, boardImg, INVISIBLE_SHOW, DefaultUpdate, 100, 450);
Sprite *borderUp = new Sprite(30, 15 - 100, boardImg, INVISIBLE_SHOW, DefaultUpdate, 385, 100);
//Sprite *borderDown = new Sprite(30, 465, boardImg, INVISIBLE_SHOW, DefaultUpdate, 385, 2);


double ballSpeed = 5;
double tSpeed = -0.4;
Vec2 ballVelocity(tSpeed, sqrt(1 - tSpeed * tSpeed));//which is always an unit vector
void BallUpdate(Rotatable* t) {
	//update the image for showing
	if ((gameTimer) / 10 % 2 == 0)
		t->image = &ballBlueImg;
	else t->image = &ballRedImg;
	if (!ballActive) {
		t->x = board->x + board->width * 0.5 - 10;
		t->y = board->y - 20;
		return;
	}
	//hitting the border
	if (isHit(t, borderLeft) || isHit(t, borderRight)) {
		grazeSE->Play();
		ballVelocity.x = -ballVelocity.x;
	}
	if (isHit(t, borderUp)) {
		grazeSE->Play();
		ballVelocity.y = -ballVelocity.y;
	}

	while (isHit(t, borderLeft))t->x += 1;
	while (isHit(t, borderRight))t->x -= 1;
	while (isHit(t, borderUp))t->y += 1;

	//hitting the block
	for (auto i = stageNow->GetBlocksBegin(); i != stageNow->GetBlocksEnd(); i++)
		if ((*i)->rank > 0 && isHitCircle(t, (*i))) {
			grazeSE->Play();
			Vec2 normal(Vec2(t->x + 0.5*t->width, t->y + 0.5*t->width)
				- Vec2((*i)->x + 0.5*(*i)->width, (*i)->y + 0.5*(*i)->width));
			Unitize(normal);
			ballVelocity = ballVelocity - 2 * (ballVelocity * normal) * normal;
			while (isHitCircle(t, (*i))) {
				t->x += normal.x;
				t->y += normal.y;
			}
			(*i)->rank--;
			gameScore += 1000;
			if ((*i)->rank <= 0)gameScore += 2000;	//消灭额外得分
			
			break;
		}

	//hitting the boss
	if (stageNow->boss != nullptr && isHitCircle(t, stageNow->boss)) {
		grazeSE->Play();
		Vec2 normal(Vec2(t->x + 0.5*t->width, t->y + 0.5*t->width)
			- Vec2(stageNow->boss->x + 0.5*stageNow->boss->width, stageNow->boss->y + 0.5*stageNow->boss->width));
		Unitize(normal);
		ballVelocity = ballVelocity - 2 * (ballVelocity * normal) * normal;
		while (isHitCircle(t, stageNow->boss)) {
			t->x += normal.x;
			t->y += normal.y;
		}
		gameScore += 10000;
		stageNow->boss->HP_now -= 30;
	}

	//hitting the board
	if (isHitCircle(t, board)) {
		grazeSE->Play();
		Vec2 normal(Vec2(t->x + 0.5*t->width, t->y + 0.5*t->width)
			- Vec2(board->x + 0.5*board->width, board->y + 0.5*board->width));
		Unitize(normal);
		ballVelocity = ballVelocity - 2 * (ballVelocity * normal) * normal;
		while (isHitCircle(t, board)) {
			t->x += normal.x;
			t->y += normal.y;
		}
	}

	t->x += ballSpeed * ballVelocity.x;
	t->y += ballSpeed * ballVelocity.y;
	
}


void BallShow(Rotatable* t) {
	
}

Rotatable *ball = new Rotatable(100, 400, ballRedImg, BallShow, BallUpdate, 20, 20, 1, 1, 0, 15);

auto PlayerBulUpdate = [](Sprite* t) {
	t->y -= 20;
	if (t->y < 0)t->del = true;
	if (isHitCircle(t, ball)) {
		t->del = true;
		double x = 2*((ball->x + ball->width*0.5) - (t->x + t->width * 0.5))/abs(ball->width + t->width);
		ballVelocity = Vec2(x, -sqrt(1 - x * x));
		while (isHitCircle(t, ball)) {
			t->y -= 1;
		}
	}

	//hitting the boss
	if (stageNow->boss!=nullptr && isHitCircle(t, stageNow->boss) && !bombOn) {
		t->del = true;
		gameScore += 10;
		stageNow->boss->HP_now -= 1;
	}
};

auto PlayerBombUpdate = [](Rotatable* t) {
	ballVelocity.x = 0;
	ballVelocity.y = -1;
	t->y -= 5;
	t->x -= 0.5;
	t->width += 1;
	t->height += 1;
	if (!bombHitted && t->y < 100) {
		for (auto i = stageNow->GetBlocksBegin(); i != stageNow->GetBlocksEnd(); i++) {
			(*i)->rank--;
			gameScore += 1000;
			if ((*i)->rank <= 0)gameScore += 2000;	//消灭额外得分
		}
		if (stageNow->boss != nullptr)
			stageNow->boss->HP_now -= 100;
		bombHitted = true;
	}
	if (t->y < -500) {
		t->del = true;
		bombOn = false;
	}
};

void BoardUpdate(Sprite* t) {
	hitLeft = isHit(t, borderLeft);
	hitRight = isHit(t, borderRight);
	//t->x = x;

	//shoot bullet
	if (getKey['Z'] && gameTimer % 5 == 0 && ballActive) {
		plstSE->Play();
		gamePool.AddSon(
			new Sprite(t->x + t->width*0.5 - 12 * 1.2 * 0.5 + 10, t->y, reimuBulImg,
				DefaultShow, PlayerBulUpdate, 12*1.2, 64*1.2, 1, 0.5)
		);
		gamePool.AddSon(
			new Sprite(t->x + t->width*0.5 - 12 * 1.2 * 0.5 - 10, t->y, reimuBulImg,
				DefaultShow, PlayerBulUpdate, 12 * 1.2, 64 * 1.2, 1, 0.5)
		);
		gamePool.Sort();
	}

	//bomb
	if (getKey['X'] && !bombOn && ballActive && gameBomb > 0) {
		bombSE->Play();
		bombOn = true;
		bombHitted = false;
		gameBomb--;
		gameBombStr->str = "";
		for (int i = 1; i <= gameBomb; i++)
			gameBombStr->str += "#";
		gamePool.AddSon(new Rotatable(130, 410, reimuBombImg, [](Rotatable* t) {}, PlayerBombUpdate, 200, 200, 2, 0.7, 0, 10));
		gamePool.AddSon(new Rotatable(130+25, 410 + 100, reimuBombImg, [](Rotatable* t) {}, PlayerBombUpdate, 150, 150, 2, 0.6, 30, 8));
		gamePool.AddSon(new Rotatable(130+50, 410 + 150, reimuBombImg, [](Rotatable* t) {}, PlayerBombUpdate, 100, 100, 2, 0.5, 60, 6));
		gamePool.Sort();
	}

	if (getKey[VK_LEFT] && !hitLeft && gameLife >= 0)
		t->x -= 10;
	if (getKey[VK_RIGHT] && !hitRight && gameLife >= 0)
		t->x += 10;
	if (stageNow->GetStageNum() == 9 && stageNow->boss->HP_now < stageNow->boss->HP_max * 0.5) {
		if (t->x > stageNow->boss->x) t->x -= 2;
		else t->x += 2;
	}
}


Sprite* index = new Sprite(430, 30, indexImg, DefaultShow, DefaultUpdate, 131 * 0.5, 320 * 0.5, 4);

void LoadGame() {
	gamePool.AddSon(board);

	gamePool.AddSon(borderLeft);
	gamePool.AddSon(borderRight);
	gamePool.AddSon(borderUp);
	//gamePool.AddSon(borderDown);

	
	gamePool.AddSon(ball);
	gamePool.AddSon(background);
	gamePool.AddSon(index);

	gamePool.AddSon(hiScoreStr);
	gamePool.AddSon(gameScoreStr);
	gamePool.AddSon(gameLifeStr);
	gamePool.AddSon(gameBombStr);
	

	gamePool.AddSon(objNumStr);

}


void GameLoad() {
	static bool loaded = false;
	if (!loaded) {
		//loaded = true;
		delete stageNow;
		stageNow = new Stage;
	}
	
	std::ifstream in(L"./data/hiscore.dat");
	in >> hiScore;
	hiScoreStr->SetNum(hiScore);
	gameScore = 0;
	gameScoreStr->SetNum(gameScore);
	gameLife = 2;
	gameBomb = 3;
	gameProcess = GAME_LOAD;
	mokouMidBgm->Stop();
	mokouBgm->Stop();
	pachiMidBgm->Stop();
	pachiBgm->Stop();
	utsuhoMidBgm->Stop();
	utsuhoBgm->Stop();
}


//GameString* paused = new GameString(100, 230, 0.8, 5);
Background myBackground;
void GameUpdate() {
	switch (gameProcess)
	{
	case GAME_LOAD:

		stageNow->Next();
		stageNow->Load();
		myBackground.Load(stageNow->GetStageNum());
		gameProcess = GAME_RESTART;
		break;
	case GAME_RESTART:
		board->x = 190;
		ballActive = false;
		ballVelocity.x = 0;
		ballVelocity.y = -1;
		gameLifeStr->str = "";
		for (int i = 1; i <= gameLife; i++)
			gameLifeStr->str += "*";

		gameBombStr->str = "";
		for (int i = 1; i <= gameBomb; i++)
			gameBombStr->str += "#";

		gameProcess = GAME_PLAY;
		break;
	case GAME_PLAY:
		gameScoreStr->SetNum(gameScore);
		if (gameScore > hiScore) {
			hiScore = gameScore;
			hiScoreStr->SetNum(hiScore);
		}
		if (ball->y > 600 - 100) {
			pldeadSE->Play();
			gameLife--;
			if(gameLife > 0)gameBomb = 3;
			gameProcess = GAME_RESTART;
		}
		if (stageNow->IsOver()) {
			gameProcess = GAME_LOAD;
			ballActive = false;
		}
		break;
	case GAME_PAUSE:
		//paused->str = "game.paused";
		//paused->Show();
		break;
	case GAME_END:
		break;
	default:
		break;
	}
	
}

#endif // !GAME_H
