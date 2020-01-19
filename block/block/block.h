#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "engine.h"

ObjectBuffer pool;	//”Œœ∑∂‘œÛ≥ÿ

float x = 100, y = 100;
extern bool getKey[256];
void keyboard() {
	if (getKey[VK_LEFT])
		x -= 5;
	if (getKey[VK_RIGHT])
		x += 5;
	if (getKey[VK_UP])
		y -= 5;
	if (getKey[VK_DOWN])
		y += 5;
}



#endif // BLOCK_H
