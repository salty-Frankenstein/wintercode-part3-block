/*						*\
		graphics.h
	一个迷你的图形库
	  封装DirectX
	2020 wintercode
	by id:191220017
\*						*/

#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include<d2d1.h>
#include<tchar.h>
#include<windows.h>
#include<wincodec.h>
#include<string>
#include<Dwrite.h>

typedef D2D1_COLOR_F COLOR;
#define _COLOR(COLOR) ( D2D1::ColorF(D2D1::ColorF:: COLOR ) )


/* point structure */
struct Point {
	float x;
	float y;
	Point(float _x, float _y);
};


/* 函数：string 转换 LPCWSTR */
LPCWSTR stringToLPCWSTR(std::string orig);


/*
	class Text
文字的渲染、显示
支持std::string和LPCWSTR
*/
class Text {
public:
	bool Create(float left = 0.f, float top = 0.f, float right = 200.f, float bottom = 200.f);
	IDWriteTextFormat* GetFormat();
	void SetRect(float left, float top, float right, float bottom);

	D2D1_RECT_F layoutRect;

private:
	IDWriteFactory * pDWriteFactory;
	IDWriteTextFormat* pTextFormat;

};


/*
class Bitmap
封装WICBitmap && D2DBitmap
*/

class Bitmap {
public:
	Bitmap(LPCWSTR _picname);
	bool Create();
	ID2D1Bitmap* GetBitmap();
	ID2D1Bitmap** GetBitmapPtr();
	IWICFormatConverter* GetConverter();

private:
	ID2D1Bitmap * pBitmap;
	IWICImagingFactory *pIWICFactory;
	IWICBitmapDecoder *pDecoder;
	IWICBitmapFrameDecode *pSource;
	IWICStream *pStream;
	IWICFormatConverter *pConverter;
	IWICBitmapScaler *pScaler;
	LPCWSTR picname;
};


//////////
/*
class Brush
封装ID2D1SolidColorBrush
*/

class Brush {
public:
	Brush();
	ID2D1SolidColorBrush* GetBrush();
	ID2D1SolidColorBrush** GetBrushPtr();
private:
	ID2D1SolidColorBrush* brush;
};


///////////
/*
class GFactory
封装D2D initializer && ID2D1HwndRenderTarget
工厂类
创建graphics库中其他类的对象
*/

class GFactory {	//as a d2d render target
public:
	GFactory(HWND& _hwndptr);

	ID2D1HwndRenderTarget* GetHandle();		//仅在测试时使用
	ID2D1Factory * GetFactory();			//仅在测试时使用
	bool Create();
	bool CreateBrush(Brush &brush, COLOR color);
	bool CreateBitmap(Bitmap &bmp);

	void BeginDraw();
	bool EndDraw();
	void Clear(COLOR color);
	void DrawLine(Brush &brush, float left, float top, float right, float bottom, float width);

	void DrawRectangle(Brush &brush, float left, float top, float right, float bottom, float width);
	void FillRectangle(Brush &brush, float left, float top, float right, float bottom);

	void DrawTriangle(Brush &brush, float x1, float y1, float x2, float y2, float x3, float y3, float width);
	void DrawTriangle(Brush &brush, Point p1, Point p2, Point p3, float width);

	void DrawBitmap(Bitmap &bmp, float left, float top, float right, float bottom);

	void Write(Text &text, Brush &brush, std::string s);
	void WriteW(Text &text, Brush &brush, LPCWSTR s);
private:
	HWND * hwndptr;
	ID2D1Factory * d2dFactory;
	ID2D1HwndRenderTarget* hdl;

};


///////////

#endif // GRAPHICS_H
