#include "engine.h"
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

/* class Object */
std::list<Object*> Object::GetSon() {
	return son;
}

void Object::AddSon(Object* s) {
	son.push_back(s);
}


/* class Sprite */
Sprite::Sprite(double _x, double _y,
	Bitmap& _image, void(*_showCallback)(Sprite*),
	void(*_updateCallback)(Sprite*),
	double _width,
	double _height){
	x = _x;
	y = _y;
	image = &_image;
	showCallback = _showCallback;
	updateCallback = _updateCallback;
	width = _width;
	height = _height;
}

Sprite::Sprite(double _x, double _y,
	Bitmap* _image, void(*_showCallback)(Sprite*),
	void(*_updateCallback)(Sprite*),
	double _width,
	double _height) {
	x = _x;
	y = _y;
	image = _image;
	showCallback = _showCallback;
	updateCallback = _updateCallback;
	width = _width;
	height = _height;
}

void Sprite::Show() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Show();
	showCallback(this);
}

void Sprite::Update() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Update();
	updateCallback(this);
}


/* class ObjectBuffer */
void ObjectBuffer::Show() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Show();
}

void ObjectBuffer::Update() {
	for (auto i = son.begin(); i != son.end(); i++)
		(*i)->Update();
}
