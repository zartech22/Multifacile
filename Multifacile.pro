SOURCES += \
    main.cpp \
    fenetre_principale.cpp \
    fen_correction.cpp \
    CheckUpdate.cpp \
    Shuffle.cpp \
    spinBox.cpp \
    MediumModeWindow.cpp \
    EasyModeWindow.cpp \
    HardModeWindow.cpp \
    AstuceWindow.cpp \
    Correction.cpp \
    TimeRecordMgr.cpp

HEADERS += \
    fenetre_principale.h \
    fen_correction.h \
    CheckUpdate.h \
    Shuffle.h \
    spinBox.h \
    modeEnum.h \
    MediumModeWindow.h \
    EasyModeWindow.h \
    HardModeWindow.h \
    AstuceWindow.h \
    Correction.h \
    TimeRecordMgr.h

RC_FILE = Icon.rc

QT += network phonon

RESOURCES += \
    ressource.qrc
