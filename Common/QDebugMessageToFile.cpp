#include "QDebugMessageToFile.h"

#ifdef QT_NO_DEBUG

#include <QMutex>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>


QDebugMessageToFile::QDebugMessageToFile()
    : log("")
{
    
}

QDebugMessageToFile::~QDebugMessageToFile()
{
    saveLogFile();
}

void QDebugMessageToFile::saveLogFile()
{
    static int callNum = 0;
    QDir dir;
    dir.mkpath("Logs");

    QFile file;
    QString path = QString("Logs/log%1.log").arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));
    file.setFileName(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString erinfo = file.errorString();
        callNum++;
        if(callNum > 10)
            return;
        else
        {
            saveLogFile();
            return ;
        }
    }
    
    QTextStream out(&file);
    out << log;
    file.close();
    callNum = 0;
}

void QDebugMessageToFile::logMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    static QMutex  mutex;//日志代码互斥锁
    mutex.lock();
    
    QByteArray localMsg = msg.toLocal8Bit();
    
    log.append(QDateTime::currentDateTime().toString("hh:mm:ss") + ":");
    switch (type) {
    case QtDebugMsg:
        log.append(msg);
        break;
    case QtInfoMsg:
        log.append(msg);
        break;
    case QtWarningMsg:
        log.append(msg);
        break;
    case QtCriticalMsg:
        log.append(msg);
        break;
    case QtFatalMsg:
        log.append(msg);
        abort();
    }

    log.append("\n");
    
    mutex.unlock();
}

#endif
