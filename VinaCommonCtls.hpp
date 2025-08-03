#pragma once
#include <variant>
#include "VinaInternalFunctionMapping.hpp"
using namespace VertexUI::Click;


typedef ID2D1DCRenderTarget* DCRT;
typedef ID2D1HwndRenderTarget* HRT;

struct VertexUICtlColor
{
	unsigned long color = VERTEXUICOLOR_MIDNIGHT;
	unsigned long borderColor = VERTEXUICOLOR_MIDNIGHTPLUS;
	unsigned long innerColor =  VERTEXUICOLOR_WHITEDRAW;
	unsigned long hoverColor = VERTEXUICOLOR_MIDNIGHT;
	unsigned long hoverBorderColor = VERTEXUICOLOR_MIDNIGHTPLUS;
	unsigned long hoverInnerColor = VERTEXUICOLOR_WHITEDRAW;
	unsigned long activeColor = VERTEXUICOLOR_LAVENDER;
	unsigned long activeBorderColor = VERTEXUICOLOR_MIDNIGHTPLUS;
	unsigned long activeInnerColor = VERTEXUICOLOR_WHITEDRAW;

};
class VinaButton : public VertexUIControl{
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, std::function<void()>events = [] {}, unsigned long clr = VERTEXUICOLOR_MIDNIGHT, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE)
	{
		this->func = events;
		this->Clr = clr;
		this->txtsz = TxtSize;
		this->txtClr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		if (this->IsPushed == true)
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcBounceCurve(ap, 0, 0.5, 10);
			/*
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(15);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
				});
				*/
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawRoundRect(hdc, x + num, y + num, cx - num * 2, cy - num * 2, nClr, 8, 1, 1.0f, VERTEXUICOLOR_MIDNIGHTPLUS);

			D2DDrawText2(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz-num, txtClr, L"Segoe UI", 1, true);
		}
		else if (this->IsHoverd==true)
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcEaseOutCurve(ap, 0,0.5, 10);
			/*
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(15);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
				});
				*/
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr)+num*20,255);
			nG = GetMaxValue(GetGValue(Clr)+num*20,255);
			nB = GetMaxValue(GetBValue(Clr)+num*20,255);
			nClr = RGB(nR, nG, nB);
			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, nClr, 8, 1, 1.0f + num, VERTEXUICOLOR_MIDNIGHTPLUS);

			D2DDrawText2(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, txtClr, L"Segoe UI", 1, true);
		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			if (ap != 0)
			{
				/*
				CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
					VertexUI::Window::SimpleShadow::iDropShadow Shadow;
					Shadow.SetSharpness(15);
					Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
					Shadow.SetSize(5 + num * 10);
					Shadow.SetDarkness(100 - (10 - ap) * 5);
					Shadow.SetPosition(0, 0);
					Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
					});
					*/
			}
			unsigned long nClr = Clr;
			if (ap !=0)
			{
				int nR, nG, nB;
				nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
				nClr = RGB(nR, nG, nB);
			}
			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, nClr, 8, 1, 1.0f, VERTEXUICOLOR_MIDNIGHTPLUS);
			D2DDrawText2(hdc, txt.c_str(), x,(float)(y+cy/2-txtsz/1.5), cx, cy, txtsz, txtClr,L"Segoe UI",1,true);
		}
	}

	virtual int OnMouseUp()
	{
		ap = 0;
		Refresh(hWnd);
		func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		ap = 0;
		this->IsPushed = true;
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt,vinaEvent eventtype)
	{
	
			if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
			if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();
				
			if (eventtype == vinaEvent::mouseOver) { 
				
				this->IsHoverd = true;
				Refresh(hWnd);
		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc,  std::shared_ptr<VinaButton> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event=L"";
	unsigned long Clr;

	int id = -1;
protected:

	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaNotice : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, unsigned long clr = VERTEXUICOLOR_SEA, int TxtSize = 14, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->Clr = clr;
		this->txtsz = TxtSize;
		this->txtClr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		if (this->IsPushed == true)
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcBounceCurve(ap, 0, 0.5, 10);
			/*
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(15);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
				});
				*/
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawRoundRect(hdc, x + num, y + num, cx - num * 2, cy - num * 2, Clr, 8, 1, 1.0f, VuiFadeColor(Clr, 40));

			D2DDrawText2(hdc, txt.c_str(), x+10, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz - num, txtClr, L"Segoe UI", 1, false);
		}
		else if (this->IsHoverd == true)
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			/*
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(15);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
				});
				*/
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, Clr, 8, 1, 1.0f + num, VuiFadeColor(Clr,40));

			D2DDrawText2(hdc, txt.c_str(), x+10, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, txtClr, L"Segoe UI", 1, false);
		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			if (ap != 0)
			{
				/*
				CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
					VertexUI::Window::SimpleShadow::iDropShadow Shadow;
					Shadow.SetSharpness(15);
					Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
					Shadow.SetSize(5 + num * 10);
					Shadow.SetDarkness(100 - (10 - ap) * 5);
					Shadow.SetPosition(0, 0);
					Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
					});
					*/
			}
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
				nClr = RGB(nR, nG, nB);
			}
			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, Clr, 8, 1, 1.0f + num, VuiFadeColor(Clr, 40));

			D2DDrawText2(hdc, txt.c_str(), x+10, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, txtClr, L"Segoe UI", 1, false);
		}
	}

	virtual int OnMouseUp()
	{
		ap = 0;
		Refresh(hWnd);
		func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		ap = 0;
		this->IsPushed = true;
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaNotice > vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:

	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaText : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt,int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE , std::function<void()>events = [] {})
	{
		this->func = events;
		this->txtsz = TxtSize;
		this->Clr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		if (GetPtInfo(hWnd, x, y, cx, cy))
		{

			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			unsigned long nClr;
			int nR, nG, nB;
			int fact = 1;
			if (VuiColorAverage(Clr) > 128)fact = -2;
			nR = GetMaxValue(GetRValue(Clr) + num * 20*fact, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20*fact, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20*fact, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawText(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Segoe UI", 1);
		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				int fact = 1;
				if (VuiColorAverage(Clr) > 128)fact = -2;
				nR = GetMaxValue(GetRValue(Clr) + num * 20*fact, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20 * fact, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20 * fact, 255);
				nClr = RGB(nR, nG, nB);
			}
			D2DDrawText(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Segoe UI", 1);
		}
	}
	virtual int OnMouseUp()
	{
		this->func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		
	
		
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaText> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event;
	unsigned long Clr;

	int id = -1;
protected:
	int x, y, cx, cy;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaFAIcon : public VertexUIControl {
public:
	std::wstring CvtFont(std::wstring from)
	{
		if (from == std::wstring(L"test-right"))return std::wstring(L"\uf178");
		if (from == std::wstring(L"test-right-upd"))return std::wstring(L"\uf178");
		if (from == std::wstring(L"win-close"))return std::wstring(L"\uf00d");
		if (from == std::wstring(L"win-max"))return std::wstring(L"\uf065");
		if (from == std::wstring(L"win-winmax"))return std::wstring(L"\uf424");
		if (from == std::wstring(L"win-winrestore"))return std::wstring(L"\uf422");
		if (from == std::wstring(L"win-min"))return std::wstring(L"\uf068");
		if (from == std::wstring(L"win-restore"))return std::wstring(L"\uf066");
		if (from == std::wstring(L"test-left"))return std::wstring(L"\uf177");
		if (from == std::wstring(L"test-more"))return std::wstring(L"\uf141");
		if (from == std::wstring(L"test-more2"))return std::wstring(L"\uf52c");
		if (from == std::wstring(L"test-more3"))return std::wstring(L"\uf142");
	}
	void Set(int x, int y,  const wchar_t* txt, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->txtsz = TxtSize;
		this->Clr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = TxtSize;
		this->cy = TxtSize;
	}
	void Set(int x, int y,int cx, const wchar_t* txt, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->txtsz = TxtSize;
		this->Clr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = TxtSize;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		if (GetPtInfo(hWnd, x, y, cx, cy))
		{

			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			unsigned long nClr;
			int nR, nG, nB;
			int fact = 1;
			if (VuiColorAverage(Clr) > 128)fact = -2;
			nR = GetMaxValue(GetRValue(Clr) + num * 20 * fact, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20 * fact, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20 * fact, 255);
			nClr = RGB(nR, nG, nB);
			std::wstring newStr = this->CvtFont(txt.c_str());
			if (txt == std::wstring(L"test-left"))
			{
				D2DDrawText(hdc, newStr.c_str(), x - num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right"))
			{
				D2DDrawText(hdc, newStr.c_str(), x + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right-upd"))
			{
				D2DDrawText3(hdc, L"现在更新", x-5 + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz-4, nClr, L"Segoe UI", 1);
				D2DDrawText(hdc, newStr.c_str(), x+cx-txtsz + num * 3, (float)(y+1 + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else D2DDrawText(hdc, newStr.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				int fact = 1;
				if (VuiColorAverage(Clr) > 128)fact = -2;
				nR = GetMaxValue(GetRValue(Clr) + num * 20 * fact, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20 * fact, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20 * fact, 255);
				nClr = RGB(nR, nG, nB);
			}
			std::wstring newStr = this->CvtFont(txt.c_str());
			if (txt == std::wstring(L"test-left"))
			{
				D2DDrawText(hdc, newStr.c_str(), x-num*3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right"))
			{
				D2DDrawText(hdc, newStr.c_str(), x + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right-upd"))
			{
				D2DDrawText3(hdc, L"现在更新", x-5 + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz-4, nClr, L"Segoe UI", 1);
				D2DDrawText(hdc, newStr.c_str(), x + cx - txtsz + num * 3, (float)(y +1+ cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else D2DDrawText(hdc, newStr.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);

		}
	}
	virtual int OnMouseUp()
	{
		this->func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{



		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaFAIcon> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event;
	unsigned long Clr;

	int id = -1;
protected:
	int x, y, cx, cy;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaSwitch: public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, VertexUICtlColor ci , std::function<void()>events = [] {} )
	{
		this->func = events;
		this->Clr = ci.color;
		this->borderClr = ci.borderColor;
		this->innerClr = ci.innerColor;
		this->aBorderClr = ci.activeBorderColor;
		this->aClr = ci.activeColor;
		this->aInnerClr = ci.activeInnerColor;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		if (GetPtInfo(hWnd, x, y, cx, cy))
		{

			if (flag == 0 )
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;

			}
			

			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(25);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, cy/2	);
				});
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			int dist = cy * 0.15;
			int innerBlockSize = cy - dist * 2;
			if (value == false)
			{
				D2DDrawRoundRect(hdc, x, y, cx, cy, nClr, cy / 2, 1, 1.0f, borderClr);
				D2DDrawRoundRect(hdc, x + dist, y + dist, innerBlockSize, innerBlockSize, innerClr, cy / 2, 1, 1.0f, borderClr);
			}
			else {
				D2DDrawRoundRect(hdc, x, y, cx, cy, aClr, cy / 2, 1, 1.0f, aBorderClr);
				D2DDrawRoundRect(hdc, x + cx - innerBlockSize - dist, y + dist, innerBlockSize, innerBlockSize, aInnerClr, cy / 2, 1, 1.0f, aBorderClr);
			}

		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			if (ap != 0)
			{
				CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
					VertexUI::Window::SimpleShadow::iDropShadow Shadow;
					Shadow.SetSharpness(25);
					Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
					Shadow.SetSize(5 + num * 10);
					Shadow.SetDarkness(100 - (10 - ap) * 5);
					Shadow.SetPosition(0, 0);
					Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, cy / 2);
					});
			}
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
				nClr = RGB(nR, nG, nB);
			}
			int dist = cy*0.15;
			int innerBlockSize = cy - dist*2;
			if (value == false)
			{
				D2DDrawRoundRect(hdc, x, y, cx, cy, nClr, cy / 2, 1, 1.0f, borderClr);
				D2DDrawRoundRect(hdc, x + dist, y + dist, innerBlockSize, innerBlockSize, innerClr, cy / 2, 1, 1.0f, borderClr);
			}
			else {
				D2DDrawRoundRect(hdc, x, y, cx, cy, aClr, cy / 2, 1, 1.0f, aBorderClr);
				D2DDrawRoundRect(hdc, x+cx-innerBlockSize-dist, y + dist, innerBlockSize, innerBlockSize, aInnerClr, cy / 2, 1, 1.0f, aBorderClr);
			}
		}
	}
	virtual int AddEvent()
	{
		if (GetPtInfo(hWnd, x, y, cx, cy))
		{
			if (ClickMsg == 1)
			{
				ClickMsg = 0;
				preValue = value;
				value = !value;
				Refresh(hWnd);
			}
			if (KeepDownMsg == 1)
			{

			}
			if (RClickMsg == 1)
			{
				RClickMsg = 0;

			}
			if (hState == 0)
			{
				Refresh(hWnd);
				hState = 1;
			}
			return 0;
		}
		return -1;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, VinaSwitch* vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	bool GetValue()
	{
		return this->value;
	}
	void SetValue(bool val)
	{
		this->value = val;
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event;


	int id = -1;
protected:
	int x, y, cx, cy;
	HWND hWnd;
	int ap = 0;
	int ap2 = 0;
	int flag = 0;
	unsigned long innerClr;
	unsigned long borderClr;
	unsigned long Clr;
	unsigned long aInnerClr;
	unsigned long aBorderClr;
	unsigned long aClr;
	std::function<void()>func;
	bool value=false;
	bool preValue;
};

class VinaCaptionBar : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, unsigned long clr = VERTEXUICOLOR_MIDNIGHT, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->Clr = clr;
		this->txtsz = TxtSize;
		this->txtClr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2DDrawSolidRect(hdc, x, y, cx, cy, Clr, 1);
		D2DDrawText2(hdc, txt.c_str(), x+20, y+10, cx, cy, txtsz, txtClr, L"Segoe UI", 1, false);
	}

	virtual int OnMouseUp()
	{
		Refresh(hWnd);
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		Refresh(hWnd);
		func();
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaCaptionBar> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:

	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};

class VinaMultiTextBox : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, unsigned long clr = VERTEXUICOLOR_MIDNIGHT)
	{
		//this->func = events;
		this->Clr = clr;
		this->txtsz = TxtSize;
		this->txtClr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}

	int GetTxtLine2(const wchar_t* str) {
		int n = 0;
		if (NULL == str) return 0;
		if (str[0] == 0) return 0;
		while (*str) { if (*str == L'\n') n++; str++; }
		if (str[-1] != L'\n') n++;//最后一行末尾没有'\n'也算一行
		return n;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		ScrollDepth += this->GetParent()->GetInstantScrollDepth();


		int TextArea = (GetTxtLine2(this->txt.c_str())* txtsz*gScale);
	//	MonitorValue(TextArea);
		ScrollDepth = GetMaxValue(GetMinValue(ScrollDepth, 1),TextArea-cy);
	//	MonitorValue(ScrollDepth);
		float SlideRate = static_cast<float>(TextArea) / cy;
		float BlankRate = static_cast<float>(TextArea) / GetMinValue(ScrollDepth, 1);
		float dist = (cy / BlankRate);
		float height = (cy / SlideRate);

		D2DDrawRoundRect(hdc, x,y,cx,cy, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);
		D2DDrawInClippedRoundRect(hWnd, hdc, x, y, cx, cy, 12,
			[this,dist,height](HWND hWnd, HRT hdc2, int x, int y, int cx, int cy)->void {
				D2DDrawText(hdc2, this->txt.c_str(), x + 20, y + 20 - GetMinValue(ScrollDepth,1), cx + 240, cy + 240, this->txtsz, VERTEXUICOLOR_WHITE);
				D2DDrawRoundRect(hdc2, x + cx - 6, y+dist, 5, height, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 40), 4, 1, 0, VERTEXUICOLOR_MIDNIGHTPLUS);
			}
		);

	}

	virtual int OnMouseUp()
	{
		//ap = 0;
		Refresh(hWnd);
		//func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
	    //	ap = 0;
		this->IsPushed = true;
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr< VinaMultiTextBox> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:
	int ScrollDepth = 0;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaBarrier : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy,std::function<void()>fun=[]{})
	{
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
		this->func = fun;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{

	}

	virtual int OnMouseUp()
	{
		//ap = 0;
		Refresh(hWnd);
		//func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		//	ap = 0;
		//this->IsPushed = true;
		func();
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr< VinaBarrier> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:
	int ScrollDepth = 0;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaSlider : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, int Value = -1, unsigned long clr = VERTEXUICOLOR_DARKEN, const wchar_t* placeholder = L"", std::function<void()>events = [] {})
	{
		this->func = events;
		this->txt = placeholder;
		this->x = x - 10;
		this->y = y - 10;
		this->cx = cx + 20;
		this->cy = cy + 20;
		if (Value != -1)this->Value = Value;
		this->Clr = clr;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		RECT crc;

		double progress = ((double)(cx - 20) * Value) / 100.0;
		D2DDrawRoundRect(hdc, x + 10, y + 10, cx - 20, cy - 20, VuiFadeColor(Clr, 60), 8, 0.2f, 2, VuiFadeColor(Clr, 100), 0.6f);
		D2DDrawRoundRect(hdc, x + 10, y + 10, progress, cy - 20, VuiFadeColor(Clr, 10), 8);
		D2DDrawText2(hdc, this->txt.c_str(), x + 10, y + 12, cx - 20, cy - 20, 12, VuiFadeColor(Clr, 120), L"Segoe UI", 0.75f, true);
	}

	virtual int OnMouseUp()
	{

		this->OnEdit = false;
		Refresh(hWnd);
		return 0;
	}
	virtual int OnMouseDown()
	{
		this->OnEdit = true;
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		double p = (static_cast<double>(pt.x) - static_cast<double>((this->x + 10) * gScale)) / static_cast<double>((cx - 20) * gScale);
		this->Value = GetMaxValue(GetMinValue(p * 100, 0), 100);
		func();
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();
		if (eventtype == vinaEvent::mouseOver) {
			if (this->OnEdit == false)return 0;
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			double p = (static_cast<double>(pt.x) - static_cast<double>((this->x + 10) * gScale)) / static_cast<double>((cx - 20) * gScale);
			this->Value = GetMaxValue(GetMinValue(p * 100, 0), 100);
			func();
			Refresh(hWnd);
		}

		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaSlider> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}
	int GetValue()
	{
		return Value;
	}
	void SetValue(int val)
	{
		this->Value = val;
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:
	bool OnEdit = false;
	int Value = 0;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};