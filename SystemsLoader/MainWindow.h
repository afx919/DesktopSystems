#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initTrayIconSettingMenu();
    void initTrayIconExitMenu();
    void initMenuBar();

protected:
    void setAutoStart(bool isAutoStart);

public:
    virtual void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;

    /**
     * @brief _mainWindowConfig 主窗口配置对象
     */
    class MainWindowConfig* _mainWindowConfig;

    /**
     * @brief _settings 保存数据的Setting对象
     */
    class QSettings* _settings;

    /**
     * @brief _systemTrayIcon 托盘图标对象
     */
    class QSystemTrayIcon* _systemTrayIcon;

    /**
     * @brief isRealClose 为true时关闭程序
     */
    bool _isRealClose;
private:
    QList<class ISystem*> _systems;
};

#endif // MAINWINDOW_H
