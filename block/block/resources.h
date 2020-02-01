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
Bitmap indexImg(L"./src/char/index.png");
Bitmap reimuBulImg(L"./src/reimubul.png");

Bitmap blockImg[5][6];

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
	BmpInit(maskImg);
	BmpInit(indexImg);
	BmpInit(reimuBulImg);

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
}

Sound titleBgm;
Sound gameBgm;
Sound okSE;
Sound selectSE;
Sound enepSE;
Sound grazeSE;
Sound pldeadSE;
void LoadSound() {
	titleBgm = Sound(L"./src/sound/bgm/menu.mp3");
	gameBgm = Sound(L"./src/sound/bgm/bgm02.mp3");

	okSE = Sound(L"./src/sound/se/se_ok00.wav");
	selectSE = Sound(L"./src/sound/se/se_select00.wav");
	enepSE = Sound(L"./src/sound/se/se_enep00.wav");
	grazeSE = Sound(L"./src/sound/se/se_graze.wav");
	pldeadSE = Sound(L"./src/sound/se/se_pldead00.wav");
}


Brush blackBrush, blueBrush;

/*
Text myText, myTextW;
Text scoreTxt;
std::string textOut;
*/



#endif // !RESOURCES_H
