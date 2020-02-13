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
Bitmap pauseImg;
Bitmap pauseButtonImg[3][2];
Bitmap pauseMaskImg;
Bitmap gameoverImg;

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

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++) {
			std::string path;
			path = "./src/button/p" + std::to_string(i) + std::to_string(j) + ".png";
			pauseButtonImg[i][j] = Bitmap(stringToLPCWSTR(path));
			BmpInit(pauseButtonImg[i][j]);
		}
	pauseImg = Bitmap(L"./src/button/pause.png");
	BmpInit(pauseImg);
	pauseMaskImg = Bitmap(L"./src/button/mask.png");
	BmpInit(pauseMaskImg);
	gameoverImg = Bitmap(L"./src/button/gameover.png");
	BmpInit(gameoverImg);

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
	pachiSImg = Bitmap(L"./src/boss/pachiS.png");
	pachiSCImg = Bitmap(L"./src/boss/pachiSC.png");
	utsuhoSImg = Bitmap(L"./src/boss/utsuhoS.png");
	utsuhoSC1Img = Bitmap(L"./src/boss/utsuhoSC1.png");
	utsuhoSC2Img = Bitmap(L"./src/boss/utsuhoSC2.png");

	normalBG_Img = Bitmap(L"./src/background/bg.png");
	mokouBG_Img = Bitmap(L"./src/background/mokou.png");
	pachiBG_Img = Bitmap(L"./src/background/pachi.png");
	utsuhoBG_Img = Bitmap(L"./src/background/utsuho.png");
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

	endingImg = Bitmap(L"./src/button/ending.png");
	BmpInit(endingImg);
	maskBlackImg = Bitmap(L"./src/button/maskB.png");
	BmpInit(maskBlackImg);

	GameTextBgImg = Bitmap(L"./src/textbg.png");
	BmpInit(GameTextBgImg);
	GameTextLeft = Bitmap(L"./src/boss/reimu/0.png");
	BmpInit(GameTextLeft);
	GameTextRight = Bitmap(L"./src/boss/pachi/0.png");
	BmpInit(GameTextRight);
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
	titleBgm = new Music(L"./src/sound/bgm/menu.mp3", 1.28);
	mokouMidBgm = new Music(L"./src/sound/bgm/bgm01.mp3", 6.21);
	mokouBgm = new Music(L"./src/sound/bgm/bgm02.mp3", 6.52);
	pachiMidBgm = new Music(L"./src/sound/bgm/bgm03.mp3", 0.64);
	pachiBgm = new Music(L"./src/sound/bgm/bgm04.mp3",38.57);
	utsuhoMidBgm = new Music(L"./src/sound/bgm/bgm05.mp3", 0.06);
	utsuhoBgm = new Music(L"./src/sound/bgm/bgm06.mp3", 3.48);
	gameoverBgm = new Music(L"./src/sound/bgm/gameover.mp3");
	endingBgm = new Music(L"./src/sound/bgm/ending.mp3", 0.06);

	okSE = new Sound(L"./src/sound/se/se_ok00.wav");
	selectSE = new Sound(L"./src/sound/se/se_select00.wav");
	enepSE = new Sound(L"./src/sound/se/se_enep00.wav");
	bossepSE = new Sound(L"./src/sound/se/se_enep01.wav");
	tanSE = new Sound(L"./src/sound/se/se_tan00.wav");
	grazeSE = new Sound(L"./src/sound/se/se_graze.wav");
	pldeadSE = new Sound(L"./src/sound/se/se_pldead00.wav");
	plstSE = new Sound(L"./src/sound/se/se_plst00.wav");
	bombSE = new Sound(L"./src/sound/se/se_gun00.wav");

	alertSE = new Sound(L"./src/sound/se/se_alert.wav");
	pauseSE = new Sound(L"./src/sound/se/se_pause.wav");
}



#endif // !RESOURCES_H
