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
        capt->Set(0, 0, rc.right / gScale - 40, 40, L"Universe", VERTEXUICOLOR_MIDNIGHT, 18);
        MainWindow->GetPanel()->Add(capt);

        static std::shared_ptr<VinaText>close = std::make_shared<VinaText>();
        close->Set(rc.right / gScale - 32, 10, 20, 20, L"×", 24, VERTEXUICOLOR_WHITE, [] {DestroyWindow(MainWindow->GetHandle()); PostQuitMessage(0); });
        MainWindow->GetPanel()->Add(close);
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
            test2->Set(20, 120, rc.right / gScale - 40, 200, LR"(-----BEGIN PGP PUBLIC KEY BLOCK-----

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

    return 0;
}


