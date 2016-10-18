#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T23:21:52
#
#-------------------------------------------------

QT       += core gui

RC_FILE = dbg_res.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interface_dbg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    core_decompiler.cpp \
    debugger.cpp \
    interfacedisasm.cpp \
    interfacememory.cpp \
    dialogboxwaitfordisasm.cpp

HEADERS  += mainwindow.h \
    core_decompiler.h \
    sdk/SDK.h \
    debugger.h \
    vm_instruction_set.h \
    types.h \
    memdump.h \
    interfacedisasm.h \
    _global.h \
    interfacememory.h \
    dialogboxwaitfordisasm.h

FORMS    += mainwindow.ui \
    dialogboxwaitfordisasm.ui

TITAN_PATH = $$[TITAN_PATH]
isEmpty(TITAN_PATH):TITAN_PATH = "C:/Users/JOAO/Documents/QtProjects/interface_dbg/sdk"
LIBS += -L$$TITAN_PATH -lTitanEngine_x86
INCLUDEPATH += $$TITAN_PATH


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sdk/ -lTitanEngine_x86
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sdk/ -lTitanEngine_x86d

#INCLUDEPATH += $$PWD/sdk
#DEPENDPATH += $$PWD/sdk

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/sdk/libTitanEngine_x86.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/sdk/libTitanEngine_x86d.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/sdk/TitanEngine_x86.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/sdk/TitanEngine_x86d.lib

RESOURCES += \
    resources.qrc
