#include "DesktopHelper.h"

#include <QDebug>


DesktopHelper::DesktopHelper()
    : desktopIconWnd(nullptr)
    , workerWnd(nullptr)
{
    getDesktopIconWnd();
}

DesktopHelper::~DesktopHelper()
{

}

bool DesktopHelper::createDesktopIconWnd()
{
    //发送消息，召唤WorkerW
    //参考：https://www.codeproject.com/articles/856020/draw-behind-desktop-icons-in-windows
    return SendMessageTimeout(FindWindow(L"Progman", nullptr), 0x52c, 0, 0, SMTO_NORMAL, 1000 , nullptr);
}

HWND DesktopHelper::getDesktopIconWnd()
{
    if(desktopIconWnd)
        return desktopIconWnd;

    //创建并获取 DesktopIconWnd
    if(createDesktopIconWnd())
    {
        HWND hWorkerW = nullptr;//WorkerW的句柄
        HWND hDefView = nullptr;//SHELLDLL_DefView的句柄

        //找到WorkerW类的窗口
        hWorkerW = FindWindowEx(nullptr, nullptr, L"WorkerW", nullptr);
        //通过遍历找到包含SHELLDLL_DefView的WorkerW
        while ((!hDefView) && hWorkerW)
        {
            hDefView = FindWindowEx(hWorkerW, nullptr, L"SHELLDLL_DefView", nullptr);
            workerWnd = hWorkerW;//得到WorkerW
            hWorkerW = FindWindowEx(nullptr, hWorkerW, L"WorkerW", nullptr);
        }
        //隐藏窗口，不让mainwindow被挡住
        ShowWindow(hWorkerW,0);

        desktopIconWnd = FindWindow(L"Progman",nullptr);
        qDebug()<<"WallpaperSystem:"<<"找到 desktopIconWnd = " << desktopIconWnd;
        return desktopIconWnd;
    }
    else
    {
        qDebug()<<"WallpaperSystem:"<<"创建 DesktopIconWnd 失败";
        return nullptr;
    }
}

void DesktopHelper::setDisktopParent(HWND child)
{
    setParent(child,getDesktopIconWnd());
}

void DesktopHelper::setParent(HWND chlid, HWND parent)
{
    SetParent(chlid,parent);
}
