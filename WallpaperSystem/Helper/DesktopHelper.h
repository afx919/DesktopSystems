#ifndef DESKTOPHELPER_H
#define DESKTOPHELPER_H

#include <qt_windows.h>

#include "../../Common/Singleton.h"

/**
 * @brief The DesktopHelper class
 * 
 * Windows桌面操作帮助类
 */

class DesktopHelper : public Singleton<DesktopHelper>
{
private:
    DesktopHelper();
    friend Singleton<DesktopHelper>;

public:
    virtual ~DesktopHelper();

public:
    /**
     * @brief getDesktopIconWnd
     * 
     * 获取壁纸窗口的句柄
     * @return 
     */
    HWND getDesktopIconWnd();
    
    /**
     * @brief setDisktopParent
     * 
     * 设置父窗口为桌面
     * @param child
     */
    void setDisktopParent(HWND child);
    
    /**
     * @brief setParent
     * 
     * 设置父窗口
     * @param chlid 子窗口
     * @param parent 父窗口
     */
    void setParent(HWND chlid,HWND parent);

private:
    /**
     * @brief createDesktopIconWnd
     * 
     * 创建壁纸窗口
     * @return 
     */
    bool createDesktopIconWnd();


private:
    HWND desktopIconWnd;
    HWND workerWnd;
};

#endif // DESKTOPHELPER_H
