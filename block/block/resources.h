﻿/*						*\
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
#include <vector>

extern GFactory *myGFactory;
extern bool keyDown;
ObjectBuffer gamePool;	//游戏对象池
GameState gameState = LOAD;


Bitmap buttonImg[5][2];
Bitmap pauseImg;
Bitmap pauseButtonImg[3][2];
Bitmap pauseMaskImg;
Bitmap gameoverImg;

Bitmap titleImg;
Bitmap coverImg;
Bitmap reimuImg;
Bitmap pressImg;

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
Bitmap pachiSImg;
Bitmap pachiSCImg;
Bitmap utsuhoSImg;
Bitmap utsuhoSC1Img;
Bitmap utsuhoSC2Img;

Bitmap normalBG_Img;
Bitmap mokouBG_Img;
Bitmap pachiBG_Img;
Bitmap utsuhoBG_Img;
Bitmap mask0Img;
Bitmap mask1Img;

Bitmap endingImg;
Bitmap maskBlackImg;

Bitmap GameTextBgImg;
Bitmap GameTextLeft;
Bitmap GameTextRight;
std::vector<Bitmap*> reimuTextImg;
std::vector<Bitmap*> mokouTextImg;
std::vector<Bitmap*> pachiTextImg;
std::vector<Bitmap*> utsuhoTextImg;

void BmpInit(Bitmap &b) {
	b.Create();
	myGFactory->CreateBitmap(b);
}

void LoadImages() {
	for (int i = 0; i <= 9; i++) {
		std::wstring path;
		path = L"./project/src/char/" + std::to_wstring(i) + L".png";
		GameString::charImg[i + '0'] = Bitmap(path.c_str());
		BmpInit(GameString::charImg[i + '0']);
	}

	for (wchar_t i = 'a'; i <= 'z'; i++) {
		std::wstring path;
		path = std::wstring(L"./project/src/char/") + i + std::wstring(L".png");
		GameString::charImg[i] = Bitmap(path.c_str());
		BmpInit(GameString::charImg[i]);
	}

	GameString::charImg['*'] = Bitmap(L"./project/src/char/star1.png");
	GameString::charImg['#'] = Bitmap(L"./project/src/char/star2.png");
	GameString::charImg['.'] = Bitmap(L"./project/src/char/dot.png");
	BmpInit(GameString::charImg['*']);
	BmpInit(GameString::charImg['#']);
	BmpInit(GameString::charImg['.']);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 2; j++) {
			std::wstring path;
			path = L"./project/src/button/" + std::to_wstring(i) + std::to_wstring(j) + L".png";
			buttonImg[i][j] = Bitmap(path.c_str());
			BmpInit(buttonImg[i][j]);
		}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++) {
			std::wstring path;
			path = L"./project/src/button/p" + std::to_wstring(i) + std::to_wstring(j) + L".png";
			pauseButtonImg[i][j] = Bitmap(path.c_str());
			BmpInit(pauseButtonImg[i][j]);
		}
	pauseImg = Bitmap(L"./project/src/button/pause.png");
	BmpInit(pauseImg);
	pauseMaskImg = Bitmap(L"./project/src/button/mask.png");
	BmpInit(pauseMaskImg);
	gameoverImg = Bitmap(L"./project/src/button/gameover.png");
	BmpInit(gameoverImg);

	titleImg = Bitmap(L"./project/src/menu/title.png");
	coverImg = Bitmap(L"./project/src/menu/cover.png");
	reimuImg = Bitmap(L"./project/src/menu/reimu.png");
	pressImg = Bitmap(L"./project/src/menu/press.png");

	boardImg = Bitmap(L"./project/src/reimu.png");
	bgImg = Bitmap(L"./project/src/bg.png");
	ballRedImg = Bitmap(L"./project/src/ballred.png");
	ballBlueImg = Bitmap(L"./project/src/ballblue.png");
	ballPurpleImg = Bitmap(L"./project/src/ballpurple.png");
	
	indexImg = Bitmap(L"./project/src/char/index.png");
	reimuBulImg = Bitmap(L"./project/src/reimubul.png");
	reimuBombImg = Bitmap(L"./project/src/boss/reimu/b1.png");

	mokouSImg = Bitmap(L"./project/src/boss/mokouS.png");
	mokouSCImg = Bitmap(L"./project/src/boss/mokouSC.png");
	pachiSImg = Bitmap(L"./project/src/boss/pachiS.png");
	pachiSCImg = Bitmap(L"./project/src/boss/pachiSC.png");
	utsuhoSImg = Bitmap(L"./project/src/boss/utsuhoS.png");
	utsuhoSC1Img = Bitmap(L"./project/src/boss/utsuhoSC1.png");
	utsuhoSC2Img = Bitmap(L"./project/src/boss/utsuhoSC2.png");

	normalBG_Img = Bitmap(L"./project/src/background/bg.png");
	mokouBG_Img = Bitmap(L"./project/src/background/mokou.png");
	pachiBG_Img = Bitmap(L"./project/src/background/pachi.png");
	utsuhoBG_Img = Bitmap(L"./project/src/background/utsuho.png");
	mask0Img = Bitmap(L"./project/src/background/mask0.png");
	mask1Img = Bitmap(L"./project/src/background/mask1.png");

	BmpInit(titleImg);
	BmpInit(coverImg);
	BmpInit(reimuImg);
	BmpInit(pressImg);

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
	BmpInit(pachiSImg);
	BmpInit(pachiSCImg);
	BmpInit(utsuhoSImg);
	BmpInit(utsuhoSC1Img);
	BmpInit(utsuhoSC2Img);

	BmpInit(normalBG_Img);
	BmpInit(mokouBG_Img);
	BmpInit(pachiBG_Img);
	BmpInit(utsuhoBG_Img);
	BmpInit(mask0Img);
	BmpInit(mask1Img);

	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 5; j++) {
			std::wstring path;
			path = L"./project/src/block" + std::to_wstring(i * 10 + j) + L".png";
			blockImg[i][j] = Bitmap(path.c_str());
			BmpInit(blockImg[i][j]);
			Block::img[i][j] = &blockImg[i][j];
		}
	for (int i = 1; i <= 5; i++)
		Block::img[0][i] = &blockImg[1][i];

	Boss::HP_Img = Bitmap(L"./project/src/hp.png");
	Boss::mahoujinImg = Bitmap(L"./project/src/boss/mahoujin.png");
	Boss::ringImg = Bitmap(L"./project/src/boss/ring.png");
	BmpInit(Boss::HP_Img);
	BmpInit(Boss::mahoujinImg);
	BmpInit(Boss::ringImg);

	endingImg = Bitmap(L"./project/src/button/ending.png");
	BmpInit(endingImg);
	maskBlackImg = Bitmap(L"./project/src/button/maskB.png");
	BmpInit(maskBlackImg);

	GameTextBgImg = Bitmap(L"./project/src/textbg.png");
	BmpInit(GameTextBgImg);
	GameTextLeft = Bitmap(L"./project/src/boss/reimu/0.png");
	BmpInit(GameTextLeft);
	GameTextRight = Bitmap(L"./project/src/boss/pachi/0.png");
	BmpInit(GameTextRight);

	for (int i = 0; i <= 7; i++) {
		std::wstring path;
		path = L"./project/src/boss/reimu/" + std::to_wstring(i) + L".png";
		reimuTextImg.push_back(new Bitmap(path.c_str()));
		BmpInit(*reimuTextImg[i]);
	}
	for (int i = 0; i <= 5; i++) {
		std::wstring path;
		path = L"./project/src/boss/mokou/" + std::to_wstring(i) + L".png";
		mokouTextImg.push_back(new Bitmap(path.c_str()));
		BmpInit(*mokouTextImg[i]);
	}
	for (int i = 0; i <= 3; i++) {
		std::wstring path;
		path = L"./project/src/boss/pachi/" + std::to_wstring(i) + L".png";
		pachiTextImg.push_back(new Bitmap(path.c_str()));
		BmpInit(*pachiTextImg[i]);
	}
	for (int i = 0; i <= 7; i++) {
		std::wstring path;
		path = L"./project/src/boss/utsuho/" + std::to_wstring(i) + L".png";
		utsuhoTextImg.push_back(new Bitmap(path.c_str()));
		BmpInit(*utsuhoTextImg[i]);
	}
}

Music *titleBgm;
Music *mokouMidBgm;
Music *mokouBgm;
Music *pachiMidBgm;
Music *pachiBgm;
Music *utsuhoMidBgm;
Music *utsuhoBgm;
Music *gameoverBgm;
Music *endingBgm;

Sound *okSE;
Sound *selectSE;
Sound *enepSE;
Sound *bossepSE;
Sound *tanSE;
Sound *grazeSE;
Sound *pldeadSE;
Sound *plstSE;
Sound *bombSE;

Sound *alertSE;
Sound *pauseSE;
void LoadSound() {
	titleBgm = new Music(L"./project/src/sound/bgm/menu.mp3", 1.28);
	mokouMidBgm = new Music(L"./project/src/sound/bgm/bgm01.mp3", 6.21);
	mokouBgm = new Music(L"./project/src/sound/bgm/bgm02.mp3", 6.52);
	pachiMidBgm = new Music(L"./project/src/sound/bgm/bgm03.mp3", 0.64);
	pachiBgm = new Music(L"./project/src/sound/bgm/bgm04.mp3",38.57);
	utsuhoMidBgm = new Music(L"./project/src/sound/bgm/bgm05.mp3", 0.06);
	utsuhoBgm = new Music(L"./project/src/sound/bgm/bgm06.mp3", 3.48);
	gameoverBgm = new Music(L"./project/src/sound/bgm/gameover.mp3");
	endingBgm = new Music(L"./project/src/sound/bgm/ending.mp3", 0.06);

	okSE = new Sound(L"./project/src/sound/se/se_ok00.wav");
	selectSE = new Sound(L"./project/src/sound/se/se_select00.wav");
	enepSE = new Sound(L"./project/src/sound/se/se_enep00.wav");
	bossepSE = new Sound(L"./project/src/sound/se/se_enep01.wav");
	tanSE = new Sound(L"./project/src/sound/se/se_tan00.wav");
	grazeSE = new Sound(L"./project/src/sound/se/se_graze.wav");
	pldeadSE = new Sound(L"./project/src/sound/se/se_pldead00.wav");
	plstSE = new Sound(L"./project/src/sound/se/se_plst00.wav");
	bombSE = new Sound(L"./project/src/sound/se/se_gun00.wav");

	alertSE = new Sound(L"./project/src/sound/se/se_alert.wav");
	pauseSE = new Sound(L"./project/src/sound/se/se_pause.wav");
}



#endif // !RESOURCES_H
