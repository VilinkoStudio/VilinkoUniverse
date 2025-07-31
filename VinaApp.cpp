// VinaApp.cpp : 定义应用程序的入口点。
//

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <json/json.h>

#include "framework.h"
#include "VinaApp.h"
#include "VertexUI/VertexUI.ClickArea.h"
#include "VertexUI/VertexUI.Panel.h"
#include "VertexUI/VertexUI.min.h"
#include "MainUI.hpp"
#include "VinaWindow.hpp"
VertexUIInit;
#define MAX_LOADSTRING 100

static bool IsCfg = false;

// 全局变量:
HINSTANCE hInst;                                // 当前实例
HANDLE hMyFont;
HGLOBAL hFntMem;
std::wstring LatestVersion;
std::wstring ChangeLog;
std::wstring InstallPath;

VinaWindow* MainWindow = new VinaWindow;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    bool bParseSuccess = false;
    Json::Value paramsRoot;
    Json::Reader jsonReader;

    try {
        if (jsonReader.parse(ws2s(lpCmdLine), paramsRoot) && paramsRoot.isMember("project") && paramsRoot["project"].isString()) {
            if (paramsRoot["project"].asString() == "lightframe" &&
                paramsRoot.isMember("build_date") && paramsRoot["build_date"].isString() &&
                paramsRoot.isMember("path") && paramsRoot["path"].isString()) {

                bParseSuccess = true;

                httplib::SSLClient httpcli("api.vertillusion.com");
                httplib::Params params;
                httplib::Headers headers = {
                    { "Vilinko-Project", "LightFrame" }
                };
                Json::Value resultRoot;
                params.emplace("build_date", paramsRoot["build_date"].asString());

                auto httpRes = httpcli.Get("/updater/check", params, headers);
                if (!httpRes ||
                    httpRes->status != httplib::StatusCode::OK_200 ||
                    !jsonReader.parse(httpRes->body, resultRoot) ||
                    !resultRoot.isMember("data") ||
                    !resultRoot["data"].isMember("has_update") ||
                    !resultRoot["data"]["has_update"].asBool()
                    )
                    PostQuitMessage(0);

                LatestVersion = s2ws(resultRoot["data"]["version"].asString());
                ChangeLog = s2ws(resultRoot["data"]["changelog"].asString());

                IsCfg = true;
            }
        }
    }
    catch (Json::Exception e) {
        std::cerr << e.what() << std::endl;
        PostQuitMessage(0);
    }

    if (!lpCmdLine && !bParseSuccess)PostQuitMessage(0);

    SetDataBase();
    hMyFont = INVALID_HANDLE_VALUE; // Here, we will (hopefully) get our font handle
    HRSRC  hFntRes = FindResource(hInstance, MAKEINTRESOURCE(IDF_FONTAWESOME), L"BINARY");
    if (hFntRes) { // If we have found the resource ... 
        hFntMem = LoadResource(hInstance, hFntRes); // Load it
        if (hFntMem != nullptr) {
            void* FntData = LockResource(hFntMem); // Lock it into accessible memory
            DWORD nFonts = 0, len = SizeofResource(hInstance, hFntRes);
            hMyFont = AddFontMemResourceEx(FntData, len, nullptr, &nFonts); // Fake install font!
        }
    }
    std::wstring fntBase = std::wstring(LocalData) + std::wstring(L"\\Font-AwesomeFree.ttf");
    FreeAnyResource(IDF_FONTAWESOME, L"BINARY", fntBase.c_str());
    AddFontResource(fntBase.c_str());

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VINAAPP));
    InitGlobalD2D();
    VuiColorSystemInit();
    gScale = GetScreenScale();
    //LoadVinaCom();

    MainWindow->Set(100, 100, 720 * gScale, 480 * gScale, L"Vina.Class.App.Main", L"Vilinko Universe");
    MainWindow->CreatePanel([](HWND hWnd, ID2D1HwndRenderTarget* hrt)->void {
        RECT rc;  
        GetClientRect(hWnd, &rc);
        D2DDrawSolidRect(hrt, 0, 0, rc.right, rc.bottom, VERTEXUICOLOR_MIDNIGHT);
        MainWindow->GetPanel()->Set(hWnd, hrt);

        static bool ExtraMsg = true;


        int ctl_x = 20; int ctl_y = 60; int ctl_w = rc.right/gScale-40; int ctl_h = 120;
        D2DDrawRoundRect(hrt, ctl_x, ctl_y, ctl_w , ctl_h, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);

        static std::shared_ptr<VinaButton>test1 = std::make_shared<VinaButton>();
        test1->Set(ctl_x+ctl_w-185, ctl_y+ctl_h-40, 80, 25, L"下载", [hWnd] {ExtraMsg = !ExtraMsg; Refresh(hWnd); },RGB( 82, 121, 251),12.5);
        MainWindow->GetPanel()->Add(test1);
        static std::shared_ptr<VinaButton>test2 = std::make_shared<VinaButton>();
        static double AnimateMove = 0;
        test2->Set(ctl_x + ctl_w - 95, ctl_y + ctl_h - 40, 80, 25, L"更新", [hWnd] {IsCfg = true; 	
        AnimateMove = 0;
        for (int i = 0; i < 30; i += 1)
        {
            AnimateMove = CalcBezierCurve(i, 0, 100, 30, .17, .67, .57, 1.29);
            XSleep(5);
            Refresh(hWnd);
        }
            }, RGB(82, 121, 251), 12.5);
        MainWindow->GetPanel()->Add(test2);
        D2DDrawRoundRect(hrt, ctl_x+15, ctl_y+15, 48, 48, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 30), 12, 1, 2, VuiFadeColor(VERTEXUICOLOR_MIDNIGHTPLUS, 30));
        D2DDrawText3(hrt, L"轻框LightFrame" ,ctl_x + 84, ctl_y + 22, 220, 40,20, VERTEXUICOLOR_WHITE,L"Segoe UI");
        D2DDrawText(hrt, L"Version:0.9.9", ctl_x + 15, ctl_y+ctl_h -28, 120, 40, 12, VERTEXUICOLOR_WHITE,L"Segoe UI",0.75f);

        int ctl_x1 = 20; int ctl_y1 = 60+ctl_h+20; 
        D2DDrawRoundRect(hrt, ctl_x1, ctl_y1, ctl_w, ctl_h, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);

        static std::shared_ptr<VinaButton>test11 = std::make_shared<VinaButton>();
        test11->Set(ctl_x1 + ctl_w - 185, ctl_y1 + ctl_h - 40, 80, 25, L"下载", [hWnd] {ExtraMsg = !ExtraMsg; Refresh(hWnd); }, RGB(82, 121, 251), 12.5);
        MainWindow->GetPanel()->Add(test11);
        static std::shared_ptr<VinaButton>test22 = std::make_shared<VinaButton>();
        test22->Set(ctl_x1 + ctl_w - 95, ctl_y1 + ctl_h - 40, 80, 25, L"更新", [hWnd] {IsCfg = true;
        AnimateMove = 0;
        for (int i = 0; i < 30; i += 1)
        {
            AnimateMove = CalcBezierCurve(i, 0, 100, 30, .17, .67, .57, 1.29);
            XSleep(5);
            Refresh(hWnd);
        }
            }, RGB(82, 121, 251), 12.5);
        MainWindow->GetPanel()->Add(test22);
        D2DDrawRoundRect(hrt, ctl_x1 + 15, ctl_y1 + 15, 48, 48, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 30), 12, 1, 2, VuiFadeColor(VERTEXUICOLOR_MIDNIGHTPLUS, 30));
        D2DDrawText3(hrt, L"重框HeavyFrame", ctl_x1 + 84, ctl_y1 + 22, 220, 40, 20, VERTEXUICOLOR_WHITE, L"Segoe UI");
        D2DDrawText(hrt, L"Version:-0.114.51", ctl_x1 + 15, ctl_y1 + ctl_h - 28, 120, 40, 12, VERTEXUICOLOR_WHITE, L"Segoe UI", 0.75f);

        if (IsCfg == true)
        {
            if (rc.bottom <= 600*gScale)
            {
                CompGdiD2D(hWnd, hrt, [rc](HWND h, HDC hrt)->void {
                    AreaBlur(hrt, { 0,int(40 * gScale + 100 * gScale - AnimateMove * gScale),int(rc.right),int(rc.bottom - 40 * gScale) }, 3, 6, 0);
                    });
            }
            else if (rc.bottom > 600 * gScale&& rc.bottom <800*gScale)
            {
                CompGdiD2D(hWnd, hrt, [rc](HWND h, HDC hrt)->void {
                    AreaBlur(hrt, { 0,int(40 * gScale + 100 * gScale - AnimateMove * gScale),int(rc.right),int(rc.bottom - 40 * gScale) }, 2, 8, 0);
                    });
            }
            else if (rc.bottom > 800 * gScale)
            {
                CompGdiD2D(hWnd, hrt, [rc](HWND h, HDC hrt)->void {
                    AreaBlur(hrt, { 0,int(40 * gScale + 100 * gScale - AnimateMove * gScale),int(rc.right),int(360 * gScale) }, 2, 10, 0);
                    });
                D2DDrawSolidRect(hrt, 0, int((40 + 360) * gScale + 100 * gScale - AnimateMove * gScale), int(rc.right), int(rc.bottom - (40 + 360) * gScale), VERTEXUICOLOR_MIDNIGHT);
            }
            static std::shared_ptr<VinaBarrier>layer = std::make_shared<VinaBarrier>();
            layer->Set(0, 40, rc.right / gScale, rc.bottom / gScale);
            MainWindow->GetPanel()->Add(layer);

            static std::shared_ptr<VinaFAIcon>bk = std::make_shared<VinaFAIcon>();
            bk->Set(20, 60 + 100- AnimateMove, L"test-left", 22, VERTEXUICOLOR_WHITE, [hWnd] {AnimateMove = 0;
            for (int i = 0; i < 30; i += 1)
            {
                AnimateMove = -CalcBezierCurve(i, -100, 100, 30, .26, -0.25, .76, .2);
                XSleep(5);
                Refresh(hWnd);
            } IsCfg = false; Refresh(hWnd); });
            MainWindow->GetPanel()->Add(bk);

            static std::shared_ptr<VinaNotice>notice = std::make_shared<VinaNotice>();
            notice->Set(20, 100+100-AnimateMove, rc.right / gScale - 40, 30, L"当前有更新可用。",VERTEXUICOLOR_SEA,12);
            MainWindow->GetPanel()->Add(notice);
            /*
            const wchar_t* btntxt;
            if (ExtraMsg == false)
            {
                btntxt = L"展开";
            }
            else  btntxt = L"折叠";

            static std::shared_ptr<VinaButton>test1 = std::make_shared<VinaButton>();
            test1->Set(20, 100, 100, 40, btntxt, [hWnd] {ExtraMsg = !ExtraMsg; Refresh(hWnd); }, VERTEXUICOLOR_MIDNIGHTPLUS);
            MainWindow->GetPanel()->Add(test1);
            */
            if (ExtraMsg == true)
            {
                static std::shared_ptr<VinaMultiTextBox>test2 = std::make_shared<VinaMultiTextBox>();
                test2->SetParent(MainWindow->GetPanel());
                test2->Set(20, 155 + 100 - AnimateMove, rc.right / gScale - 40, 200, ChangeLog.c_str(), 18, VERTEXUICOLOR_WHITE, VERTEXUICOLOR_MIDNIGHTPLUS);
                MainWindow->GetPanel()->Add(test2);

                //D2DDrawRoundRect(hrt, 20, 120, rc.right/gScale - 40, 200, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);
                //D2DDrawText(hrt, L"Hello World\n12345678", 30, 140, rc.right / gScale - 70, 200, 18, VERTEXUICOLOR_WHITE);

            }
        }
        //82 121 251
        
       
        

        static std::shared_ptr<VinaCaptionBar>capt = std::make_shared<VinaCaptionBar>();
        capt->Set(0, 0, rc.right / gScale - 120, 40, L"Vilinko Universe", VERTEXUICOLOR_MIDNIGHT, 18);
        MainWindow->GetPanel()->Add(capt);

        static std::shared_ptr<VinaFAIcon>close = std::make_shared<VinaFAIcon>();
        close->Set(rc.right / gScale - 32, 20, L"win-close", 15, VERTEXUICOLOR_WHITE, [] {DestroyWindow(MainWindow->GetHandle()); PostQuitMessage(0); });
        MainWindow->GetPanel()->Add(close);

        static bool IsMaximized = false;
        if (IsZoomed(hWnd) == true)IsMaximized = true;
        else IsMaximized = false;

        if (IsMaximized == false)
        {
            static std::shared_ptr<VinaFAIcon>max = std::make_shared<VinaFAIcon>();
            max->Set(rc.right / gScale - 32 - 32, 20, L"win-max", 15, VERTEXUICOLOR_WHITE, [hWnd] {
                IsMaximized = !IsMaximized;
                SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0); });
            MainWindow->GetPanel()->Add(max);
        }
        else {
            static std::shared_ptr<VinaFAIcon>max = std::make_shared<VinaFAIcon>();
            max->Set(rc.right / gScale - 32 - 32, 20, L"win-restore", 15, VERTEXUICOLOR_WHITE, [hWnd] {
                IsMaximized = !IsMaximized;
                SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0); });
            MainWindow->GetPanel()->Add(max);
        }
        static std::shared_ptr<VinaFAIcon>min = std::make_shared<VinaFAIcon>();
        min->Set(rc.right / gScale - 32 - 32 - 32, 20, L"win-min", 15, VERTEXUICOLOR_WHITE, [hWnd] {SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); });
        MainWindow->GetPanel()->Add(min);

        });
        
    MainWindow->SetOutFrame(VinaWindow::Client);
    MainWindow->RunFull();

    return 0;
}


