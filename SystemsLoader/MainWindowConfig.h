#ifndef MAINWINDOWCONFIG_H
#define MAINWINDOWCONFIG_H

#include <QObject>

#include "../Interface/IConfig.h"

class MainWindowConfig : public QObject, public IConfig
{
    Q_OBJECT
public:
    explicit MainWindowConfig(QObject *parent = nullptr);

public:
    Q_PROPERTY(bool autoStart READ autoStart WRITE setAutoStart NOTIFY autoStartChanged)

public:
    bool autoStart() const;
    void setAutoStart(bool autoStart);

signals:
    void autoStartChanged (bool autoStart);
public slots:

private:
    bool _autoStart;

    // IConfig interface
public:
    void loadSettings(QSettings *settings);
    void saveSettings(QSettings *settings);
};

#endif // MAINWINDOWCONFIG_H
