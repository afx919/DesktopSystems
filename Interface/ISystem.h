#ifndef ISYSTEM_H
#define ISYSTEM_H


class ISystem
{
public:
    ISystem(bool isEnabled = true) :isEnabled(isEnabled){}
    virtual ~ISystem(){}
public:
    
    virtual bool getIsEnabled() const
    {
        return isEnabled;
    }

    virtual void setIsEnabled(const bool &value)
    {
        isEnabled = value;
    }


public:
    /*
     调用顺序：
         1、loadConfig
         2、initSystem
         3、initSettingWidget
         4、saveConfig
         5、exitSystem
    */

    /**
     * @brief loadConfig 加载配置
     * @param settings
     */
    virtual void loadConfig(class QSettings* settings) = 0;


    /**
     * @brief initSystem 初始化系统
     */
    virtual void initSystem() = 0;

    /**
     * @brief initSettingWidget 初始化系统的设置界面
     * @param parent
     */
    virtual void initSettingWidget(class QTabWidget* parent) = 0;

    /**
     * @brief initTrayMenu 初始化托盘菜单
     * @param trayMenu
     */
    virtual void initTrayMenu(class QMenu* trayMenu) = 0;

    /**
     * @brief saveConfig 保存
     * @param settings
     */
    virtual void saveConfig(class QSettings* settings) = 0;

    /**
     * @brief exitSystem 退出系统
     */
    virtual void exitSystem() = 0;
    
protected:
    bool isEnabled;//是否启用该系统
};

#endif // ISYSTEM_H
