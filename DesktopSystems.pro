#-------------------------------------------------
#
# Project created by QtCreator 2019-02-25T17:26:58
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets

include (SystemsLoader/SystemsLoader.pri)
include (WallpaperSystem/WallpaperSystem.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesktopSystems
TEMPLATE = app

#设置tu图标
RC_ICONS = icon.ico

# 版本号
VERSION = 1.0.1

# 语言
# 0x0004 表示 简体中文
# 详见 https://msdn.microsoft.com/en-us/library/dd318693%28vs.85%29.aspx
RC_LANG = 0x0004

# 公司名
#QMAKE_TARGET_COMPANY = XXXX公司

# 产品名称
QMAKE_TARGET_PRODUCT = 桌面插件

# 详细描述
QMAKE_TARGET_DESCRIPTION = 桌面插件,包含许多桌面小工具

# 版权
#QMAKE_TARGET_COPYRIGHT = Copyright(C) 2019 XXXXX


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
    SingleApplication.cpp \
    Common/QDebugMessageToFile.cpp

HEADERS += \
    SingleApplication.h \
    Common/QDebugMessageToFile.h \
    Common/Singleton.h \
    Interface/ISystem.h \
    Interface/IConfig.h \
    DataSheet.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
