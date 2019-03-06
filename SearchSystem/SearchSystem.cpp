#include "SearchSystem.h"

#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QTabWidget>

#include "SearchWidget.h"
#include "SearchSettingWidget.h"
#include "SearchConfig.h"

SearchSystem::SearchSystem(QObject *parent) : QObject(parent)
  , ISystem ()
  , _searchWidget(new SearchWidget())
  , _searchSettingWidget(nullptr)
  , _searchConfig(new SearchConfig(this))
{

    connect(_searchConfig,&SearchConfig::isEnabledChanged,this,&SearchSystem::setIsEnabled);
}

void SearchSystem::showSearchWidget()
{
    _searchWidget->showNormal();
}

void SearchSystem::loadConfig(QSettings *settings)
{
    _searchConfig->loadSettings(settings);
    _searchWidget->setSearchConfig(_searchConfig);
}

void SearchSystem::initSystem()
{

}

void SearchSystem::initSettingWidget(QTabWidget *parent)
{
    _searchSettingWidget = new SearchSettingWidget(_searchConfig,parent);
    parent->addTab(_searchSettingWidget,tr("搜索"));
}

void SearchSystem::initTrayMenu(QMenu *trayMenu)
{
    QAction* action = new QAction(tr("全局搜索"),trayMenu);
    connect(action,&QAction::triggered,this,&SearchSystem::showSearchWidget);
    trayMenu->addAction(action);
}

void SearchSystem::saveConfig(QSettings *settings)
{
    _searchConfig->saveSettings(settings);
}

void SearchSystem::exitSystem()
{
    _searchWidget->close();
}

void SearchSystem::setIsEnabled(const bool &value)
{
    if(value)
    {

    }
    else
    {

    }
}
