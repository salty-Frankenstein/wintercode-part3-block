/*					*\
		block.h
	游戏内对象相关定义
	2020 wintercode
	by id:191220017
\*					*/

#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "engine.h"
GFactory *myGFactory; 
D2D1::Matrix3x2F oriTransMat;

Layer myLayer;
enum GameState { LOAD, MENU, SELECT, HISCORE, GAME, QUIT };
enum GameProcess { GAME_LOAD, GAME_RESTART, GAME_PLAY, GAME_PAUSE, GAME_END };

unsigned long long gameTimer = 0;
double x = 100, y = 100;
bool hitLeft = false, hitRight = false;
int menuButtonOn = 0;
int pauseButtonOn = 0;
bool pressedEnter = false;
bool isMenu = false;
bool ballActive;
bool bombOn = false;
bool bombHitted = false;
GameProcess gameProcess;

extern bool getKey[256];
void GameLoad();


auto DefaultShow = [](Sprite* t) {
	if (t->opacity < 0.99) {
		myLayer.layerParameters.opacity = t->opacity;
		myGFactory->PushLayer(myLayer);
		myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height);
		myGFactory->PopLayer();
	}
	else {
		myGFactory->DrawBitmap(*(t->image), t->x, t->y, t->x + t->width, t->y + t->height);
	}

};

auto DefaultUpdate = [](Sprite* t) {};

class Rotatable :public Sprite {
public:
	Rotatable(double _x, double _y,
		Bitmap& _image, void(*_showCallback)(Rotatable*),
		void(*_updateCallback)(Rotatable*),
		double _width,	double _height,
		int _layer = 1, double _opacity = 1, double _angle = 0, double _velocity = 0) 
		:Sprite(){

		x = _x;
		y = _y;
		image = &_image;
		showCallback = _showCallback;
		updateCallback = _updateCallback;
		width = _width;
		height = _height;
		opacity = _opacity;
		layer = _layer;
		del = false;

		angle = _angle;
		velocity = _velocity;
		
	}

	void Show();
	void Update();

	ID2D1BitmapBrush * brush;
	D2D1_SIZE_F imgSize;
	D2D_RECT_F rec1;
	ID2D1RectangleGeometry *Grec;
	double angle;	//the angle with the x axis of degree
	double velocity;

private:
	void(*showCallback)(Rotatable*);
	void(*updateCallback)(Rotatable*);
};


void Rotatable::Show() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Show();

	imgSize = image->GetBitmap()->GetSize();
	rec1.left = x;
	rec1.top = y;
	rec1.right = x + imgSize.width;
	rec1.bottom = y + imgSize.height;

	myGFactory->GetHandle()->CreateBitmapBrush(image->GetBitmap(), &brush);
	myGFactory->GetFactory()->CreateRectangleGeometry(rec1, &Grec);

	brush->SetTransform(D2D1::Matrix3x2F::Translation(x, y));

	myGFactory->GetHandle()->SetTransform(
		D2D1::Matrix3x2F::Rotation(angle,
			D2D1::Point2F((rec1.right + rec1.left) / 2, (rec1.top + rec1.bottom) / 2))
		*D2D1::Matrix3x2F::Scale(
			D2D1::Size(width / imgSize.width, height / imgSize.height),
			D2D1::Point2F(x, y))
	);

	if (opacity < 0.99) {
		myLayer.layerParameters.opacity = opacity;
		myGFactory->PushLayer(myLayer);
		myGFactory->GetHandle()->FillGeometry(Grec, brush);
		myGFactory->PopLayer();
	}
	else {
		myGFactory->GetHandle()->FillGeometry(Grec, brush);
	}
	
	myGFactory->GetHandle()->SetTransform(oriTransMat);

	showCallback(this);
}

void Rotatable::Update() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Update();

	angle += velocity;

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
		int _rank, double _width = 30, double _height = 30,
		int _layer = 1, double _opacity = 1)
		:Sprite() {
		x = _x;
		y = _y;
		image = Block::img[1][1];
		showCallback = _showCallback;
		updateCallback = _updateCallback;
		width = _width;
		height = _height;
		layer = _layer;
		opacity = _opacity;
		sound = false;
		del = false;
		rank = _rank;
	}
	bool sound;
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


class Boss :public Sprite {
public:
	Boss(double _x, double _y,
		Bitmap& _image, void(*_showCallback)(Boss*),
		void(*_updateCallback)(Boss*),
		double _width, double _height,
		int _HP_max, int _layer = 1, double _opacity = 1)
		:Sprite() {
		x = _x;
		y = _y;
		image = &_image;
		showCallback = _showCallback;
		updateCallback = _updateCallback;
		width = _width;
		height = _height;
		HP_max = _HP_max;
		HP_now = HP_max;
		liveTime = 0;
		opacity = _opacity;
		layer = _layer;
		sound = false;
		setTime = false;
		del = false;
		isDead = false;
		mahoujin = new Rotatable(x, y, mahoujinImg,[](Rotatable *t) {},[](Rotatable *t) {}, 200, 200, 1, 0.6, 0, -3);
		ring = new Rotatable(x, y, ringImg, [](Rotatable *t) {}, [](Rotatable *t) {}, 600, 600, 1, 0.6, 0, 1);
		radius = 600;
		hp_x = 390;
	}

	~Boss() {
		delete mahoujin;
		delete ring;
	}

	bool IsDead() {
		return isDead;
	}

	auto GetLiveTime() {
		return liveTime;
	}

	void SetTime() {
		setTime = true;
	}

	void Show();
	void Update();
	
	bool sound;
	bool setTime;
	int HP_max;
	int HP_now;
	static Bitmap HP_Img;
	static Bitmap mahoujinImg;
	static Bitmap ringImg;
	Rotatable* mahoujin;
	Rotatable* ring;
	double radius;
	double hp_x;
private:
	void(*showCallback)(Boss*);
	void(*updateCallback)(Boss*);
	bool isDead;
	unsigned long long liveTime;	//
};

Bitmap Boss::HP_Img;
Bitmap Boss::mahoujinImg;
Bitmap Boss::ringImg;

void Boss::Show() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Show();
	
	ring->Show();
	mahoujin->Show();
	showCallback(this);
}

void Boss::Update() {
	if(setTime)
		liveTime++;
	if (HP_now < 0 && opacity < 0)isDead = true;
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Update();

	mahoujin->Update();
	mahoujin->x = x + width / 2 - mahoujin->width / 2;
	mahoujin->y = y + height / 2 - mahoujin->width / 2;
	ring->Update();

	if (radius > 600 * (1.0*HP_now / HP_max))
		radius -= 1;
	ring->width = radius;
	ring->height = radius;
	ring->x = x + width / 2 - ring->width / 2;
	ring->y = y + height / 2 - ring->width / 2;

	updateCallback(this);
}


class Button :public Sprite {
public:
	Button(double _x, double _y, Bitmap &offImg, Bitmap &onImg,
		void(*_showCallback)(Button*),
		void(*_updateCallback)(Button*),
		double _width = 30, double _height = 30, 
		int _layer = 1, double _opacity = 1, bool _is_on = false)
		:Sprite() {
		x = _x;
		y = _y;
		image = &offImg;
		onImage = &onImg;
		showCallback = _showCallback;
		updateCallback = _updateCallback;
		width = _width;
		height = _height;
		layer = _layer;
		opacity = _opacity;
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

class GameString :public Object {
public:
	GameString(double _x, double _y, double _size,int _layer = 1, double _interval = 0) {
		x = _x;
		y = _y;
		size = _size;
		layer = _layer;
		interval = _interval;
		del = false;
	}
	
	
	std::string str;
	double x, y;
	double size;
	double interval;
	static Bitmap charImg[200];	//just using ACSII

	void Show() {
		for (int i = 0; i < str.length(); i++) {
			myGFactory->DrawBitmap(charImg[str[i]],
				x + i * (30 * size) + i * interval, y, x + (i + 1) * (30 * size) + i * interval, y + (37 * size));
		}
	}

	void Update() {

	}

	void SetNum(int x) {
		str = std::to_string(x);
		while (str.length() < 9)str = '0' + str;
	}

};
Bitmap GameString::charImg[200];

class Particle :public Object {	//16 kinds 1~16
public:
	Particle() {
		for (int i = 1; i <= 16; i++)
			isTypeActive[i] = false;
	}
	static Bitmap particleImg[20];
	bool isTypeActive[20];
private:
	ObjectBuffer pool;
};

Bitmap Particle::particleImg[20];




#endif // BLOCK_H
