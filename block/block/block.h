#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "engine.h"

ObjectBuffer pool;	//ÓÎÏ·¶ÔÏó³Ø

float x = 100, y = 100;
bool hitLeft = false, hitRight = false;
extern bool getKey[256];
void keyboard() {
	if (getKey[VK_LEFT] && !hitLeft)
		x -= 5;
	if (getKey[VK_RIGHT] && !hitRight)
		x += 5;
	if (getKey[VK_UP])
		y -= 5;
	if (getKey[VK_DOWN])
		y += 5;
}

class Rotatable :public Sprite {
public:
	Rotatable(double _x, double _y,
		Bitmap& _image, void(*_showCallback)(Sprite*),
		void(*_updateCallback)(Sprite*),
		double _width,	double _height, double _angle = 0, double _velocity = 1) 
		:Sprite(_x,_y,_image,_showCallback,_updateCallback,_width,_height){

		angle = _angle;
		velocity = _velocity;
		D2D1_SIZE_F size;
		size.height = _height;
		size.width = _width;
		D2D_RECT_F rec1;
		rec1.left = x;
		rec1.top = y;
		rec1.right = x + size.width;
		rec1.bottom = y + size.height;
	}

	D2D_RECT_F rec1;
	ID2D1RectangleGeometry *Grec;
	ID2D1TransformedGeometry *Grec2;
	double angle;	//the angle with the x axis of rad
	double velocity;
};



inline bool isHit(Sprite* a, Sprite* b) {
	double startX1 = a->x,
		startY1 = a->y,
		endX1 = startX1 + a->width,
		endY1 = startY1 + a->height;

	double startX2 = b->x,
		startY2 = b->y,
		endX2 = startX2 + b->width,
		endY2 = startY2 + b->height;

	return !(endY2 < startY1 || endY1 < startY2 || startX1 > endX2 || startX2 > endX1);
}

#endif // BLOCK_H
