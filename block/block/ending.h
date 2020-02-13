/*						*\
		ending.h
	结束界面相关代码
	2020 wintercode
	by id:191220017
\*						*/
#pragma once
#ifndef ENDING_H
#define ENDING_H

#include "resources.h"
Sprite * maskBlack = new Sprite(0, 0, maskBlackImg, DefaultShow, DefaultUpdate, 640, 480);
Sprite * ending = new Sprite(0, 0, endingImg, DefaultShow, DefaultUpdate, 640, 480);
ObjectBuffer endingPool;
unsigned long long endingTime;
bool isEnding;
bool endingLoaded = false;
void LoadEnding() {
	static bool loaded = false;
	if (!endingLoaded) {
		utsuhoBgm->Stop();
		isEnding = true;
		endingTime = 0;
		if (!loaded) {
			endingPool.AddSon(ending);
			endingPool.AddSon(maskBlack);
			loaded = true;
		}

		endingLoaded = true;
	}
}

void EndingUpdate() {
	endingTime++;
	if (endingTime < 60 * 3) {
		return;
	}
	if (endingTime < 60 * 3 + 60) {
		endingBgm->active = true;
		endingBgm->Play();
		maskBlack->opacity -= (1.0 / 60);
	}
	else {
		if (getKey['Z']) {
			isEnding = false;
			okSE->Play();
			endingBgm->Stop();
		}
	}
}

#endif // !ENDING_H


