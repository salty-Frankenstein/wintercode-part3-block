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
GameState gameState = MENU;
int hiScore = 0;
int gameScore = 0;


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

Bitmap blockImg[5][6];

void LoadImages() {
	for (int i = 0; i <= 9; i++) {
		std::string path;
		path = "./src/char/" + std::to_string(i) + ".png";
		GameString::charImg[i + '0'] = Bitmap(stringToLPCWSTR(path));
		GameString::charImg[i + '0'].Create();
		myGFactory->CreateBitmap(GameString::charImg[i + '0']);
	}

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
	indexImg.Create();

	myGFactory->CreateBitmap(testImg);
	myGFactory->CreateBitmap(boardImg);
	myGFactory->CreateBitmap(bgImg);
	myGFactory->CreateBitmap(ballRedImg);
	myGFactory->CreateBitmap(ballBlueImg);
	myGFactory->CreateBitmap(ballPurpleImg);
	myGFactory->CreateBitmap(maskImg);
	myGFactory->CreateBitmap(indexImg);

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

/*
Brush blackBrush, blueBrush;
Text myText, myTextW;
Text scoreTxt;
std::string textOut;
*/

#endif // !RESOURCES_H
