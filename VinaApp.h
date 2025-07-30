#pragma once

#include "resource.h"
#include "LightFrame.Data.h"

void SetDataBase()
{
    wchar_t test[260] = L"";
    GetAppdataPath(LocalData);
    GetAppdataPath(LocalAppData);
    GetAppdataPath(test);
    GetAppdataPathA(LocalDataA);


    wcscat(LocalData, L"\\Vilinko\\VisUniverse");
    strcat(LocalDataA, "\\Vilinko\\VisUniverse");

    wcscpy(LocalData2, LocalData);
    wcscpy(LocalRes, LocalData);
    wcscpy(LocalCache, LocalData);
    strcpy(LocalCacheA, LocalDataA);

    wcscpy(LocalCom, LocalData);
    wcscpy(LocalCards, LocalData);
    strcpy(LocalComA, LocalDataA);
    wcscat(LocalCom, L"\\Vilinko\\VisUniverse\\Components");
    wcscat(LocalCards, L"\\Vilinko\\VisUniverse\\Cards");
    strcat(LocalComA, "\\Vilinko\\VisUniverse\\Components");

    wcscat(LocalCache, L"\\Vilinko\\VisUniverse\\VisUniverse.vui");
    strcat(LocalCacheA, "\\Vilinko\\VisUniverse\\VisUniverse.vui");
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