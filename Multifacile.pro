SOURCES += \
    main.cpp \
    fenetre_principale.cpp \
    CheckUpdate.cpp \
    Shuffle.cpp \
    MediumModeWindow.cpp \
    EasyModeWindow.cpp \
    HardModeWindow.cpp \
    AstuceWindow.cpp \
    Correction.cpp \
    TimeRecordMgr.cpp \
    MinCloseMenu.cpp \
    DataFileMgr.cpp

HEADERS += \
    fenetre_principale.h \
    CheckUpdate.h \
    Shuffle.h \
    MediumModeWindow.h \
    EasyModeWindow.h \
    HardModeWindow.h \
    AstuceWindow.h \
    Correction.h \
    TimeRecordMgr.h \
    MinCloseMenu.h \
    FenetrePrincipaleEnums.h \
    DataFileMgr.h

RC_FILE = Icon.rc

QT += network xml

RESOURCES += \
    ressource.qrc \

TRANSLATIONS += en.ts
