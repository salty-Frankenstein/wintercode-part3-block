/*						*\
		engine.h
	一个迷你的游戏引擎
	 2020 wintercode
	 by id:191220017
\*						*/

#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "win.h"
#include "graphics.h"
#include <list>

extern bool getKey[256];
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


/* 接口类，所有引擎内对象基类 */
class Object {
public:
	virtual void Show() = 0;
	virtual void Update() = 0;
	std::list<Object*> GetSon();
	void AddSon(Object* s);

protected:
	bool del;
	std::list<Object*> son;

};


/* class Sprite */
class Sprite :public Object {	//a universal object
public:
	Sprite(double _x, double _y, 
		Bitmap& _image, void(*showCallback)(Sprite*), 
		void(*updateCallback)(Sprite*),
		double width = 100.f,
		double height = 100.f
	);
	Sprite(double _x, double _y,
		Bitmap* _image, void(*showCallback)(Sprite*),
		void(*updateCallback)(Sprite*),
		double width = 100.f,
		double height = 100.f
	);
	void Show();
	void Update();
	Bitmap* image;
	double width, height;	//size
	double x, y;	//position
	double angle;	//the angle with the x axis of rad

private:
	void(*showCallback)(Sprite*);
	void(*updateCallback)(Sprite*);

};

#define INVISIBLE_IMG (nullptr)		//隐形sprite的image
#define INVISIBLE_SHOW ([](Sprite* t) {})	//隐形sprite的show函数

/* 游戏对象缓存 */
class ObjectBuffer :public Object {
public:
	void Show();
	void Update();
};



#endif // ENGINE_H

