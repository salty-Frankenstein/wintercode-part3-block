#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "engine.h"
GFactory *myGFactory;
enum GameState { MENU, HISCORE, GAME, QUIT };

unsigned long long gameTimer = 0;
float x = 100, y = 100;
bool hitLeft = false, hitRight = false;
int menuButtonOn = 0;
bool pressedEnter = false;
extern bool getKey[256];
void keyboard(GameState state) {
	switch (state)
	{
	case MENU:
		if ((gameTimer) % 5 == 0) {
			if (getKey[VK_UP])
				menuButtonOn = (menuButtonOn + 4) % 5;
			if (getKey[VK_DOWN])
				menuButtonOn = (menuButtonOn + 1) % 5;
			if (getKey['Z']) pressedEnter = true;
		}
		break;
	case HISCORE:
		break;
	case GAME:
		if (getKey[VK_LEFT] && !hitLeft)
			x -= 5;
		if (getKey[VK_RIGHT] && !hitRight)
			x += 5;
		if (getKey[VK_UP])
			y -= 5;
		if (getKey[VK_DOWN])
			y += 5;
		break;
	case QUIT:
		break;
	default:
		break;
	}
	
}

auto DefaultShow = [](Sprite* t) {
	myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height);

};

auto DefaultUpdate = [](Sprite* t) {};

class Rotatable :public Sprite {
public:
	Rotatable(double _x, double _y,
		Bitmap& _image, void(*_showCallback)(Rotatable*),
		void(*_updateCallback)(Rotatable*),
		double _width,	double _height, double _angle = 0, double _velocity = 1) 
		:Sprite(){

		x = _x;
		y = _y;
		image = &_image;
		showCallback = _showCallback;
		updateCallback = _updateCallback;
		width = _width;
		height = _height;
		del = false;

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

	void Show();
	void Update();

	ID2D1BitmapBrush * brush;

	D2D_RECT_F rec1;
	ID2D1RectangleGeometry *Grec;
	ID2D1TransformedGeometry *Grec2;
	double angle;	//the angle with the x axis of rad
	double velocity;

private:
	void(*showCallback)(Rotatable*);
	void(*updateCallback)(Rotatable*);
};


void Rotatable::Show() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Show();
	showCallback(this);
}

void Rotatable::Update() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Update();
	updateCallback(this);
}


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

inline bool isHitCircle(Sprite* a, Sprite *b) {
	Point cen_a(a->x + 0.5*a->width, a->y + 0.5*a->width),
		cen_b(b->x + 0.5*b->width, b->y + 0.5*b->width);
	return (cen_a.x - cen_b.x)*(cen_a.x - cen_b.x) + (cen_a.y - cen_b.y)*(cen_a.y - cen_b.y)
		<= (0.5*a->width + 0.5*b->width)*(0.5*a->width + 0.5*b->width);
}


typedef Point Vec2;
float Squared_Mod(Vec2 v) {
	return v.x * v.x + v.y * v.y;
}

void Unitize(Vec2& v) {
	float t = sqrt(Squared_Mod(v));
	v.x /= t;
	v.y /= t;
}

Vec2 operator +(Vec2 a, Vec2 b) {
	return Vec2(a.x + b.x, a.y + b.y);
}

Vec2 operator -(Vec2 a, Vec2 b) {
	return Vec2(a.x - b.x, a.y - b.y);
}

float operator *(Vec2 a, Vec2 b) {
	return a.x * b.x + a.y * b.y;
}

Vec2 operator *(float u, Vec2 v) {
	return Vec2(u * v.x, u * v.y);
}


class Block :public Sprite {
public:
	Block(double _x, double _y,
		void(*_showCallback)(Block*),
		void(*_updateCallback)(Block*),
		int _rank, double _width = 30, double _height = 30)
		:Sprite() {
		x = _x;
		y = _y;
		image = INVISIBLE_IMG;
		showCallback = _showCallback;
		updateCallback = _updateCallback;
		width = _width;
		height = _height;
		del = false;
		rank = _rank;
	}
	int rank;
	static Bitmap* img[5][6];

	void Show();
	void Update();
private:
	void(*showCallback)(Block*);
	void(*updateCallback)(Block*);
};

Bitmap* Block::img[5][6];

void Block::Show() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Show();
	showCallback(this);
}

void Block::Update() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Update();
	updateCallback(this);
}

void BlockShow(Block* t) {
	if (t->rank > 0) {
		t->image = Block::img[t->rank][int(gameTimer / (7 + (0.2*t->rank))) % 5 + 1];
		//t->image = Block::img[t->rank][1];
		DefaultShow(t);
	}

}

void BlockUpdate(Block *t) {
	if (t->rank <= 0)t->del = true;
}

class Button :public Sprite {
public:
	Button(double _x, double _y, Bitmap &offImg, Bitmap &onImg,
		void(*_showCallback)(Button*),
		void(*_updateCallback)(Button*),
		double _width = 30, double _height = 30, bool _is_on = false)
		:Sprite() {
		x = _x;
		y = _y;
		image = &offImg;
		onImage = &onImg;
		showCallback = _showCallback;
		updateCallback = _updateCallback;
		width = _width;
		height = _height;
		del = false;
		is_on = _is_on;
		time = gameTimer;
		stop = false;
		isActive = false;
	}
	bool is_on;
	bool stop;
	bool isActive;
	unsigned long long time;
	Bitmap* onImage;
	void Show();
	void Update();
private:
	void(*showCallback)(Button*);
	void(*updateCallback)(Button*);
};

void Button::Show() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Show();
	showCallback(this);
}

void Button::Update() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Update();
	updateCallback(this);
}



#endif // BLOCK_H
