SOURCES += \
    main.cpp \
    CheckUpdate.cpp \
    Shuffle.cpp \
    MediumModeWindow.cpp \
    EasyModeWindow.cpp \
    HardModeWindow.cpp \
    AstuceWindow.cpp \
    Correction.cpp \
    TimeRecordMgr.cpp \
    MinCloseMenu.cpp \
    DataFileMgr.cpp \
    MainWindow.cpp

HEADERS += \
    CheckUpdate.h \
    Shuffle.h \
    MediumModeWindow.h \
    EasyModeWindow.h \
    HardModeWindow.h \
    AstuceWindow.h \
    Correction.h \
    TimeRecordMgr.h \
    MinCloseMenu.h \
    DataFileMgr.h \
    MainWindow.h \
    MainWindowEnums.h

RC_FILE = Icon.rc

QT += network xml

RESOURCES += \
    ressource.qrc \

TRANSLATIONS += en.ts
