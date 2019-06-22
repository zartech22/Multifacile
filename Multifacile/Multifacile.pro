SOURCES += \
    main.cpp \
    CheckUpdate.cpp \
    Shuffle.cpp \
    MediumModeWindow.cpp \
    EasyModeWindow.cpp \
    HardModeWindow.cpp \
    Correction.cpp \
    MinCloseMenu.cpp \
    DataFileMgr.cpp \
    MainWindow.cpp \
    CustomMessageBox.cpp \
    MainWidget.cpp \
    ProblemWidget.cpp \
    AbstractModeWindow.cpp

HEADERS += \
    CheckUpdate.h \
    Shuffle.h \
    MediumModeWindow.h \
    EasyModeWindow.h \
    HardModeWindow.h \
    Correction.h \
    MinCloseMenu.h \
    DataFileMgr.h \
    MainWindow.h \
    CustomMessageBox.h \
    Menu.h \
    MainWidget.h \
    ProblemWidget.h \
    Include.h \
    AbstractModeWindow.h


QT += network xml sql widgets

RESOURCES += \
    ressource.qrc \

RC_FILE += Icon.rc

TRANSLATIONS += en.ts

BUILD_PATH = ../build
BIN_PATH = ../bin

CONFIG(release, debug|release) {
OBJECTS_DIR = $${BUILD_PATH}/release/Multifacile
MOC_DIR = $${BUILD_PATH}/release/Multifacile
RCC_DIR = $${BUILD_PATH}/release/Multifacile
DESTDIR = $${BIN_PATH}/release
DEFINES += RELEASE
LIBS += -L$${BIN_PATH}/release/ -lnetwork
}
CONFIG(debug, debug|release) {
OBJECTS_DIR = $${BUILD_PATH}/debug/Multifacile
MOC_DIR = $${BUILD_PATH}/debug/Multifacile
RCC_DIR = $${BUILD_PATH}/debug/Multifacile
DESTDIR = $${BIN_PATH}/debug
DEFINES += DEBUG
LIBS += -L$${BIN_PATH}/debug/ -lnetworkd
}

INCLUDEPATH += $$PWD/../network
DEPENDPATH += $$PWD/../network
