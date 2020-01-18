/*						*\
		engine.h
	一个迷你的游戏引擎
	  封装Direct2D
	 2020 wintercode
	 by id:191220017
\*						*/

#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "win.h"

bool getKey[256] = { 0 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN:
		getKey[wParam] = true;
		return 0;

	case WM_KEYUP:
		getKey[wParam] = false;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

#endif

