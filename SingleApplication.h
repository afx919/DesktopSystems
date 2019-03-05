#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H


#include <QApplication>

class SingleApplication : public QApplication
{
    Q_OBJECT

public:
    explicit SingleApplication(int &argc, char **argv);

    /**
     * @brief isRunning 检查是否已經有一个实例在运行
     * @return true - 有实例运行， false - 没有实例运行
     */
    bool isRunning();

signals:

public slots:
    /**
     * @brief newLocalConnection 有新连接时触发
     * 通过socket通讯实现程序单实例运行，监听到新的连接时触发该函数
     */
    void newLocalConnection();

private:
    /**
     * @brief initLocalConnection 初始化本地连接
     * 通过socket通讯实现程序单实例运行
     * 如果连接不上server，则创建，否则退出
     */
    bool initLocalConnection();

    /**
     * @brief newLocalServer 创建服务端(LocalServer)
     */
    void newLocalServer();

private:
    /**
     * @brief bRunning 是否已经有实例在运行
     */
    bool _isRunning;

    /**
     * @brief localServer 本地socket Server
     */
    class QLocalServer *localServer;

    /**
     * @brief serverName 服务名称
     */
    static const QString serverName;
};

#endif // SINGLEAPPLICATION_H
