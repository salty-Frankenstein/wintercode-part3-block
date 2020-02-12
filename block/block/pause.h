/*						*\
		pause.h
	暂停界面相关代码
	2020 wintercode
	by id:191220017
\*						*/

#pragma once
#ifndef PAUSE_H
#define PAUSE_H

#include "resources.h"

enum PauseButton { B_GAME, B_TITLE, B_RETRY };
Button *pauseButtons[3];
Sprite *pause, *pauseMask;
ObjectBuffer pauseUI_Pool;

void MenuButtonShow(Button* t) {
	if (t->is_on)myGFactory->DrawBitmap(*(t->onImage), t->x, t->y, t->x + t->width, t->y + t->height);
	else myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height);
};

void LoadPauseButton() {
	static bool loaded = false;
	if (!loaded) {
		pauseMask = new Sprite(31.5, 15, pauseMaskImg, DefaultShow, DefaultUpdate, 415-30, 465-15, 1, 0.5);
		pauseUI_Pool.AddSon(pauseMask);

		pauseButtons[B_GAME] = new Button(150, 225,
			pauseButtonImg[0][0], pauseButtonImg[0][1], MenuButtonShow, [](Button* t) {}, 244 * 0.6, 61 * 0.6);
		pauseButtons[B_TITLE] = new Button(125, 225 + 45,
			pauseButtonImg[1][0], pauseButtonImg[1][1], MenuButtonShow, [](Button* t) {}, 338 * 0.6, 55 * 0.6);
		pauseButtons[B_RETRY] = new Button(140, 225 + 90,
			pauseButtonImg[2][0], pauseButtonImg[2][1], MenuButtonShow, [](Button* t) {}, 267 * 0.6, 66 * 0.6);

		for (int i = 0; i < 3; i++) {
			pauseUI_Pool.AddSon(pauseButtons[i]);
		}

		pause = new Sprite(160, 200 - 30, pauseImg, DefaultShow, DefaultUpdate, 167 * 0.7, 54 * 0.7);
		pauseUI_Pool.AddSon(pause);

		loaded = true;
	}
}

extern int pauseButtonOn;
extern bool pressedEnter;
void PauseUI_Update() {
	for (int i = 0; i < 3; i++) {
		if (i == pauseButtonOn) {
			if (!pauseButtons[i]->is_on)selectSE->Play();
			pauseButtons[i]->is_on = 1;
		}
		else pauseButtons[i]->is_on = 0;
	}
	if (pressedEnter) {
		pressedEnter = false;
		okSE->Play();
		switch (PauseButton(pauseButtonOn))
		{
		case B_GAME:
			gameProcess = GAME_PLAY;
			break;
		case B_TITLE:

			break;
		case B_RETRY:
			GameLoad();
			break;
		default:
			break;
		}
	}
}


#endif // !PAUSE_H
