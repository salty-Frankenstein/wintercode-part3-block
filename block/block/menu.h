/*					*\
		menu.h
	主菜单UI相关代码
	2020 wintercode
	by id:191220017
\*					*/

#pragma once
#ifndef MENU_H
#define MENU_H

#include "resources.h"

Sprite *cover;
Sprite *reimu;
Sprite *title;
Sprite *press;

ObjectBuffer menuUI_Pool;
void LoadMenuUI() {
	cover = new Sprite(0, 0, coverImg, DefaultShow, DefaultUpdate, 640, 480);
	reimu = new Sprite(300, 0, reimuImg, DefaultShow, DefaultUpdate, 333, 457);
	title = new Sprite(100, 0, titleImg, DefaultShow, DefaultUpdate, 335 * 1.25, 91 * 1.25);
	press = new Sprite(200 + 15 * 0.5, 350, pressImg, DefaultShow, DefaultUpdate, 225, 27);
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

void LoadMenuButton() {
	menuButtons[B_GAME_START] = new Button(450 + 300, 200, buttonImg[0][0], buttonImg[0][1], ButtonShow, ButtonUpdate, 143, 27);
	menuButtons[B_PLAYER_DATA] = new Button(450 + 300, 235, buttonImg[1][0], buttonImg[1][1], ButtonShow, ButtonUpdate, 140, 33);
	menuButtons[B_MUSIC_ROOM] = new Button(450 + 300, 270, buttonImg[2][0], buttonImg[2][1], ButtonShow, ButtonUpdate, 150, 27);
	menuButtons[B_OPTION] = new Button(450 + 300, 305, buttonImg[3][0], buttonImg[3][1], ButtonShow, ButtonUpdate, 89, 33);
	menuButtons[B_QUIT] = new Button(450 + 300, 340, buttonImg[4][0], buttonImg[4][1], ButtonShow, ButtonUpdate, 53, 30);
	for (int i = 0; i <= 4; i++) {
		menuButtons[i]->opacity = 0.5;
		menuUI_Pool.AddSon(menuButtons[i]);
	}
}

void MenuUI_Load() {
	static bool loaded = false;
	if(!loaded)
		titleBgm->Play();
	loaded = true;
}

extern int menuButtonOn;
extern bool pressedEnter;
extern bool isMenu;
void MenuUI_Update() {
	static bool pressed = false;
	static bool loaded = false;
	static unsigned long long pressTime = 0;
	static double opacity = 0;
	if (!isMenu) {	//title
		if (gameTimer <= 60) {
			reimu->opacity = opacity;
			title->opacity = opacity;
			//cover->opacity = opacity;
			opacity += 1/60.0;
			reimu->x -= 6 - gameTimer * 0.1;
			title->y += 6 - gameTimer * 0.1;
		}
		if (gameTimer / 60 % 2) {
			//press->x += 0.5;
			press->opacity += 0.015;
		}
		else {
			//press->x -= 0.5;
			press->opacity -= 0.015;
		}

		if (gameTimer > 60 && keyDown) {
			pressed = true;
			press->del = true;
			okSE->Play();
		}

		if (!pressed) {
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
				isMenu = true;
			}
		}

	}
	else {	//menu
		for (int i = 0; i <= 4; i++) {
			if (i == menuButtonOn) {
				if (!menuButtons[i]->is_on)selectSE->Play();
				menuButtons[i]->is_on = 1;
			}
			else menuButtons[i]->is_on = 0;
		}
		if (pressedEnter) {
			okSE->Play();
			switch (MenuButton(menuButtonOn))
			{
			case B_GAME_START:
				gameState = SELECT;
				break;
			case B_OPTION:

				break;
			case B_QUIT:
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}
	}

}

#endif // !MENU_H
