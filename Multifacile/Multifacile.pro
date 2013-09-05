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
    Menu.cpp

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
    Menu.h

RC_FILE = Icon.rc

QT += network xml

RESOURCES += \
    ressource.qrc \

TRANSLATIONS += en.ts

BUILD_PATH = ../build
BIN_PATH = ../bin

CONFIG(release, debug|release) {
OBJECTS_DIR = $${BUILD_PATH}/release
MOC_DIR = $${BUILD_PATH}/release
RCC_DIR = $${BUILD_PATH}/release
DESTDIR = $${BIN_PATH}/release
DEFINES += RELEASE
}
CONFIG(debug, debug|release) {
OBJECTS_DIR = $${BUILD_PATH}/debug
MOC_DIR = $${BUILD_PATH}/debug
RCC_DIR = $${BUILD_PATH}/debug
DESTDIR = $${BIN_PATH}/debug
DEFINES += DEBUG
}

win32:CONFIG(release, debug|release): LIBS += -L$${BIN_PATH}/release/ -lnetwork
else:win32:CONFIG(debug, debug|release): LIBS += -L$${BIN_PATH}/debug/ -lnetworkd
else:unix: LIBS += -L$$OUT_PWD/../network/ -lnetworkd

INCLUDEPATH += $$PWD/../network
DEPENDPATH += $$PWD/../network
