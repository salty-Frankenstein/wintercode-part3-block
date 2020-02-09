/*						*\
		resources.h
	关于图片、音频等游戏资源
	载入相关的facilities
	2020 wintercode
	by id:191220017
\*						*/

#pragma once
#ifndef RESOURCES_H
#define RESOURCES
#include "block.h"
#include <fstream>

extern GFactory *myGFactory;
extern bool keyDown;
ObjectBuffer gamePool;	//游戏对象池
GameState gameState = LOAD;



Bitmap buttonImg[5][2];
Bitmap titleImg;
Bitmap coverImg;
Bitmap reimuImg;
Bitmap pressImg;

Bitmap testImg;
Bitmap boardImg;
Bitmap bgImg;
Bitmap ballRedImg;
Bitmap ballBlueImg;
Bitmap ballPurpleImg;

Bitmap indexImg;
Bitmap reimuBulImg;
Bitmap reimuBombImg;

Bitmap blockImg[5][6];


Bitmap mokouSImg;
Bitmap mokouSCImg;

Bitmap normalBG_Img;
Bitmap mokouBG_Img;
Bitmap mask0Img;
Bitmap mask1Img;

void BmpInit(Bitmap &b) {
	b.Create();
	myGFactory->CreateBitmap(b);
}

void LoadImages() {
	for (int i = 0; i <= 9; i++) {
		std::string path;
		path = "./src/char/" + std::to_string(i) + ".png";
		GameString::charImg[i + '0'] = Bitmap(stringToLPCWSTR(path));
		BmpInit(GameString::charImg[i + '0']);
	}

	for (char i = 'a'; i <= 'z'; i++) {
		std::string path;
		path = std::string("./src/char/") + i + std::string(".png");
		GameString::charImg[i] = Bitmap(stringToLPCWSTR(path));
		BmpInit(GameString::charImg[i]);
	}

	GameString::charImg['*'] = Bitmap(L"./src/char/star1.png");
	GameString::charImg['#'] = Bitmap(L"./src/char/star2.png");
	GameString::charImg['.'] = Bitmap(L"./src/char/dot.png");
	BmpInit(GameString::charImg['*']);
	BmpInit(GameString::charImg['#']);
	BmpInit(GameString::charImg['.']);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 2; j++) {
			std::string path;
			path = "./src/button/" + std::to_string(i) + std::to_string(j) + ".png";
			buttonImg[i][j] = Bitmap(stringToLPCWSTR(path));
			BmpInit(buttonImg[i][j]);
		}

	titleImg = Bitmap(L"./src/menu/title.png");
	coverImg = Bitmap(L"./src/menu/cover.png");
	reimuImg = Bitmap(L"./src/menu/reimu.png");
	pressImg = Bitmap(L"./src/menu/press.png");

	testImg = Bitmap(L"./src/enemy1.png");
	boardImg = Bitmap(L"./src/reimu.png");
	bgImg = Bitmap(L"./src/bg.png");
	ballRedImg = Bitmap(L"./src/ballred.png");
	ballBlueImg = Bitmap(L"./src/ballblue.png");
	ballPurpleImg = Bitmap(L"./src/ballpurple.png");
	
	indexImg = Bitmap(L"./src/char/index.png");
	reimuBulImg = Bitmap(L"./src/reimubul.png");
	reimuBombImg = Bitmap(L"./src/boss/reimu/b1.png");

	mokouSImg = Bitmap(L"./src/boss/mokouS.png");
	mokouSCImg = Bitmap(L"./src/boss/mokouSC.png");

	normalBG_Img = Bitmap(L"./src/background/bg.png");
	mokouBG_Img = Bitmap(L"./src/background/mokou.png");
	mask0Img = Bitmap(L"./src/background/mask0.png");
	mask1Img = Bitmap(L"./src/background/mask1.png");

	BmpInit(titleImg);
	BmpInit(coverImg);
	BmpInit(reimuImg);
	BmpInit(pressImg);

	BmpInit(testImg);
	BmpInit(boardImg);
	BmpInit(bgImg);
	BmpInit(ballRedImg);
	BmpInit(ballBlueImg);
	BmpInit(ballPurpleImg);
	
	BmpInit(indexImg);
	BmpInit(reimuBulImg);
	BmpInit(reimuBombImg);
	
	BmpInit(mokouSImg);
	BmpInit(mokouSCImg);

	BmpInit(normalBG_Img);
	BmpInit(mokouBG_Img);
	BmpInit(mask0Img);
	BmpInit(mask1Img);

	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 5; j++) {
			std::string path;
			path = "./src/block" + std::to_string(i * 10 + j) + ".png";
			blockImg[i][j] = Bitmap(stringToLPCWSTR(path));
			BmpInit(blockImg[i][j]);
			Block::img[i][j] = &blockImg[i][j];
		}
	for (int i = 1; i <= 5; i++)
		Block::img[0][i] = &blockImg[1][i];

	Boss::HP_Img = Bitmap(L"./src/hp.png");
	Boss::mahoujinImg = Bitmap(L"./src/boss/mahoujin.png");
	Boss::ringImg = Bitmap(L"./src/boss/ring.png");
	BmpInit(Boss::HP_Img);
	BmpInit(Boss::mahoujinImg);
	BmpInit(Boss::ringImg);
}

Sound *titleBgm;
Sound *gameBgm;
Sound *okSE;
Sound *selectSE;
Sound *enepSE;
Sound *bossepSE;
Sound *tanSE;
Sound *grazeSE;
Sound *pldeadSE;
Sound *plstSE;
Sound *bombSE;
void LoadSound() {
	titleBgm = new Sound(L"./src/sound/bgm/menu.mp3");
	gameBgm = new Sound(L"./src/sound/bgm/bgm02.mp3");

	okSE = new Sound(L"./src/sound/se/se_ok00.wav");
	selectSE = new Sound(L"./src/sound/se/se_select00.wav");
	enepSE = new Sound(L"./src/sound/se/se_enep00.wav");
	bossepSE = new Sound(L"./src/sound/se/se_enep01.wav");
	tanSE = new Sound(L"./src/sound/se/se_tan00.wav");
	grazeSE = new Sound(L"./src/sound/se/se_graze.wav");
	pldeadSE = new Sound(L"./src/sound/se/se_pldead00.wav");
	plstSE = new Sound(L"./src/sound/se/se_plst00.wav");
	bombSE = new Sound(L"./src/sound/se/se_gun00.wav");
}


Brush blackBrush, blueBrush;

/*
Text myText, myTextW;
Text scoreTxt;
std::string textOut;
*/



#endif // !RESOURCES_H
