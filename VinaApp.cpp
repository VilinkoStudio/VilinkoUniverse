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

// 全局变量:
HINSTANCE hInst;                                // 当前实例

VinaWindow* MainWindow = new VinaWindow;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VINAAPP));
    InitGlobalD2D();
    VuiColorSystemInit();
    gScale = GetScreenScale();
    //LoadVinaCom();

    MainWindow->Set(100, 100, 720 * gScale, 480 * gScale, L"Vina.Class.App.Main", L"Test");
    MainWindow->CreatePanel([](HWND hWnd, ID2D1HwndRenderTarget* hrt)->void {
        RECT rc;  
        GetClientRect(hWnd, &rc);
        D2DDrawSolidRect(hrt, 0, 0, rc.right, rc.bottom, VERTEXUICOLOR_MIDNIGHT);
        MainWindow->GetPanel()->Set(hWnd, hrt);

        static bool ExtraMsg = false;

        static std::shared_ptr<VinaCaptionBar>capt = std::make_shared<VinaCaptionBar>();
        capt->Set(0, 0, rc.right / gScale - 120, 40, L"Universe", VERTEXUICOLOR_MIDNIGHT, 18);
        MainWindow->GetPanel()->Add(capt);

        static std::shared_ptr<VinaFAIcon>close = std::make_shared<VinaFAIcon>();
        close->Set(rc.right / gScale - 32, 20, L"win-close",15, VERTEXUICOLOR_WHITE, [] {DestroyWindow(MainWindow->GetHandle()); PostQuitMessage(0); });
        MainWindow->GetPanel()->Add(close);

        static bool IsMaximized = false;
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
        min->Set(rc.right / gScale - 32 - 32-32, 20, L"win-min", 15, VERTEXUICOLOR_WHITE, [hWnd] {SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); });
        MainWindow->GetPanel()->Add(min);

        int ctl_x = 20; int ctl_y = 60; int ctl_w = rc.right/gScale-40; int ctl_h = 120;
        D2DDrawRoundRect(hrt, ctl_x, ctl_y, ctl_w , ctl_h, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);

        static std::shared_ptr<VinaButton>test1 = std::make_shared<VinaButton>();
        test1->Set(ctl_x+ctl_w-185, ctl_y+ctl_h-40, 80, 25, L"下载", [hWnd] {ExtraMsg = !ExtraMsg; Refresh(hWnd); },RGB( 82, 121, 251),12.5);
        MainWindow->GetPanel()->Add(test1);
        static std::shared_ptr<VinaButton>test2 = std::make_shared<VinaButton>();
        test2->Set(ctl_x + ctl_w - 95, ctl_y + ctl_h - 40, 80, 25, L"更新", [hWnd] {ExtraMsg = !ExtraMsg; Refresh(hWnd); }, RGB(82, 121, 251), 12.5);
        MainWindow->GetPanel()->Add(test2);
        D2DDrawRoundRect(hrt, ctl_x+15, ctl_y+15, 40, 40, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 30), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);
        D2DDrawText(hrt, L"轻框LightFrame" ,ctl_x + 75, ctl_y + 15, 220, 40,20, VERTEXUICOLOR_WHITE,L"Segoe UI Bold");
        D2DDrawText(hrt, L"Version:0.9.9", ctl_x + 15, ctl_y+ctl_h -28, 120, 40, 12, VERTEXUICOLOR_WHITE,L"Segoe UI",0.75f);
        //82 121 251
        /*
        const wchar_t* btntxt;
        if (ExtraMsg == false)
        {
            btntxt = L"展开";
        }
        else  btntxt = L"折叠";
        
        static std::shared_ptr<VinaButton>test1 = std::make_shared<VinaButton>();
        test1->Set(20, 60, 100, 40, btntxt, [hWnd] {ExtraMsg = !ExtraMsg; Refresh(hWnd); }, VERTEXUICOLOR_MIDNIGHTPLUS);
        MainWindow->GetPanel()->Add(test1);
        if (ExtraMsg == 1)
        {
            static std::shared_ptr<VinaMultiTextBox>test2 = std::make_shared<VinaMultiTextBox>();
            test2->SetParent(MainWindow->GetPanel());
            test2->Set(20, 120, rc.right / gScale - 40, 200, LR"(-----TEST TEXT-----
QWQ QWQ QWQ QWQ
    QWQ QWQ QWQ
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
1234567890
)", 18, VERTEXUICOLOR_WHITE, VERTEXUICOLOR_MIDNIGHTPLUS);
            MainWindow->GetPanel()->Add(test2);
            
            //D2DDrawRoundRect(hrt, 20, 120, rc.right/gScale - 40, 200, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);
            //D2DDrawText(hrt, L"Hello World\n12345678", 30, 140, rc.right / gScale - 70, 200, 18, VERTEXUICOLOR_WHITE);
            
        }
        */
        });
        
    MainWindow->SetOutFrame(VinaWindow::Client);
    MainWindow->RunFull();

    return 0;
}


