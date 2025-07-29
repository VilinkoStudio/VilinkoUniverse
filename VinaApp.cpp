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
    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VINAAPP));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VINAAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VINAAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   InitGlobalD2D();
   VuiColorSystemInit();
   gScale = GetScreenScale();
   LoadVinaCom();
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    // 执行应用程序初始化:
	MainWindow->Set(100, 100, 720 * gScale, 480 * gScale, L"Vina.Class.App.Main", L"Test");
	MainWindow->CreatePanel([](HWND hWnd, ID2D1HwndRenderTarget* hrt)->void {
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2DDrawSolidRect(hrt, 0, 0, rc.right, rc.bottom, VERTEXUICOLOR_MIDNIGHT);
		MainWindow->GetPanel()->Set(hWnd, hrt);

		static bool ExtraMsg = false;

		static std::shared_ptr<VinaCaptionBar>capt = std::make_shared<VinaCaptionBar>();
		capt->Set(0, 0, rc.right / gScale - 40, 40, L"Universe", VERTEXUICOLOR_MIDNIGHT, 18);
		MainWindow->GetPanel()->Add(capt);
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		static std::shared_ptr<VinaText>close = std::make_shared<VinaText>();
		close->Set(rc.right / gScale - 32, 10, 20, 20, L"×", 24, VERTEXUICOLOR_WHITE, [] {DestroyWindow(MainWindow->GetHandle()); PostQuitMessage(0); });
		MainWindow->GetPanel()->Add(close);
		const wchar_t* btntxt;
		if (ExtraMsg == false)
		{
			btntxt = L"展开";
	return 0;
		else  btntxt = L"折叠";
		static std::shared_ptr<VinaButton>test1 = std::make_shared<VinaButton>();
		MainWindow->GetPanel()->Add(test1);

		if (ExtraMsg == 1)
		{
			static std::shared_ptr<VinaMultiTextBox>test2 = std::make_shared<VinaMultiTextBox>();
			test2->SetParent(MainWindow->GetPanel());
			test2->Set(20, 120, rc.right / gScale - 40, 200, LR"(-----BEGIN PGP PUBLIC KEY BLOCK-----
    WNDCLASSEXW wcex;
 mQINBGhAYQABEADuU + Gm4CkjJAtEXusC5wL + 4XpxtFdY37KO + ELhJd6wCV1PIHjr
   KtDM8K2BfBZBRQ6FUbp3m2EBTyJWxITngGXehGIhPPo0NnwoFlOcbHojOkEUo2uc
        EZqfysWcNcjJI / IRAN5ojURj47sXDf7khov1ZyiD7cr6gZqtkvyQY53H8V6extAh
       8Ey1SVCuZMhtfwom4pXnqJwxY5oj5EhKf7csPz9uEh6tTd8VpYv2SnSkxDhULt7O
    rqT4qz4jhfMCqYq2rRjwGyL5Vc98MxG50oBk7WmYjD4C7VVmnkdA8hs2clVgSx1W
       dmoxz4FlTa81pv5zhrXaoUCRdBznKg2sUMao + TkhCJKdCFWH / 6gFrCDj + NvXtP3R
        Aaf6zJicP4PYEZJ0setUN679yklsuj6DiW3OPbFcjwMIlGlPHQYFsnhRVIBjXEQe
     a4FuhpPOa9LdOebvBgK75G9FpXVpPN0wsvV2OkQq2a4MF14djxWVkMarmFe6fkCj
     N8GwNr7kr39qsgXzwWisJZMCIwRn3nUOCl3am3iXH6DLezPFMJ7lpHLaDQARAQAB
                tCdLYWd1cmEgaVlvUm95IDx5b3Jpc29jdXRlMjMzQGdtYWlsLmNvbT6JAk4EEwEK
      ADgWIQQ + zP / ewstMuNqAib6a8vLgPOj9ZwUCaEBhAAIbAwULCQgHAgYVCgkICwIE
                FgIDAQIeAQIXgAAKCRCa8vLgPOj9Zyw5D / 0b6fznIVeggg2lDO4QeBPrUQy3pwMY
        MGLtVwRLieXI7ntnGUXQi2IOAee00TLGGY1qc5hQf0e8bjXeB6pzy78Ute + / AtN8
                Cl47dPufIJYejcPq3ZjCNQHB + c9kCvdi4Jc38mbRgZ8jMpqWQfybVuqaz / b6Eu / j
                zm4NkBY + wJzWo4kl4YHoVCxcXyGrakAVslmGXYVKoo / yQNuXRLZFB4E6Vt0d1Ly4
           v4oasyB4uBdsAT6//pTmWwTW/K0NstMxF/CiOSb3S/wTMcMsfGnS9US5DBvlXOhn
                QqChBCkwtT1 + d6XeZ34lM0W4Ee + hh0XMG / tSdHhzWJ7dMcUfdeRpuvBbL8wM8uCN
                / KKf8gWb + oWhC5HabtvNuhp6hFb6A / v6n6AneCim4DnPw9SZVRZGXxXU2Kc3bPtM
                eWCOmIlClgIxjpknwDsYhEoRbFokub3mB9DWjzWdO0W7iDWaRcXpA9qkzbICFjil
         bXbWMJIXiFdC2NxMXrtQJK9xzFAFvgch6VYw2 / 9gxrBdOtJGfdIlg8ayW / rZWkl6
                E5FpJAObZq8LR / 3okO5jtWMMXOFxnpVW / l2dGdTvUS2A69OpA2rMNqub9wu2hCqw
                PLtqk76wwqNATPI4uBmvopKEVumqQ9ojLW4aOsi1hl6MDnGkjCmh7TmqRazcTpoB
                gJpTh0IGltuwfbkCDQRoQGEAARAArXe2 / iSyVAnFxvRyRgqwLYoDfn2ang0iIbNm
                4ETR3zQahAdNlKEjadPXTR5BM1ctyf + oXqCihYPkyxdOnK3UYTH4uCBMEoWlnrn +
                PjEKdnWCeo98J4Km98Guo1a1JGruaUfNzdhCkAFjh1ZKwxbjwyGHbp1TV6Hbl / FT
                / YfXH2IR4f2VxY3pFHptnw6W3llAaN0RcpT86RVRhcPZ + c + 6MvDuHPN1M6tOQUj /
                fcqJMJA6B9uT0Y / onKjs7UhzZTemImqV + orVDhjTuamjOTDEZ2Snu9KEMt7NqQGG
                p0VLsw5LR61A8albmpfGIcBThEQaoylx3OTm9bJN4wTQiDXYaCWQoMun8ARUU / jM
                oevrydPqcaODpCXUfRPJMFZJbV5xBSN9Rm50YWk0He / ++GnkkFpbRD1rPkIt1LDd
                EbJDdBecJ4Cn3 + 19LI + eSuVZDpGRrEUC4kg / 69QO96t7VH3BAYNfshVsO90kvIbn
                51D + eOCAhOn3OVP0edlHvKqazzraqo7iCLVRzdx739xyWxRcHaZhzBWQZN3Fv87U
                fevwdFIcpNhF3j + e6KjFL4iFNIn73 / e8YqxNQcuoqeK5Dd1cvRCg6tn / styCJX0v
                / 9HYqO9Lovq6n22TEJofHHLWtB381nKQ / tLWHii9lqcJ8 + fmUKotoob9Cgyp8D7T
                nj7NTP8AEQEAAYkCNgQYAQoAIBYhBD7M / 97Cy0y42oCJvpry8uA86P1nBQJoQGEA
                AhsMAAoJEJry8uA86P1nCTcQAI0x8fZuT5E2L40aaR / Wt9n + Jd5TXwob4 / Lp0Tz1
                63cyMsAUO8JukHHMnachX4ePTk2g9clBKOXKsIbbP8D4nkBeOJwtolcw9jm6nDGO
                PBpSanb4OGEPvuG//pbDR0H/5arWVTPjChE7YylMZL0aRPZ8PqkGblnBvD2miSqi
                Afluuljd55vl3ZmMqp3nPpSzEA + DTBEGbAXRiE / 8XAKvfCdNNQY892Ctu + BCPn2B
                9QJ2F8HgAdV9JeyI01zbuwGd / wUQFnPVdXOSAf2f7n8i5CMfajnqKnMtjSEeb6tU
                RMWBYceo9 / Le386Gu3pLfYPJkuNWbkCqqySGlFK + JFtYYnb0Wlus29ypDEUEC / eu
                xkrUtlJtGNAw4E798uJ29lHW877zc2KREazyhJYa0lkbFPlzbftamDeYv8Jzw3qt
                q4zTWPx57f + 3bC1O4kyqOmnNGqP5wAgsz1Xox7c3v6sz6WPAkj7w + x5xUXCN + hpw
                zbtRNcZbs40kokH2jpzW1vU1QNa1e57qjLvzj8PqX5DDR8Sk25gldMIJNTwsnuDu
                ODmDOmBqSXWQfscmncdtb / tzYhxBj9qn1GMYH0cewgYgiekXjdnI5LK4XS7mahUq
wKszzUhVZweZqUQO06tORKW01jYfmdyEYfrQQpZSfKqxgfvSo2lP7J0PorLV2yJv
hClv
 = IuSR
                ---- - END PGP PUBLIC KEY BLOCK---- - )", 18, VERTEXUICOLOR_WHITE, VERTEXUICOLOR_MIDNIGHTPLUS);
			MainWindow->GetPanel()->Add(test2);
			/*
			D2DDrawRoundRect(hrt, 20, 120, rc.right/gScale - 40, 200, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);
			D2DDrawText(hrt, L"Hello World\n12345678", 30, 140, rc.right / gScale - 70, 200, 18, VERTEXUICOLOR_WHITE);
			*/
		}
		});
	MainWindow->SetOutFrame(VinaWindow::Client);
	MainWindow->RunFull();
   gScale = GetScreenScale();
   LoadVinaCom();
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    // 执行应用程序初始化:
   if (!hWnd)
   {
      return FALSE;
   }
   SetTimer(hWnd, 11, 16, 0);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {


        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_SIZE:
    {
        D2D1_SIZE_U resize;
        resize.height = HIWORD(lParam);
        resize.width = LOWORD(lParam);
        if (pRT != NULL)pRT->Resize(resize);
        break;
    }
    case  WM_MOUSEMOVE:
    {
        RECT winrc;
        GetClientRect(hWnd, &winrc);
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = hWnd;
        TrackMouseEvent(&tme);
        if (NewUIPanel->AddEvent(pt, vinaEvent::mouseOver))Refresh(hWnd);
        break;
    }
    case WM_MOUSELEAVE:{
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt, vinaEvent::mouseUnfocus);
        Refresh(hWnd);
        break;
    }
    case WM_TIMER:
    {
        switch (wParam)
        {
        case 10:
        {

            RefreshWindow(hWnd);
    WNDCLASSEXW wcex;
            break;
        }
        case 11:
        {
            if (GlobalAnimationCount >= 1)
            {
                RefreshWindow(hWnd);
            }
            break;
        }
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt, vinaEvent::mouseDown);
        break;
    }
    case WM_LBUTTONUP:
    {
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt,vinaEvent::mouseUp);
        break;
    }
    case WM_RBUTTONUP:
    {
        SendRClickEvent(hWnd, wParam, lParam);
    }
   gScale = GetScreenScale();
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            CreateD2DPanel(hWnd, MainUI);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
   if (!hWnd)
   {
      return FALSE;
   }
   SetTimer(hWnd, 11, 16, 0);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {


        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_SIZE:
    {
        D2D1_SIZE_U resize;
        resize.height = HIWORD(lParam);
        resize.width = LOWORD(lParam);
        if (pRT != NULL)pRT->Resize(resize);
        break;
    }
    case  WM_MOUSEMOVE:
    {
        RECT winrc;
        GetClientRect(hWnd, &winrc);
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = hWnd;
        TrackMouseEvent(&tme);
        if (NewUIPanel->AddEvent(pt, vinaEvent::mouseOver))Refresh(hWnd);
        break;
    }
    case WM_MOUSELEAVE:{
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt, vinaEvent::mouseUnfocus);
        Refresh(hWnd);
        break;
    }
    case WM_TIMER:
    {
        switch (wParam)
        {
        case 10:
        {

            RefreshWindow(hWnd);
    WNDCLASSEXW wcex;
            break;
        }
        case 11:
        {
            if (GlobalAnimationCount >= 1)
            {
                RefreshWindow(hWnd);
            }
            break;
        }
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt, vinaEvent::mouseDown);
        break;
    }
    case WM_LBUTTONUP:
    {
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt,vinaEvent::mouseUp);
        break;
    }
    case WM_RBUTTONUP:
    {
        SendRClickEvent(hWnd, wParam, lParam);
    }
   gScale = GetScreenScale();
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            CreateD2DPanel(hWnd, MainUI);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
   if (!hWnd)
   {
      return FALSE;
   }
   SetTimer(hWnd, 11, 16, 0);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))

#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {


        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_SIZE:
    {
        D2D1_SIZE_U resize;
        resize.height = HIWORD(lParam);
        resize.width = LOWORD(lParam);
        if (pRT != NULL)pRT->Resize(resize);
        break;
    }
    case  WM_MOUSEMOVE:
    {
        RECT winrc;
        GetClientRect(hWnd, &winrc);
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = hWnd;
        TrackMouseEvent(&tme);
        if (NewUIPanel->AddEvent(pt, vinaEvent::mouseOver))Refresh(hWnd);
        break;
    }
    case WM_MOUSELEAVE:{
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt, vinaEvent::mouseUnfocus);
        Refresh(hWnd);
        break;
    }
    case WM_TIMER:
    {
        switch (wParam)
        {
        case 10:
        {

            RefreshWindow(hWnd);

            break;
        }
        case 11:
        {
            if (GlobalAnimationCount >= 1)
            {
                RefreshWindow(hWnd);
            }
            break;
        }
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt, vinaEvent::mouseDown);
        break;
    }
    case WM_LBUTTONUP:
    {
        vinaPoint pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        NewUIPanel->AddEvent(pt,vinaEvent::mouseUp);
        break;
    }
    case WM_RBUTTONUP:
    {
        SendRClickEvent(hWnd, wParam, lParam);
    }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            CreateD2DPanel(hWnd, MainUI);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
