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
    Menu.cpp \
    MainWidget.cpp

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
    MainWindowEnums.h \
    CustomMessageBox.h \
    Menu.h \
    MainWidget.h

RC_FILE = Icon.rc

QT += network xml

RESOURCES += \
    ressource.qrc \

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
