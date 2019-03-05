#include <QApplication>
#include <QFont>
#include <QDebug>

#include "SingleApplication.h"
#include "SystemsLoader/MainWindow.h"

#ifdef QT_NO_DEBUG
#include "Common/QDebugMessageToFile.h"
#ifdef __cplusplus
extern "C"{
#endif
void gLogMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QDebugMessageToFile::getInstance()->logMsgOutput(type,context,msg);
}
#ifdef __cplusplus
}
#endif
#endif


int main(int argc, char *argv[])
{
    //开启高DPI缩放
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#else
    #error ("Mini Qt Version Is 5.6")
#endif
    
#ifdef QT_NO_DEBUG
    qInstallMessageHandler(gLogMsgOutput);
#endif
    
    SingleApplication app(argc, argv);

    if(!app.isRunning())
    {
        MainWindow w;

#ifdef QT_NO_DEBUG
        int nRet = app.exec();
        qInstallMessageHandler(gLogMsgOutput);
        return nRet;
#else
        return app.exec();
#endif
        
    }
    return 0;
}
