#include "SingleApplication.h"

#include <qt_windows.h>

#include <QWidget>
#include <QMainWindow>
#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>

//初始化LocalServer的名字
const QString SingleApplication::serverName = "DesktopSystems";

SingleApplication::SingleApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , _isRunning(false)
    , localServer(nullptr)
{
    if(initLocalConnection())
    {
        //初始化字体
        QFont font;
        font.setPixelSize(12);
        font.setFamily("msyh");
        setFont(font);
    }
}

bool SingleApplication::isRunning()
{
    return _isRunning;
}


void SingleApplication::newLocalConnection()
{
    QLocalSocket *socket = localServer->nextPendingConnection();
    if (!socket)
        return;
    socket->waitForReadyRead(1000);

    QTextStream stream(socket);
    //在此处处理消息
    if(stream.readAll().trimmed() == "show")
    {
        for(auto widget : allWidgets())
        {
            QMainWindow* mainWindow = dynamic_cast<QMainWindow*>(widget);
            if(mainWindow)
            {
                if (mainWindow->isMinimized())
                {
                    mainWindow->showNormal();
                }
                //设置窗口置顶
                ::SetWindowPos(HWND(mainWindow->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
                ::SetWindowPos(HWND(mainWindow->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

                mainWindow->show();
                mainWindow->activateWindow();
                break;
            }
        }
    }

    socket->flush();
    socket->close();
    socket->deleteLater();
}


bool SingleApplication::initLocalConnection()
{
    _isRunning = false;
    QLocalSocket socket;
    socket.connectToServer(serverName);
    if(socket.waitForConnected(500))
    {
        _isRunning = true;
        // 其他处理，如：将启动参数发送到服务端
        QTextStream stream(&socket);
        //TODO 在此处给实例发送消息   stream<<xxx;
        stream<<"show";

        stream.flush();
        socket.waitForBytesWritten();
        socket.flush();
        socket.close();
        return false;
    }

    //连接不上服务器，就创建一个
    newLocalServer();
    return true;
}

void SingleApplication::newLocalServer()
{
    localServer = new QLocalServer(this);
    connect(localServer, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));

    //监听
    if(!localServer->listen(serverName))
    {
        // 此时监听失败，可能是程序崩溃时,残留进程服务导致的,移除之
        if(localServer->serverError() == QAbstractSocket::AddressInUseError)
        {
            qDebug()<<"listen error = QAbstractSocket::AddressInUseError";
            qDebug()<<"relisten...";
            QLocalServer::removeServer(serverName); // <-- 重点
            localServer->listen(serverName); // 再次监听
        }
    }
}

