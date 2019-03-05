#include "MainWindowConfig.h"

#include <QSettings>


const QString MainWindowConfig::_configScope("MainWindowConfig/");

MainWindowConfig::MainWindowConfig(QObject *parent) : QObject(parent)
  , IConfig()
  , _autoStart(true)
{

}

bool MainWindowConfig::autoStart() const
{
    return _autoStart;
}

void MainWindowConfig::setAutoStart(bool autoStart)
{
    _autoStart = autoStart;
    emit autoStartChanged(autoStart);
}

void MainWindowConfig::loadSettings(QSettings *settings)
{
    QVariant retData;

    retData = settings->value(CONFIG_KEY("autoStart"),true);
    if(retData.canConvert<bool>())
    {
        setAutoStart(retData.toBool());
    }
}

void MainWindowConfig::saveSettings(QSettings *settings)
{
    //保存配置
    settings->setValue(CONFIG_KEY("autoStart"),autoStart());
}
