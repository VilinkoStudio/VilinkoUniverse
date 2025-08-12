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
static bool UpdateMode = false;
short DownloadProgress;
enum class UpdateStatus {
    PENDING, DOWNLOADING, REPLACING, SUCCESS, ERR
};
enum class Project {
    LIGHTFRAME
};

// 全局变量:
HINSTANCE hInst;                                // 当前实例
HANDLE hMyFont;
HGLOBAL hFntMem;
struct projectInfo {
    std::wstring LatestVersion;
    std::wstring ChangeLog;
    std::wstring BuildDate;
    std::wstring InstallPath;
    std::string DownloadURL;
    ID2D1Bitmap* Icon = nullptr;
    bool HasUpdate;
};
std::unordered_map< std::wstring, projectInfo>project;
std::thread thCheckUpdate;
std::thread thUpdate;
std::mutex mutexUpdateLocalData;
UpdateStatus mUpdateStatus = UpdateStatus::PENDING;

bool CheckUpdate(Project proj) {
    switch (proj) {
    case Project::LIGHTFRAME: {
        httplib::SSLClient httpcli("api.vilinko.com");
        httplib::Params params;
        httplib::Headers headers = {
            { "Vilinko-Project", "LightFrame" }
        };
        Json::Value resultRoot;
        Json::Reader jsonReader;
        params.emplace("build_date", ws2s(project[L"lightframe"].BuildDate));
        params.emplace("project", "lightframe");

        auto httpRes = httpcli.Get("/universe/update", params, headers);
        if (!httpRes ||
            httpRes->status != httplib::StatusCode::OK_200 ||
            !jsonReader.parse(httpRes->body, resultRoot) ||
            !resultRoot.isMember("data") ||
            !resultRoot["data"].isMember("has_update") ||
            !resultRoot["data"]["has_update"].asBool()
            )
            return false;

        std::lock_guard<std::mutex> lock(mutexUpdateLocalData);
        project[L"lightframe"].LatestVersion = s2ws(resultRoot["data"]["version"].asString());
        project[L"lightframe"].ChangeLog = s2ws(resultRoot["data"]["changelog"].asString());
        project[L"lightframe"].DownloadURL = resultRoot["data"]["download_url"].asString();
        project[L"lightframe"].HasUpdate = true;
        return true;
    }
    }
    return false;
}

VinaWindow* MainWindow = new VinaWindow;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    SetDataBase();
    InitGlobalD2D();

    bool bParseSuccess = false;
    Json::Value paramsRoot;
    Json::Reader jsonReader;

    auto obj = vui::parser::fparser(LocalLFCacheA, "Main");

    const wchar_t* path = VUIGetObject(obj, "AppDir");
    const wchar_t* date = VUIGetObject(obj, "BuildDate");
    std::wstring strr = date;
    replace_all(strr, L"%20", L" ");
    date = strr.c_str();
    int lf_ver;
    obj.get("version", lf_ver);
    project[L"lightframe"].InstallPath = std::wstring(path);
    project[L"lightframe"].BuildDate = std::wstring(date);
    project[L"lightframe"].LatestVersion = version2ws(lf_ver);
    project[L"lightframe"].HasUpdate = false;

    try {
        if (jsonReader.parse(ws2s(lpCmdLine), paramsRoot) && paramsRoot.isMember("project") && paramsRoot["project"].isString()) {
            if (paramsRoot["project"].asString() == "lightframe") {
                bParseSuccess = true;

                if (CheckUpdate(Project::LIGHTFRAME))
                    IsCfg = true, UpdateMode = true;
                else return 0;
            }
        }
    }
    catch (Json::Exception e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    if (std::wstring(lpCmdLine).size() && !bParseSuccess)return 0;

    if (!std::wstring(lpCmdLine).size()) {
        thCheckUpdate = std::thread([&] {
            CheckUpdate(Project::LIGHTFRAME);
            });
        thCheckUpdate.detach();
    }

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


    VuiColorSystemInit();
    gScale = GetScreenScale();
    //LoadVinaCom();





    MainWindow->Set(100, 100, 720 * gScale, 480 * gScale, L"Vina.Class.App.Main", L"Vilinko Universe");
    MainWindow->CreatePanel([](HWND hWnd, ID2D1HwndRenderTarget* hrt)->void {
        ClearVector(btns);


        RECT rc;
        GetClientRect(hWnd, &rc);
        D2DDrawSolidRect(hrt, 0, 0, rc.right, rc.bottom, VERTEXUICOLOR_MIDNIGHT);
        MainWindow->GetPanel()->Set(hWnd, hrt);

        static int prevwinval = 0;

        int winval = rc.bottom + rc.right;

        if (winval != prevwinval)ClearVector(btns);

        prevwinval = winval;

        static double AnimateMove = 0;

        static bool isAbout = false;
        std::wstring ul_ver = std::wstring(L"Version:") + project[L"lightframe"].LatestVersion;
        if (project[L"lightframe"].Icon == nullptr)
        {
            ID2D1Bitmap* bmplf = D2DCreateIconBitmap(hrt, project[L"lightframe"].InstallPath.c_str(), 256);
            project[L"lightframe"].Icon = bmplf;
        }
        CreatePanelInfoBox(MainWindow, hrt, 1, L"轻框LightFrame", ul_ver.c_str(), [hWnd] {
            PROCESS_INFORMATION ProInfo;
            STARTUPINFO    StartInfo;
            ZeroMemory(&StartInfo, sizeof(StartInfo));
            CreateProcess(NULL, wstrcopy(project[L"lightframe"].InstallPath), NULL, NULL, FALSE, 0, NULL, NULL, &StartInfo, &ProInfo); Refresh(hWnd);
            }, [hWnd] {
                auto obj = vui::parser::fparser(LocalLFCacheA, "Main");

                const wchar_t* path = VUIGetObject(obj, "AppDir");
                const wchar_t* date = VUIGetObject(obj, "BuildDate");
                std::wstring strr = date;
                replace_all(strr, L"%20", L" ");
                date = strr.c_str();
                project[L"lightframe"].InstallPath = std::wstring(path);
                project[L"lightframe"].BuildDate = std::wstring(date);
                Json::Value paramsRoot;
                Json::Reader jsonReader;
                try {
                    if (jsonReader.parse(R"({"project":"lightframe"})", paramsRoot) && paramsRoot.isMember("project") && paramsRoot["project"].isString()) {
                        if (paramsRoot["project"].asString() == "lightframe") {

                            //InstallPath = paramsRoot["path"].asString();

                            httplib::SSLClient httpcli("api.vilinko.com");
                            httplib::Params params;
                            httplib::Headers headers = {
                                { "Vilinko-Project", "LightFrame" }
                            };
                            Json::Value resultRoot;
                            params.emplace("build_date", ws2s(project[L"lightframe"].BuildDate));
                            params.emplace("project", "lightframe");

                            auto httpRes = httpcli.Get("/universe/update", params, headers);
                            if (!httpRes ||
                                httpRes->status != httplib::StatusCode::OK_200 ||
                                !jsonReader.parse(httpRes->body, resultRoot) ||
                                !resultRoot.isMember("data") ||
                                !resultRoot["data"].isMember("has_update") ||
                                !resultRoot["data"]["has_update"].asBool()
                                )
                                return 0;

                            project[L"lightframe"].LatestVersion = s2ws(resultRoot["data"]["version"].asString());
                            project[L"lightframe"].ChangeLog = s2ws(resultRoot["data"]["changelog"].asString());
                            project[L"lightframe"].DownloadURL = resultRoot["data"]["download_url"].asString();

                        }
                    }
                }
                catch (Json::Exception e) {
                    std::cerr << e.what() << std::endl;
                    return 0;
                }

                IsCfg = true;
                AnimateMove = 0;
                for (int i = 0; i < 30; i += 1)
                {
                    AnimateMove = CalcBezierCurve(i, 0, 100, 30, .17, .67, .57, 1.29);
                    XSleep(5);
                    Refresh(hWnd);
                }
                }, project[L"lightframe"].Icon, project[L"lightframe"].HasUpdate);

            for (auto i : btns)
            {
                MainWindow->GetPanel()->Add(i);
            }

            if (IsCfg == true)
            {
                if (UpdateMode)AnimateMove = 100, UpdateMode = false;
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
                bk->Set(20, 60 + 100 - AnimateMove, L"test-left", 22, VERTEXUICOLOR_WHITE, [hWnd] {AnimateMove = 0;
                for (int i = 0; i < 30; i += 1)
                {

                    AnimateMove = -CalcBezierCurve(i, -100, 100, 30, .26, -0.25, .76, .2);
                    XSleep(5);
                    Refresh(hWnd);
                    MainWindow->KillAnimation();
                } IsCfg = false; isAbout = false; Refresh(hWnd); ExtraMsg = true; });
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
                    DrawDisplayBox2(hrt, RGB(163, 139, 251), 25, 105 + 100 - AnimateMove, 300, GetMinValue(GetMaxValue(AnimateMove * 2, 220), 1), L"沫海CimiMoly", L"\"星河如沫，映入澄曈\"\n去海岸 望星河 永远向圆满。");
                    DrawDisplayBox2(hrt, RGB(240, 141, 56), 25 + 25 + 300, 105 + 100 - AnimateMove, 300, GetMinValue(GetMaxValue(AnimateMove * 2, 220), 1), L"悠笙iYoRoy", L"「愿世间万物都能被温柔以待。」");
                    D2DDrawText(hrt, L"( 以上是参加 Vilinko Universe 的开发者。其他项目请参考相关\"关于\"页面。)\nCopyright © 2025 Vilinko Studio  |  感谢每一个为项目贡献的小伙伴！", 25, 330, rc.right / gScale, 24, GetMinValue(GetMaxValue(AnimateMove / 5, 16), 1), VERTEXUICOLOR_WHITE, L"Segoe UI", 0.8);
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
                        test2->Set(20, 155 + 100 - AnimateMove, rc.right / gScale - 40, 200, project[L"lightframe"].ChangeLog.c_str(), 18, VERTEXUICOLOR_WHITE, VERTEXUICOLOR_MIDNIGHTPLUS);
                        MainWindow->GetPanel()->Add(test2);

                        //D2DDrawRoundRect(hrt, 20, 120, rc.right/gScale - 40, 200, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);
                        //D2DDrawText(hrt, L"Hello World\n12345678", 30, 140, rc.right / gScale - 70, 200, 18, VERTEXUICOLOR_WHITE);


                        static std::shared_ptr<VinaFAIcon>nxt = std::make_shared<VinaFAIcon>();

                        nxt->Set(rc.right / gScale - 25 - 100, 120 + 360 - AnimateMove, 100, L"test-right-upd", 22, VERTEXUICOLOR_WHITE, [hWnd] {
                            ExtraMsg = false;
                            GlobalAnimationCount++;
                            MainWindow->InitAnimation();
                            Refresh(hWnd);
                            thUpdate = std::thread([] {
                                mUpdateStatus = UpdateStatus::PENDING;
                                std::string host, path;
                                std::regex url_regex(R"((https?)://([^/]+)(/.*)?)", std::regex::icase);
                                std::smatch match;
                                if (std::regex_match(project[L"lightframe"].DownloadURL, match, url_regex)) {
                                    host = match[2].str();
                                    path = match[3].str().empty() ? "/" : match[3].str();
                                }
                                httplib::Client httpcli(host);
                                httpcli.set_follow_location(true);
                                mUpdateStatus = UpdateStatus::DOWNLOADING;
                                auto res = httpcli.Get(path, [](size_t len, size_t total) {
                                    DownloadProgress = (len * 1.0 / total) * 100 + 1;
                                    return true;
                                    }
                                );
                                if (!res) {
                                    mUpdateStatus = UpdateStatus::ERR;
                                    return 0;
                                }
                                mUpdateStatus = UpdateStatus::REPLACING;
                                WaitForLightFrameExit(project[L"lightframe"].InstallPath);
                                XSleep(500);
                                std::ofstream WriteFile(project[L"lightframe"].InstallPath, std::ios::binary);
                                WriteFile << res->body;
                                WriteFile.close();
                                PROCESS_INFORMATION ProInfo;
                                STARTUPINFO    StartInfo;
                                ZeroMemory(&StartInfo, sizeof(StartInfo));
                                CreateProcess(NULL, wstrcopy(project[L"lightframe"].InstallPath), NULL, NULL, FALSE, 0, NULL, NULL, &StartInfo, &ProInfo);
                                mUpdateStatus = UpdateStatus::SUCCESS;
                                MainWindow->KillAnimation();
                                return 0;
                                });
                            });
                        MainWindow->GetPanel()->Add(nxt);
                    }
                    else
                    {
                        static std::shared_ptr<VinaProgress>notice = std::make_shared<VinaProgress>();

                        switch (mUpdateStatus) {
                        case UpdateStatus::ERR: {
                            notice->Set(20, 100 + 100 - AnimateMove, rc.right / gScale - 40, 30, DownloadProgress, RGB(220, 40, 35), L"发生错误");
                            break;
                        }
                        case UpdateStatus::SUCCESS: {
                            notice->Set(20, 100 + 100 - AnimateMove, rc.right / gScale - 40, 30, DownloadProgress, RGB(35, 134, 54), L"完成！");
                            break;
                        }
                        default: {
                            notice->Set(20, 100 + 100 - AnimateMove, rc.right / gScale - 40, 30, DownloadProgress, RGB(65, 174, 134), L"正在更新...");
                            break;
                        }
                        }

                        MainWindow->GetPanel()->Add(notice);

                        static int ani = 0;
                        ani++;
                        double animove = CalcBezierCurve(ani, 0, 200, 100, .27, .04, .79, .98);
                        if (ani > 99)ani = 0;

                        if (mUpdateStatus != UpdateStatus::SUCCESS && mUpdateStatus != UpdateStatus::ERR)
                            D2DDrawCircleArc(hrt, rc.right / gScale / 2 - 7, 120 + 160 - AnimateMove, 15, VERTEXUICOLOR_SEA, animove, 3);

                        std::wstring stepmsg;
                        switch (mUpdateStatus) {
                        case UpdateStatus::PENDING: {
                            stepmsg = L"等待中...";
                            break;
                        }
                        case UpdateStatus::DOWNLOADING: {
                            stepmsg = L"正在下载";
                            break;
                        }
                        case UpdateStatus::REPLACING: {
                            stepmsg = L"正在应用更新";
                            break;
                        }
                        case UpdateStatus::SUCCESS: {
                            stepmsg = L"完成！";
                            break;
                        }
                        }
                        D2DDrawText2(hrt, stepmsg.c_str(), -2, 120 + 200 - AnimateMove, rc.right / gScale, 20, 14, VERTEXUICOLOR_WHITE, L"Segoe UI", 1, true);
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
            more->Set(rc.right / gScale - 32 - 32 - 32 - 25, 20, L"test-more3", 15, VERTEXUICOLOR_WHITE, [hWnd] {isMenu = true; GlobalAnimationCount += 1; MainWindow->InitAnimation(); });
            MainWindow->GetPanel()->Add(more);


            if (isMenu == true)
            {
                static int ani = 0;
                static double animove = 0;
                if (ani > 96 && ani < 100) { GlobalAnimationCount -= 1; }
                else if (ani > 96) {}
                else {
                    ani += 6;
                    animove = CalcBezierCurve(ani, 0, 120, 100, .54, .65, .61, .99);
                }
                static std::shared_ptr<VinaBarrier>layer = std::make_shared<VinaBarrier>();
                layer->Set(0, 0, rc.right / gScale, rc.bottom / gScale, [] {isMenu = false; ani = 0; });
                MainWindow->GetPanel()->Add(layer);

                CompGdiD2D(hWnd, hrt, [rc](HWND h, HDC hrt)->void {
                    AreaBlur3(hrt, { (int)(rc.right - (32 + 32 + 32 + 25) * gScale),(int)(25 * gScale),(int)((animove / 1.1) * gScale),(int)((animove / 3.2) * gScale) }, 3, 2, 0);
                    });
                D2DDrawRoundRect(hrt, rc.right / gScale - (32 + 32 + 32 + 25) - 1, 23, (animove / 1.1) + 2, animove / 3.2, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 0.75, 2, VuiFadeColor(VERTEXUICOLOR_MIDNIGHTPLUS, 20));

                static std::shared_ptr<VinaButton>test1 = std::make_shared<VinaButton>();
                test1->Set(rc.right / gScale - (32 + 32 + 32 + 25) + 6, 23 + 6, (animove / 1.1) - 12, animove / 5, L"关于", [hWnd] {
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

                    }, VERTEXUICOLOR_MIDNIGHTPLUS, GetMinValue2(GetMaxValue2(animove / 6, 12.5), 2));
                MainWindow->GetPanel()->Add(test1);
            }
        });

    MainWindow->SetOutFrame(VinaWindow::Client);
    MainWindow->RunFull();

    return 0;
}


