SOURCES += \
    main.cpp \
    fenetre_principale.cpp \
    CheckUpdate.cpp \
    Shuffle.cpp \
    spinBox.cpp \
    MediumModeWindow.cpp \
    EasyModeWindow.cpp \
    HardModeWindow.cpp \
    AstuceWindow.cpp \
    Correction.cpp \
    TimeRecordMgr.cpp \
    MinCloseMenu.cpp

HEADERS += \
    fenetre_principale.h \
    CheckUpdate.h \
    Shuffle.h \
    spinBox.h \
    MediumModeWindow.h \
    EasyModeWindow.h \
    HardModeWindow.h \
    AstuceWindow.h \
    Correction.h \
    TimeRecordMgr.h \
    MinCloseMenu.h \
    FenetrePrincipaleEnums.h

RC_FILE = Icon.rc

QT += network

RESOURCES += \
    ressource.qrc \
