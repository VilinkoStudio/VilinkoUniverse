#pragma once
#include "tsl/ordered_map.h"
#include "VinaCommonCtls.hpp"
#include "VertexUI/vui.parser/vui.parser.hpp"
#include "Vui.Foundation/Encoding.h"
#include "VinaWindow.hpp"
const wchar_t* testChar = LR"(
Text{id("114514"),x(230),y(220),cx(100),cy(40),text("TextQAQ")}
FontIcon{id("114519"),x(230),y(410),size(40),text("test-right")}
FontIcon{id("114524"),x(280),y(410),size(25),text("test-right")}
FontIcon{id("114534"),x(310),y(410),size(15),text("test-right")}
Button{id("QwQ"),x(100),y(20),cx(100),cy(100),text("模拟点击"),internalEvent("NIUZHI")}
Button{id("QwQ2"),x(100),y(140),cx(100),cy(100),text("层2")}
Button{id("QwQ3"),x(100),y(260),cx(200),cy(100),text("层3（nznb")}
Button{id("QwQ91"),x(160),y(180),cx(100),cy(100),text("层4")}
Button{id("QwQ31"),x(200),y(260),cx(200),cy(100),text("层5")}
Button{id("QwQ4"),x(100),y(380),cx(100),cy(100),text("层6")}

)";
std::vector<std::shared_ptr<VinaButton>>btns;
void CreatePanelInfoBox(VinaWindow* Main,HRT hrt,int order, const wchar_t* txt, const wchar_t* version, std::function<void()> btn1, std::function<void()> btn2,ID2D1Bitmap* ico = nullptr)
{
	RECT rc;
	GetClientRect(Main->GetHandle(), &rc);
	int ctl_h = 120;
	int ctl_x = 20; int ctl_y = 60+(order-1)*(ctl_h+20); int ctl_w = rc.right / gScale - 40;
	D2DDrawRoundRect(hrt, ctl_x, ctl_y, ctl_w, ctl_h, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);

    std::shared_ptr<VinaButton>test1 = std::make_shared<VinaButton>();
		test1->Set(ctl_x + ctl_w - 185, ctl_y + ctl_h - 40, 80, 25, L"下载", btn1, RGB(82, 121, 251), 12.5);
		if (btns.size()<order*2-1)btns.push_back(test1);
	//	Main->GetPanel()->Add(test1);
    std::shared_ptr<VinaButton>test2 = std::make_shared<VinaButton>();

	test2->Set(ctl_x + ctl_w - 95, ctl_y + ctl_h - 40, 80, 25, L"更新",btn2, RGB(82, 121, 251), 12.5);
	if (btns.size() < order*2)btns.push_back(test2);
	D2DDrawRoundRect(hrt, ctl_x + 15, ctl_y + 15, 48, 48, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 30), 12, 1, 2, VuiFadeColor(VERTEXUICOLOR_MIDNIGHTPLUS, 30));
	D2DDrawText3(hrt, txt, ctl_x + 84, ctl_y + 22, 220, 40, 20, VERTEXUICOLOR_WHITE, L"Segoe UI");
	D2DDrawText(hrt, version, ctl_x + 15, ctl_y + ctl_h - 28, 120, 40, 12, VERTEXUICOLOR_WHITE, L"Segoe UI", 0.75f);
}
void DrawDisplayBox2(HRT hrt, unsigned long clr,int x,int y,int cx,int cy,const wchar_t* title,const wchar_t* des)
{
	D2DDrawRoundRect(hrt, x, y, cx, cy, VERTEXUICOLOR_MIDNIGHTPLUS, 20, 1);
	D2DDrawRoundRect(hrt, x + 10, y + 10, cx - 20, cy / 3, clr, 20, 1);
	D2DDrawText3(hrt, title, x + 25, y +20, cx - 20, cy / 3, GetMinValue( cy / 3 - 35,2),VERTEXUICOLOR_WHITE);
	D2DDrawText(hrt, des, x + 20, y + cy / 3+25, cx - 20, cy / 3, GetMinValue(cy / 14, 2), VERTEXUICOLOR_WHITE,L"Segoe UI",0.85);
}

tsl::ordered_map < std::wstring, std::variant < std::monostate, std::shared_ptr<VinaButton>, std::shared_ptr<VinaText>, std::shared_ptr<VinaFAIcon>>> comVina;
int ParseVinaCom() {
	auto parser = vui::parser::wparser(testChar);
	parser.parse();
	for (auto obj : parser)
	{
		if (obj.name() == std::wstring(L"Button"))
		{
			std::wstring id;
			std::wstring text;
			std::wstring internalEvent=L"";
			int x, y, cx, cy = 0;
			for (auto pair : obj)
			{
				if (pair.name() == std::wstring(L"id"))pair.get(id);
				if (pair.name() == std::wstring(L"x"))pair.get(x);
				if (pair.name() == std::wstring(L"y"))pair.get(y);
				if (pair.name() == std::wstring(L"cx"))pair.get(cx);
				if (pair.name() == std::wstring(L"cy"))pair.get(cy);
				if (pair.name() == std::wstring(L"text"))pair.get(text);
				if (pair.name() == std::wstring(L"internalEvent"))pair.get(internalEvent);
			}
			std::shared_ptr<VinaButton> cb=std::make_shared <VinaButton>();
			cb->Set(x, y, cx, cy, text.c_str());
			cb->SetInternalEvent(internalEvent);
			comVina[id.c_str()] = cb;
		}
		if (obj.name() == std::wstring(L"Text"))
		{
			std::wstring id;
			std::wstring text;
			int x, y, cx, cy = 0;
			for (auto pair : obj)
			{
				if (pair.name() == std::wstring(L"id"))pair.get(id);
				if (pair.name() == std::wstring(L"x"))pair.get(x);
				if (pair.name() == std::wstring(L"y"))pair.get(y);
				if (pair.name() == std::wstring(L"cx"))pair.get(cx);
				if (pair.name() == std::wstring(L"cy"))pair.get(cy);
				if (pair.name() == std::wstring(L"text"))pair.get(text);

			}
			std::shared_ptr<VinaText> cb = std::make_shared <VinaText>();
			cb->Set(x, y, cx, cy, text.c_str());
			comVina[id.c_str()] = cb;
		}
		if (obj.name() == std::wstring(L"FontIcon"))
		{
			std::wstring id;
			std::wstring text;
			int x, y,  cy = 0;
			for (auto pair : obj)
			{
				if (pair.name() == std::wstring(L"id"))pair.get(id);
				if (pair.name() == std::wstring(L"x"))pair.get(x);
				if (pair.name() == std::wstring(L"y"))pair.get(y);
				if (pair.name() == std::wstring(L"size"))pair.get(cy);
				if (pair.name() == std::wstring(L"text"))pair.get(text);

			}
			std::shared_ptr<VinaFAIcon> cb = std::make_shared <VinaFAIcon>();
			cb->Set(x, y, text.c_str(),cy);
			comVina[id.c_str()] = cb;
		}
	}

	return 0;
}
int LoadVinaCom() {
	ParseVinaCom();
	return 0;
}