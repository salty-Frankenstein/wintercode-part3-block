#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "resources.h"

class Background {
public:
	Background() {
		background = nullptr;
		mask = nullptr;
	}

	~Background() {
		delete background;
		delete mask;
	}

	void Load(int stageNum) {
		delete background;
		delete mask;
		switch (stageNum)
		{
		case 3:
			background = new Sprite(0, 0, mokouBG_Img, DefaultShow, DefaultUpdate, 640, 480);
			mask = new Rotatable(-50, -50, mask0Img, [](Rotatable* t) {}, [](Rotatable* t) {}, 600, 600, 1, 1, 0, 0.5);
			break;
		case 6:
			background = new Sprite(0, 0, pachiBG_Img, DefaultShow, DefaultUpdate, 640, 480);
			mask = new Rotatable(-50, -50, mask0Img, [](Rotatable* t) {}, [](Rotatable* t) {}, 600, 600, 1, 1, 0, 0.5);
			break;
		case 9:
			background = new Sprite(0, 0, utsuhoBG_Img, DefaultShow, DefaultUpdate, 640, 480);
			mask = new Rotatable(-50, -50, mask0Img, [](Rotatable* t) {}, [](Rotatable* t) {}, 600, 600, 1, 1, 0, 0.5);
			break;
		default:
			background = new Sprite(0, 0, normalBG_Img, DefaultShow, DefaultUpdate, 640, 480);
			auto maskShow = [](Sprite* t) {
				myGFactory->DrawBitmap(*t->image, t->x, t->y - t->height, t->x + t->width, t->y);
				myGFactory->DrawBitmap(*t->image, t->x + t->width, t->y - t->height, t->x + 2 * t->width, t->y);
				myGFactory->DrawBitmap(*t->image, t->x + 2 * t->width, t->y - t->height, t->x + 3 * t->width, t->y);
				myGFactory->DrawBitmap(*t->image, t->x, t->y, t->x + t->width, t->y + t->height);
				myGFactory->DrawBitmap(*t->image, t->x, t->y + t->height, t->x + t->width, t->y + 2 * t->height);
				myGFactory->DrawBitmap(*t->image, t->x + t->width, t->y, t->x + 2 * t->width, t->y + t->height);
				myGFactory->DrawBitmap(*t->image, t->x + t->width, t->y + t->height, t->x + 2 * t->width, t->y + 2 * t->height);
				myGFactory->DrawBitmap(*t->image, t->x + 2 * t->width, t->y, t->x + 3 * t->width, t->y + t->height);
				myGFactory->DrawBitmap(*t->image, t->x + 2 * t->width, t->y + t->height, t->x + 3 * t->width, t->y + 2 * t->height);
			};
			auto maskUpdate = [](Sprite* t) {
				t->x -= 1;
				t->y += 1;
				if (t->x < -t->width) {
					t->x = 0;
					t->y = 0;
				}
			};
			mask = new Sprite(0, 0, mask1Img, maskShow, maskUpdate, 256, 256, 1, 1);
			break;
		}
	}

	void Show(){
		if (bombOn) {
			if (gameTimer / 6 % 2 == 0) {
				background->x += 1;
				mask->x += 1;
			}
			else {
				background->x -= 1;
				mask->x -= 1;
			}
			if (gameTimer / 5 % 2 == 1) {
				background->y += 2;
				mask->y += 2;
			}
			else {
				background->y -= 2;
				mask->y -= 2;
			}
		}
		else {
			background->x = 0;
			background->y = 0;
		}
		background->Show();
		mask->Show();
		mask->Update();
	}

private:
	Sprite * background;
	Sprite * mask;
};

#endif // !BACKGROUND_H
