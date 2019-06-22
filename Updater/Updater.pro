QT += network widgets

HEADERS += \
    Updater.h

SOURCES += \
    Updater.cpp \
    main.cpp

RC_FILE += Icon.rc


RESOURCES += \
    ressource.qrc
win32:!CONFIG(no-elevation){
    QMAKE_LFLAGS *= /MANIFESTUAC:"level=\'requireAdministrator\'"
}

BUILD_PATH = ..\\build
BIN_PATH = ..\\bin

CONFIG(release, debug|release) {
OBJECTS_DIR = $${BUILD_PATH}\\release\\Updater
MOC_DIR = $${BUILD_PATH}\\release\\Updater
RCC_DIR = $${BUILD_PATH}\\release\\Updater
DESTDIR = $${BIN_PATH}\\release
DEFINES += RELEASE
LIBS += -L$${BIN_PATH}\\release\\ -lnetwork
}
CONFIG(debug, debug|release) {
OBJECTS_DIR = $${BUILD_PATH}\\debug\\Updater
MOC_DIR = $${BUILD_PATH}\\debug\\Updater
RCC_DIR = $${BUILD_PATH}\\debug\\Updater
DESTDIR = $${BIN_PATH}\\debug
DEFINES += DEBUG
LIBS += -L$${BIN_PATH}\\debug\\ -lnetworkd
}

INCLUDEPATH += $$PWD\\..\\network
DEPENDPATH += $$PWD\\..\\network
