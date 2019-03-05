#include "MainWindowConfig.h"

#include <QSettings>

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
    LOAD_PROPERTYS(settings);
}

void MainWindowConfig::saveSettings(QSettings *settings)
{
    SAVE_PROPERTYS(settings);
}
