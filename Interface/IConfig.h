#ifndef ICONFIG_H
#define ICONFIG_H

//使用宏需要定义 QString _configScope 否则会找不到_configScope
#define CONFIG_KEY(NAME) _configScope + NAME
#define SAVE_CONFIG(P_SETTINGS,NAME)  P_SETTINGS->setValue(CONFIG_KEY(#NAME),NAME());

class IConfig
{
public:
    IConfig(){}
    virtual ~IConfig(){}

public:
    /**
     * @brief loadFromFile 从文件读取配置
     */
    virtual void loadSettings(class QSettings *settings) = 0;

    /**
     * @brief saveToFile 写配置到文件
     */
    virtual void saveSettings(class QSettings *settings) = 0;
};
#endif // ICONFIG_H
