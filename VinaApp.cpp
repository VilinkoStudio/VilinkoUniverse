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
                    return 0;

                LatestVersion = s2ws(resultRoot["data"]["version"].asString());
                ChangeLog = s2ws(resultRoot["data"]["changelog"].asString());

                IsCfg = true;
            }
        }
    }
    catch (Json::Exception e) {
        std::cerr << e.what() << std::endl;
        return 0;
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

        static int prevwinval = 0;

        int winval = rc.bottom + rc.right;

        if (winval!=prevwinval)ClearVector(btns);

        prevwinval = winval;

        static double AnimateMove = 0;

        static bool isAbout = false;

        CreatePanelInfoBox(MainWindow, hrt, 1, L"轻框LightFrame", L"Version:0.9.9", [hWnd] { Refresh(hWnd); }, [hWnd] {IsCfg = true;
        AnimateMove = 0;
        for (int i = 0; i < 30; i += 1)
        {
            AnimateMove = CalcBezierCurve(i, 0, 100, 30, .17, .67, .57, 1.29);
            XSleep(5);
            Refresh(hWnd);
        }
            });


        CreatePanelInfoBox(MainWindow, hrt, 2, L" 重框HeavyFrame", L"Version:-11.4.51", [hWnd] {Refresh(hWnd); }, [hWnd] {IsCfg = true;
        AnimateMove = 0;
        for (int i = 0; i < 30; i += 1)
        {
            AnimateMove = CalcBezierCurve(i, 0, 100, 30, .17, .67, .57, 1.29);
            XSleep(5);
            Refresh(hWnd);
        }
            });

        CreatePanelInfoBox(MainWindow, hrt, 3, L" 超重框HeaviestFrame", L"Version:-114.451.419", [hWnd] { Refresh(hWnd); }, [hWnd] {IsCfg = true;
        AnimateMove = 0;
        for (int i = 0; i < 30; i += 1)
        {
            AnimateMove = CalcBezierCurve(i, 0, 100, 30, .17, .67, .57, 1.29);
            XSleep(5);
            Refresh(hWnd);
        }
            });

        for (auto i : btns)
        {
            MainWindow->GetPanel()->Add(i);
        }

        if (IsCfg == true)
        {
            static bool ExtraMsg = true;
            if (isAbout == true)
            {  
                D2DDrawSolidRect(hrt, 0, 100 - AnimateMove, rc.right, rc.bottom, VERTEXUICOLOR_MIDNIGHT);
            }
            else
            {

                if (winval <= 1920 * gScale)
                {
                    CompGdiD2D(hWnd, hrt, [rc](HWND h, HDC hrt)->void {
                        AreaBlur3(hrt, { 0,int(40 * gScale + 100 * gScale - AnimateMove * gScale),int(rc.right),int(rc.bottom - 40 * gScale) }, 3 - (1.9 - 0.02 * AnimateMove), 6, 0);
                        });
                }
                else if (winval > 1920 * gScale && winval < 2580 * gScale)
                {
                    D2DDrawSolidRect(hrt, 0, int((360) + 100 - AnimateMove), int(rc.right / gScale), int(rc.bottom / gScale - 40), VERTEXUICOLOR_MIDNIGHT);
                    CompGdiD2D(hWnd, hrt, [rc](HWND h, HDC hrt)->void {
                        AreaBlur3(hrt, { 0,int(40 * gScale + 100 * gScale - AnimateMove * gScale),int(rc.right),int(rc.bottom - 40 * gScale) }, 2 - (0.9 - 0.01 * AnimateMove), 8, 0);
                        });

                }
                else if (winval > 2580 * gScale)
                {
                    D2DDrawSolidRect(hrt, 0, int((360) + 100 - AnimateMove), int(rc.right) / gScale, int(rc.bottom / gScale - (40 + 360)), VERTEXUICOLOR_MIDNIGHT);
                    CompGdiD2D(hWnd, hrt, [rc](HWND h, HDC hrt)->void {
                        AreaBlur3(hrt, { 0,int(40 * gScale + 100 * gScale - AnimateMove * gScale),int(rc.right),int(360 * gScale) }, 2 - (0.9 - 0.01 * AnimateMove), 10, 0);
                        });

                }
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
                MainWindow->KillAnimation();
            } IsCfg = false;isAbout = false; Refresh(hWnd); ExtraMsg = true; });
            MainWindow->GetPanel()->Add(bk);

           
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
            if (isAbout == true)
            {
                DrawDisplayBox2(hrt, RGB(163, 139, 251),25, 105 + 100 - AnimateMove,300,GetMinValue(GetMaxValue( AnimateMove*2,220),1), L"沫海CimiMoly", L"\"星河如沫，映入澄曈\"\n去海岸 望星河 永远向圆满。");
                DrawDisplayBox2(hrt,RGB(240, 141, 56), 25+25+300, 105 + 100 - AnimateMove, 300, GetMinValue(GetMaxValue(AnimateMove * 2, 220), 1), L"悠笙iYoRoy", L"「愿世间万物都能被温柔以待。」");
                D2DDrawText(hrt, L"( 以上是参加 Vilinko Universe 的开发者。其他项目请参考相关\"关于\"页面。)\nCopyright © 2025 Vilinko Studio  |  感谢每一个为项目贡献的小伙伴！", 25, 330 , rc.right / gScale, 24,GetMinValue(GetMaxValue(AnimateMove/5, 16),1), VERTEXUICOLOR_WHITE, L"Segoe UI", 0.8);
            }
            else
            {
                if (ExtraMsg == true)
                {
                    static std::shared_ptr<VinaNotice>notice = std::make_shared<VinaNotice>();
                    notice->Set(20, 100 + 100 - AnimateMove, rc.right / gScale - 40, 30, L"当前有更新可用。", VERTEXUICOLOR_SEA, 12);
                    MainWindow->GetPanel()->Add(notice);

                    static std::shared_ptr<VinaMultiTextBox>test2 = std::make_shared<VinaMultiTextBox>();
                    test2->SetParent(MainWindow->GetPanel());
                    test2->Set(20, 155 + 100 - AnimateMove, rc.right / gScale - 40, 200, ChangeLog.c_str(), 18, VERTEXUICOLOR_WHITE, VERTEXUICOLOR_MIDNIGHTPLUS);
                    MainWindow->GetPanel()->Add(test2);

                    //D2DDrawRoundRect(hrt, 20, 120, rc.right/gScale - 40, 200, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);
                    //D2DDrawText(hrt, L"Hello World\n12345678", 30, 140, rc.right / gScale - 70, 200, 18, VERTEXUICOLOR_WHITE);


                    static std::shared_ptr<VinaFAIcon>nxt = std::make_shared<VinaFAIcon>();
                    nxt->Set(rc.right / gScale - 25 - 100, 120 + 360 - AnimateMove, 100, L"test-right-upd", 22, VERTEXUICOLOR_WHITE, [hWnd] {ExtraMsg = false; GlobalAnimationCount++;    MainWindow->InitAnimation(); Refresh(hWnd); });
                    MainWindow->GetPanel()->Add(nxt);
                }
                else
                {


                    static std::shared_ptr<VinaNotice>notice = std::make_shared<VinaNotice>();
                    notice->Set(20, 100 + 100 - AnimateMove, rc.right / gScale - 40, 30, L"正在更新...", RGB(65, 174, 134), 12);
                    MainWindow->GetPanel()->Add(notice);

                    static int ani = 0;
                    ani++;
                    double animove = CalcBezierCurve(ani, 0, 200, 100, .27, .04, .79, .98);
                    if (ani > 99)ani = 0;

                    D2DDrawCircleArc(hrt, rc.right / gScale / 2 - 7, 120 + 160 - AnimateMove, 15, VERTEXUICOLOR_SEA, animove, 3);

                    D2DDrawText2(hrt, L"当前步骤...", -2, 120 + 200 - AnimateMove, rc.right / gScale, 20, 14, VERTEXUICOLOR_WHITE, L"Segoe UI", 1, true);
                }
            }
        }
        //82 121 251
        
       
        static bool isMenu = false;

        static std::shared_ptr<VinaCaptionBar>capt = std::make_shared<VinaCaptionBar>();
        capt->Set(0, 0, rc.right / gScale - 160, 40, L"Vilinko Universe", VERTEXUICOLOR_MIDNIGHT, 18);
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
        min->Set(rc.right / gScale - 32 - 32 - 32, 20, L"win-min", 15, VERTEXUICOLOR_WHITE, [hWnd] {MainWindow->KillAnimation(); SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); });
        MainWindow->GetPanel()->Add(min);

        static std::shared_ptr<VinaFAIcon>more = std::make_shared<VinaFAIcon>();
        more->Set(rc.right / gScale - 32 - 32 - 32 - 25, 20, L"test-more3", 15, VERTEXUICOLOR_WHITE, [hWnd] {isMenu = true; GlobalAnimationCount+=1; MainWindow->InitAnimation(); });
        MainWindow->GetPanel()->Add(more);

        if (isMenu == true)
        {
            static int ani = 0;
            static double animove = 0;
            if (ani > 96&&ani<100) { GlobalAnimationCount -= 1; }
            else if(ani > 96){}
            else {
                ani+=6;
                animove = CalcBezierCurve(ani, 0, 120, 100, .54, .65, .61, .99);
            }
            static std::shared_ptr<VinaBarrier>layer = std::make_shared<VinaBarrier>();
            layer->Set(0, 0, rc.right / gScale, rc.bottom / gScale, [] {isMenu = false; ani = 0; });
            MainWindow->GetPanel()->Add(layer);

            CompGdiD2D(hWnd, hrt, [rc](HWND h, HDC hrt)->void {
                AreaBlur3(hrt, { (int)(rc.right - (32 + 32 + 32 + 25)*gScale),(int)(25*gScale),(int)((animove/1.1)*gScale),(int)((animove/3.2)*gScale) }, 3, 2, 0);
                });
            D2DDrawRoundRect(hrt, rc.right/gScale - (32 + 32 + 32 + 25)-1 ,23, (animove / 1.1)+2, animove/3.2, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 0.75, 2,VuiFadeColor( VERTEXUICOLOR_MIDNIGHTPLUS,20));

            static std::shared_ptr<VinaButton>test1 = std::make_shared<VinaButton>();
            test1->Set(rc.right / gScale - (32 + 32 + 32 + 25) +6, 23+6, (animove / 1.1) - 12, animove/5, L"关于" ,[hWnd]{
                isMenu = false; ani = 0;
                IsCfg = true;
                isAbout = true;
                AnimateMove = 0;
                for (int i = 0; i < 30; i += 1)
                {
                    AnimateMove = CalcBezierCurve(i, 0, 100, 30, .17, .67, .57, 1.29);
                    XSleep(5);
                    Refresh(hWnd);
                }

                }, VERTEXUICOLOR_MIDNIGHTPLUS,GetMinValue2(GetMaxValue2(animove/6, 12.5),2));
            MainWindow->GetPanel()->Add(test1);
        }
        });
        
    MainWindow->SetOutFrame(VinaWindow::Client);
    MainWindow->RunFull();

    return 0;
}


