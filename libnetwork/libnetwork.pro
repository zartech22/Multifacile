#-------------------------------------------------
#
# Project created by QtCreator 2013-08-11T15:47:06
#
#-------------------------------------------------

QT += network

QT -= gui

BUILD_PATH = ../build
BIN_PATH = ../bin

CONFIG(release, debug|release) {
OBJECTS_DIR = $${BUILD_PATH}/release
MOC_DIR = $${BUILD_PATH}/release
RCC_DIR = $${BUILD_PATH}/release
DESTDIR = $${BIN_PATH}/release
TARGET = network
}
CONFIG(debug, debug|release) {
OBJECTS_DIR = $${BUILD_PATH}/debug
MOC_DIR = $${BUILD_PATH}/debug
RCC_DIR = $${BUILD_PATH}/debug
DESTDIR = $${BIN_PATH}/debug
TARGET = networkd
}


TEMPLATE = lib

DEFINES += NETWORK_LIBRARY

SOURCES += Network.cpp

HEADERS += Network.h\
        network_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
