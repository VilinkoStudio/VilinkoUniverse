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
class VinaProgress : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, int Value = -1, unsigned long clr = VERTEXUICOLOR_DARKEN, const wchar_t* placeholder = L"")
	{
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
		D2DDrawRoundRect(hdc, x + 10, y + 10, cx - 20, cy - 20, VuiFadeColor(Clr, 60), 8, 0.2f, 1.2f, VuiFadeColor(Clr, 100), 0.6f);
		D2DDrawRoundRect(hdc, x + 10, y + 10, progress, cy - 20, VuiFadeColor(Clr, 10), 8);
		D2DDrawText2(hdc, this->txt.c_str(), x + 20, y + cy/2-9, cx - 20, cy - 20, 12, VuiFadeColor(Clr, 140), L"Segoe UI", 0.75f);
	}

	virtual int OnMouseUp()
	{

		Refresh(hWnd);
		return 0;
	}
	virtual int OnMouseDown()
	{
		
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();
		if (eventtype == vinaEvent::mouseOver) {
			if (this->OnEdit == false)return 0;
			Refresh(hWnd);
		}

		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaProgress> vuic)
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
class VinaLabel : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, int TxtSize = 15,
		unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {}) {
		this->func = events;
		this->txtsz = TxtSize;
		this->Clr = TxtColor;
		this->SetText(txt);
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
		this->CalculateLineInfo();
	}

	void SetText(const wchar_t* txt) {
		if (txt) {
			this->text = txt;
		}
		else {
			this->text = L"";
		}
		this->CalculateLineInfo();
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc) {
		this->hWnd = hWnd;
		this->RenderText(hdc);
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaProgress> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	virtual void RenderText(HRT hdc) {
		if (text.empty() || !hdc) return;

		// 创建文本格式
		IDWriteTextFormat* pTextFormat = nullptr;
		HRESULT hr = pDWriteFactory->CreateTextFormat(
			L"Segoe UI",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			(FLOAT)txtsz * gScale,
			L"en-US",
			&pTextFormat
		);

		if (SUCCEEDED(hr)) {
			pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			pTextFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP);

			// 创建文本布局
			IDWriteTextLayout* pTextLayout = nullptr;
			hr = pDWriteFactory->CreateTextLayout(
				text.c_str(),
				(UINT32)text.length(),
				pTextFormat,
				(FLOAT)(cx - 20) * gScale,  // 宽度限制
				(FLOAT)(cy - 20) * gScale,  // 高度限制
				&pTextLayout
			);

			if (SUCCEEDED(hr)) {
				// 设置文本颜色
				ID2D1SolidColorBrush* pBrush = nullptr;
				hdc->CreateSolidColorBrush(D2D1::ColorF(GetRValue(Clr) / 255.0f,
					GetGValue(Clr) / 255.0f,
					GetBValue(Clr) / 255.0f), &pBrush);

				if (pBrush) {
					// 绘制背景（如果需要选择高亮）
					if (hasSelection) {
						DrawSelectionBackground(hdc, pTextLayout);
					}

					// 绘制文本
					D2D1_RECT_F layoutRect = D2D1::RectF(
						(FLOAT)(x + 10) * gScale,
						(FLOAT)(y + 10) * gScale,
						(FLOAT)(x + cx - 10) * gScale,
						(FLOAT)(y + cy - 10) * gScale
					);

					hdc->DrawTextLayout(D2D1::Point2F(layoutRect.left, layoutRect.top),
						pTextLayout, pBrush);

					// 绘制光标
					if (showCursor && hasFocus) {
						DrawCursor(hdc, pTextLayout);
					}

					pBrush->Release();
				}

				pTextLayout->Release();
			}

			pTextFormat->Release();
		}
	}

	void DrawSelectionBackground(HRT hdc, IDWriteTextLayout* pTextLayout) {
		if (selectionStart == selectionEnd) return;

		UINT32 start = std::min(selectionStart, selectionEnd);
		UINT32 end = std::max(selectionStart, selectionEnd);

		DWRITE_HIT_TEST_METRICS hitTestMetrics;
		FLOAT x, y;

		// 获取选择起始位置坐标
		pTextLayout->HitTestTextPosition(start, FALSE, &x, &y, &hitTestMetrics);

		ID2D1SolidColorBrush* pSelectionBrush = nullptr;
		hdc->CreateSolidColorBrush(D2D1::ColorF(0.2f, 0.4f, 0.8f, 0.3f), &pSelectionBrush);

		if (pSelectionBrush) {
			// 简化的选择背景绘制（实际应该按行绘制矩形）
			D2D1_RECT_F selectionRect = D2D1::RectF(
				x,
				y,
				x + 100, // 这里需要更精确的计算
				y + hitTestMetrics.height
			);
			hdc->FillRectangle(selectionRect, pSelectionBrush);
			pSelectionBrush->Release();
		}
	}

	void DrawCursor(HRT hdc, IDWriteTextLayout* pTextLayout) {
		DWRITE_HIT_TEST_METRICS hitTestMetrics;
		FLOAT cursorX, cursorY;

		pTextLayout->HitTestTextPosition(cursorPosition, FALSE, &cursorX, &cursorY, &hitTestMetrics);

		ID2D1SolidColorBrush* pCursorBrush = nullptr;
		hdc->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f), &pCursorBrush);

		if (pCursorBrush) {
			D2D1_RECT_F cursorRect = D2D1::RectF(
				cursorX,
				cursorY,
				cursorX + 2.0f,
				cursorY + hitTestMetrics.height
			);
			hdc->FillRectangle(cursorRect, pCursorBrush);
			pCursorBrush->Release();
		}
	}

	virtual int OnMouseUp() {
		this->isMouseDown = false;
		this->hasFocus = true;
		UpdateCursorPosition();
		Refresh(hWnd);
		return 0;
	}

	virtual int OnMouseDown() {
		this->isMouseDown = true;
		this->hasFocus = true;
		this->selectionStart = GetTextPositionFromPoint();
		this->selectionEnd = this->selectionStart;
		this->hasSelection = false;
		UpdateCursorPosition();
		Refresh(hWnd);
		return 0;
	}

	virtual int OnMouseMove(const vinaPoint& pt) {
		if (isMouseDown && hasFocus) {
			UINT32 newEnd = GetTextPositionFromPoint();
			if (newEnd != selectionEnd) {
				selectionEnd = newEnd;
				hasSelection = (selectionStart != selectionEnd);
				Refresh(hWnd);
			}
		}
		return 0;
	}

	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype) {
		switch (eventtype) {
		case vinaEvent::mouseUp:
			return OnMouseUp();
		case vinaEvent::mouseDown:
			return OnMouseDown();
		case vinaEvent::mouseOver:
			if (isMouseDown) {
				return OnMouseMove(pt);
			}
			break;
		case vinaEvent::mouseUnfocus:
			hasFocus = false;
			Refresh(hWnd);
			break;
		}
		return 0;
	}

	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaLabel> vuic) {
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}

	// 获取选择的文本
	std::wstring GetSelectedText() {
		if (!hasSelection || selectionStart == selectionEnd) {
			return L"";
		}

		UINT32 start = std::min(selectionStart, selectionEnd);
		UINT32 end = std::max(selectionStart, selectionEnd);

		if (end <= text.length()) {
			return text.substr(start, end - start);
		}
		return L"";
	}

	// 全选
	void SelectAll() {
		selectionStart = 0;
		selectionEnd = (UINT32)text.length();
		hasSelection = (selectionEnd > 0);
		cursorPosition = selectionEnd;
		Refresh(hWnd);
	}

	// 清除选择
	void ClearSelection() {
		selectionStart = selectionEnd = cursorPosition = 0;
		hasSelection = false;
		Refresh(hWnd);
	}

protected:
	std::wstring text;
	float txtsz = 15;
	unsigned long Clr;
	std::function<void()> func;
	HWND hWnd;
	bool isMouseDown = false;
	bool hasFocus = false;
	bool hasSelection = false;
	bool showCursor = true;
	UINT32 selectionStart = 0;
	UINT32 selectionEnd = 0;
	UINT32 cursorPosition = 0;

	// 行信息结构
	struct LineInfo {
		UINT32 startChar;
		UINT32 endChar;
		FLOAT height;
	};
	std::vector<LineInfo> lineInfos;

	void CalculateLineInfo() {
		lineInfos.clear();
		if (text.empty()) return;

		// 这里应该使用 IDWriteTextLayout 来计算实际的行信息
		// 简化实现：按换行符分割
		UINT32 start = 0;
		for (UINT32 i = 0; i <= text.length(); ++i) {
			if (i == text.length() || text[i] == L'\n') {
				LineInfo line;
				line.startChar = start;
				line.endChar = i;
				line.height = txtsz * 1.2f; // 估算行高
				lineInfos.push_back(line);
				start = i + 1;
			}
		}
	}

	UINT32 GetTextPositionFromPoint() {
		// 简化的点到文本位置转换
		// 实际应该使用 IDWriteTextLayout::HitTestPoint
		return (UINT32)text.length() / 2; // 示例返回中间位置
	}

	void UpdateCursorPosition() {
		cursorPosition = selectionEnd;
	}

	void Refresh(HWND hWnd) {
		InvalidateRect(hWnd, NULL, FALSE);
	}
};


