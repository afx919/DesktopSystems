#ifndef ICONFIG_H
#define ICONFIG_H

//从配置文件加载属性
#define SAVE_PROPERTYS(P_SETTINGS) \
    QString className = metaObject()->className(); \
    className += "/"; \
    for(int i = 0; i < metaObject()->propertyCount(); i++) \
    { \
        P_SETTINGS->setValue(className + (metaObject()->property(i).name()),this->property(metaObject()->property(i).name())); \
    }

//从配置文件写入属性
#define LOAD_PROPERTYS(P_SETTINGS) \
    QString className = metaObject()->className(); \
    className += "/"; \
    for(int i = 0; i < metaObject()->propertyCount(); i++) \
    { \
        QString key = className + (metaObject()->property(i).name()); \
        if(settings->contains(key)) \
        { \
            setProperty(metaObject()->property(i).name(),settings->value(key)); \
        } \
    }


#include <QMetaObject>
#include <QMetaProperty>

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
