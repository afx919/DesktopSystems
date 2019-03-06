#ifndef SEARCHSYSTEM_H
#define SEARCHSYSTEM_H

#include <QObject>

#include "../Interface/ISystem.h"

class SearchSystem : public QObject, public ISystem
{
    Q_OBJECT
public:
    explicit Q_INVOKABLE SearchSystem(QObject *parent = nullptr);

public:
    void showSearchWidget();
signals:

public slots:

private:
    class SearchWidget* _searchWidget;
    class SearchSettingWidget* _searchSettingWidget;
    class SearchConfig* _searchConfig;

    // ISystem interface
public:
    virtual void loadConfig(QSettings *settings) override;
    virtual void initSystem() override;
    virtual void initSettingWidget(QTabWidget *parent) override;
    virtual void initTrayMenu(QMenu *trayMenu) override;
    virtual void saveConfig(QSettings *settings) override;
    virtual void exitSystem() override;

    virtual void setIsEnabled(const bool &value) override;
};

#endif // SEARCHSYSTEM_H
