#include "graphics.h"

/* point structure */
Point::Point(float _x, float _y) {
	x = _x;
	y = _y;
}

/* º¯Êý£ºstring ×ª»» LPCWSTR */
LPCWSTR stringToLPCWSTR(std::string orig) {
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

/* class Text */
bool Text::Create(float left, float top, float right, float bottom) {
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory));

	HRESULT hr = pDWriteFactory->CreateTextFormat(
		L"Arial",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f * 96.0f / 72.0f,
		L"en-US",
		&pTextFormat
	);

	layoutRect = D2D1::RectF(left, top, right, bottom);
	return true;
}

IDWriteTextFormat* Text::GetFormat() {
	return pTextFormat;
}

void Text::SetRect(float left, float top, float right, float bottom) {
	layoutRect.left = left;
	layoutRect.top = top;
	layoutRect.right = right;
	layoutRect.bottom = bottom;
}


/* class Bitmap */
Bitmap::Bitmap(LPCWSTR _picname) {
	picname = _picname;
}

bool Bitmap::Create() {
	HRESULT hr = S_OK;
	pIWICFactory = NULL;
	pDecoder = NULL;
	pSource = NULL;
	pStream = NULL;
	pConverter = NULL;
	pScaler = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pIWICFactory
	);


	hr = pIWICFactory->CreateDecoderFromFilename(
		picname,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
		if (FAILED(hr)) {
			MessageBox(NULL, _T("Draw 1failed!"), _T("Error"), 0);
			return false;
		}
	}


	if (SUCCEEDED(hr))
	{
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
		if (FAILED(hr)) {
			MessageBox(NULL, _T("Draw 2failed!"), _T("Error"), 0);
			return false;
		}
	}

	hr = pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
	);

	if (FAILED(hr)) {
		MessageBox(NULL, _T("Draw 3failed!"), _T("Error"), 0);
		return false;
	}

	return true;
}

ID2D1Bitmap* Bitmap::GetBitmap() {
	return pBitmap;
}

ID2D1Bitmap** Bitmap::GetBitmapPtr() {
	return &pBitmap;
}

IWICFormatConverter* Bitmap::GetConverter() {
	return pConverter;
}

/* class Brush */
Brush::Brush() {}

ID2D1SolidColorBrush* Brush::GetBrush() {
	return brush;
}

ID2D1SolidColorBrush** Brush::GetBrushPtr() {
	return &brush;
}


/* class GFactory */
GFactory::GFactory(HWND& _hwndptr) {
	hwndptr = &_hwndptr;
}

ID2D1HwndRenderTarget* GFactory::GetHandle() {
	return hdl;
}

ID2D1Factory* GFactory::GetFactory() {
	return d2dFactory;
}

bool GFactory::Create() {
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);
	if (FAILED(hr)) {
		MessageBox(*hwndptr, _T("Create D2D factory failed!"), _T("Error"), 0);
		return false;
	}

	RECT rc;
	GetClientRect(*hwndptr, &rc);
	hr = d2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			*hwndptr,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
		),
		&hdl
	);
	if (FAILED(hr)) {
		MessageBox(*hwndptr, _T("Create render target failed!"), _T("Error"), 0);
		return false;
	}

	return true;
}

bool GFactory::CreateBrush(Brush &brush, COLOR color) {
	HRESULT hr;
	hr = hdl->CreateSolidColorBrush(
		color,
		brush.GetBrushPtr()
	);

	if (FAILED(hr)) {
		MessageBox(*hwndptr, _T("Create brush failed!"), _T("Error"), 0);
		return false;
	}

	return true;
}


bool GFactory::CreateBitmap(Bitmap &bmp) {
	HRESULT hr;
	hr = hdl->CreateBitmapFromWicBitmap(
		bmp.GetConverter(),
		NULL,
		bmp.GetBitmapPtr()
	);

	if (FAILED(hr)) {
		MessageBox(NULL, _T("Draw 4failed!"), _T("Error"), 0);
		return false;
	}
	return true;
}


void GFactory::BeginDraw() {
	hdl->BeginDraw();
}

bool GFactory::EndDraw() {
	HRESULT hr = hdl->EndDraw();
	if (FAILED(hr)) {
		MessageBox(NULL, _T("Draw failed!"), _T("Error"), 0);
		return false;
	}
	return true;
}

void GFactory::Clear(COLOR color) {	// Clear background color to a color
	hdl->Clear(color);
}

void GFactory::DrawLine(Brush &brush, float left, float top, float right, float bottom, float width = 1.0) {
	hdl->DrawLine(D2D1::Point2F(left, top), D2D1::Point2F(right, bottom), brush.GetBrush(), width);
}

void GFactory::DrawRectangle(Brush &brush, float left, float top, float right, float bottom, float width = 1.0) {
	hdl->DrawRectangle(
		D2D1::RectF(left, top, right, bottom),
		brush.GetBrush(),
		width
	);
}

void GFactory::FillRectangle(Brush &brush, float left, float top, float right, float bottom) {
	hdl->FillRectangle(
		D2D1::RectF(left, top, right, bottom),
		brush.GetBrush()
	);
}

void GFactory::DrawTriangle(Brush &brush, float x1, float y1, float x2, float y2, float x3, float y3, float width = 1.0) {
	hdl->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush.GetBrush(), width);
	hdl->DrawLine(D2D1::Point2F(x2, y2), D2D1::Point2F(x3, y3), brush.GetBrush(), width);
	hdl->DrawLine(D2D1::Point2F(x3, y3), D2D1::Point2F(x1, y1), brush.GetBrush(), width);
}

void GFactory::DrawTriangle(Brush &brush, Point p1, Point p2, Point p3, float width) {
	hdl->DrawLine(D2D1::Point2F(p1.x, p1.y), D2D1::Point2F(p2.x, p2.y), brush.GetBrush(), width);
	hdl->DrawLine(D2D1::Point2F(p2.x, p2.y), D2D1::Point2F(p3.x, p3.y), brush.GetBrush(), width);
	hdl->DrawLine(D2D1::Point2F(p3.x, p3.y), D2D1::Point2F(p1.x, p1.y), brush.GetBrush(), width);
}

void GFactory::DrawBitmap(Bitmap &bmp, float left, float top, float right, float bottom) {
	hdl->DrawBitmap(
		bmp.GetBitmap(),
		D2D1::RectF(left, top, right, bottom)
	);
}

void GFactory::Write(Text &text, Brush &brush, std::string s) {
	hdl->DrawText(
		stringToLPCWSTR(s),
		s.length(),
		text.GetFormat(),
		text.layoutRect,
		brush.GetBrush()
	);
}

void GFactory::WriteW(Text &text, Brush &brush, LPCWSTR s) {
	hdl->DrawText(
		s,
		wcslen(s),
		text.GetFormat(),
		text.layoutRect,
		brush.GetBrush()
	);
}
