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
