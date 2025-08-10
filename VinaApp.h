#pragma once

#include "resource.h"
#include "LightFrame.Data.h"

#include <TlHelp32.h>

void SetDataBase()
{
    wchar_t test[260] = L"";
    GetAppdataPath(LocalData);
    GetAppdataPath(LocalAppData);
    GetAppdataPath(test);
    GetAppdataPathA(LocalDataA);
    GetAppdataPath(LocalLFData);
    GetAppdataPathA(LocalLFDataA);


    wcscat(LocalData, L"\\Vilinko\\VisUniverse");
    strcat(LocalDataA, "\\Vilinko\\VisUniverse");
    wcscat(LocalLFData, L"\\LightFrame");
    strcat(LocalLFDataA, "\\LightFrame");

    wcscpy(LocalData2, LocalData);
    wcscpy(LocalRes, LocalData);
    wcscpy(LocalCache, LocalData);
    strcpy(LocalCacheA, LocalDataA);
    wcscpy(LocalLFCache, LocalLFData);
    strcpy(LocalLFCacheA, LocalLFDataA);

    wcscpy(LocalCom, LocalData);
    wcscpy(LocalCards, LocalData);
    strcpy(LocalComA, LocalDataA);
    wcscat(LocalCom, L"\\Vilinko\\VisUniverse\\Components");
    wcscat(LocalCards, L"\\Vilinko\\VisUniverse\\Cards");
    strcat(LocalComA, "\\Vilinko\\VisUniverse\\Components");

    wcscat(LocalCache, L"\\Vilinko\\VisUniverse\\VisUniverse.vui");
    strcat(LocalCacheA, "\\Vilinko\\VisUniverse\\VisUniverse.vui");
    wcscat(LocalLFCache, L"\\LightFrame.vui");
    strcat(LocalLFCacheA, "\\LightFrame.vui");
    wcscat(LocalRes, L"\\Vilinko\\VisUniverse\\reslib");

    SetTagW(LocalData2, L"\\", L"/");
    SetTagW(LocalCache2, L"\\", L"/");
    if (_waccess(LocalData, 0) == -1)
    {
        mkdirs(LocalData2);
    }
}

std::string ws2s(const std::wstring& wstr) {
    if (wstr.empty()) {
        return "";
    }

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

std::wstring version2ws(int version) {
    if (version < 0) {
        return L"";
    }

    std::wstring str = std::to_wstring(version);
    size_t len = str.length();
    std::wstring result;

    if (len == 1) {
        result = L"0.0." + str;
    }
    else if (len == 2) {
        result = L"0." + str.substr(0, 1) + L"." + str.substr(1, 1);
    }
    else if (len == 3) {

        result = L"0." + str.substr(0, 1) + L"." + str.substr(1, 2);
    }
    else if (len == 4) {

        result = str.substr(0, 1) + L"." + str.substr(1, 1) + L"." + str.substr(2, 2);
    }
    else if (len >= 5) {

        result = str.substr(0, 2) + L"." + str.substr(2, len - 4) + L"." + str.substr(len - 2, 2);
    }

    return result;
}

void WaitForLightFrameExit(std::wstring strFileName) {
    HWND hWndLF = FindWindow(L"LIGHTFRAME", L"LightFrame");
    PROCESSENTRY32  pe32;
    HANDLE hSnaphot;
    HANDLE hApp;
    DWORD dProcess = 0;
    hSnaphot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    Process32First(hSnaphot, &pe32);
    do {
        if (lstrcmpi(pe32.szExeFile, strFileName.c_str()) == 0) {
            dProcess = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(hSnaphot, &pe32));
    hApp = OpenProcess(
        PROCESS_VM_OPERATION | SYNCHRONIZE, FALSE, dProcess);
    ::SendMessage(hWndLF, 0xff3, 0, 1);
}