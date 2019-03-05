#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QList>
#include <QMetaObject>
#include <QDebug>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QDir>

#include "MainWindowConfig.h"
#include "../DataSheet.h"
#include "../Interface/ISystem.h"
#include "WallpaperSystem/WallpaperWidget.h"
#include "../WallpaperSystem/WallpaperSystem.h"

static QList<QMetaObject> _SystemTypes =
{
    {WallpaperSystem::staticMetaObject},
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , _mainWindowConfig(new MainWindowConfig(this))
  , _systemTrayIcon(new QSystemTrayIcon(this))
  , _isRealClose(false)
{
    ui->setupUi(this);

    _settings = new QSettings(G_SETTING_FILE_NAME,QSettings::Format::IniFormat,this);

    _mainWindowConfig->loadSettings(_settings);

    _systems.clear();
    
    //初始化tabWidget
    ui->tab_settings->clear();

    for(auto systemMetaObjects : _SystemTypes)
    {
        auto systemObject = systemMetaObjects.newInstance(Q_ARG(QObject*,this));
        if(systemObject)
        {
            auto system = dynamic_cast<ISystem*>(systemObject);
            if(system)
            {
                system->loadConfig(_settings);
                system->initSystem();
                system->initSettingWidget(ui->tab_settings);
                _systems.push_back(system);
            }
        }
    }

    //初始化托盘
    initTrayIcon();

    //初始化菜单栏
    initMenuBar();
}

void MainWindow::initTrayIcon()
{
    _systemTrayIcon->setIcon(QIcon(":/SystemTrayIcon.png"));
    _systemTrayIcon->setToolTip(tr("桌面插件"));

    //初始化托盘右键菜单
    auto trayMenu = new QMenu(this);
    QAction* action = nullptr;

    action = new QAction(tr("主页面"),trayMenu);
    connect(action,&QAction::triggered,this,&MainWindow::show);
    trayMenu->addAction(action);

    action = new QAction(tr("退出"),trayMenu);
    connect(action,&QAction::triggered,[&]()
    {
        _isRealClose = true;
        this->close();
    });
    trayMenu->addAction(action);

    _systemTrayIcon->setContextMenu(trayMenu);

    /*
    connect(_systemTrayIcon,&QSystemTrayIcon::activated,[&](auto reason)
    {
        qDebug()<<reason;
        if(reason == QSystemTrayIcon::ActivationReason::DoubleClick)
        {
            this->show();
        }
    });
    */

    _systemTrayIcon->hide();
}

void MainWindow::initMenuBar()
{
    //绑定事件
    connect(ui->menu_setting_auto_start_action,&QAction::triggered,[&]()
    {
        _mainWindowConfig->setAutoStart(!_mainWindowConfig->autoStart());
    });

    connect(_mainWindowConfig,&MainWindowConfig::autoStartChanged,[&](auto isAutoStart)
    {
        //更新菜单
        if(isAutoStart)
        {
            ui->menu_setting_auto_start_action->setIcon(QIcon(":/yes.png"));
        }
        else
        {
            ui->menu_setting_auto_start_action->setIcon(QIcon(""));
        }

        //更新注册表实现开机自启
        this->setAutoStart(isAutoStart);
    });

    //初始化UI状态
    _mainWindowConfig->setAutoStart(_mainWindowConfig->autoStart());
    /*
    if(_mainWindowConfig->autoStart())
    {
        ui->menu_setting_auto_start_action->setIcon(QIcon(":/yes.png"));
    }*/
}

void MainWindow::setAutoStart(bool isAutoStart)
{
#ifdef Q_OS_WIN32
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    QString appName = QApplication::applicationName();

    if(isAutoStart)
    {
        reg.setValue(appName,appPath);
    }
    else
    {
        reg.remove(appName);
    }
#endif

#ifdef Q_OS_LINUX
    //写.desktop文件, 到/etc/xdg/autostart目录下
#endif

#ifdef Q_OS_MACOS
    if (isAutoStart){
        LSSharedFileListRef loginItems = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
        CFURLRef url = (CFURLRef)[NSURL fileURLWithPath:QStringToNSString(appPath)];
        LSSharedFileListItemRef item = LSSharedFileListInsertItemURL(loginItems, kLSSharedFileListItemLast, NULL, NULL, url, NULL, NULL);
        CFRelease(item);
        CFRelease(loginItems);
    }else{
        UInt32 seedValue;
        CFURLRef thePath;
        LSSharedFileListRef loginItems = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
        CFArrayRef loginItemsArray = LSSharedFileListCopySnapshot(loginItems, &seedValue);
        for (id item in (NSArray *)loginItemsArray) {
            LSSharedFileListItemRef itemRef = (LSSharedFileListItemRef)item;
            if (LSSharedFileListItemResolve(itemRef, 0, (CFURLRef*) &thePath, NULL) == noErr){
                if ([[(NSURL *)thePath path] hasPrefix:QStringToNSString(appPath)]){
                    LSSharedFileListItemRemove(loginItems, itemRef);
                }
                CFRelease(thePath);
            }
        }
        CFRelease(loginItemsArray);
        CFRelease(loginItems);
    }
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
    if(_settings)
    {
        _settings->sync();
        _settings->deleteLater();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    if(!_isRealClose)
    {
        hide();
        event->ignore();
    }
    else
    {
        _mainWindowConfig->saveSettings(_settings);
        _systemTrayIcon->hide();
        _systemTrayIcon->deleteLater();
    }

    for(auto system : _systems)
    {
        if(system)
        {
            system->saveConfig(_settings);
            if(_isRealClose)
            {
                system->exitSystem();
            }
        }
    }
}
