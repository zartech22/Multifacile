SOURCES += \
    main.cpp \
    fenetre_principale.cpp \
    bouton.cpp \
    fen_correction.cpp \
    CheckUpdate.cpp \
    Shuffle.cpp \
    spinBox.cpp \
    MediumModeWindow.cpp \
    EasyModeWindow.cpp \
    HardModeWindow.cpp

HEADERS += \
    fenetre_principale.h \
    bouton.h \
    fen_correction.h \
    CheckUpdate.h \
    Shuffle.h \
    spinBox.h \
    modeEnum.h \
    MediumModeWindow.h \
    EasyModeWindow.h \
    HardModeWindow.h
RC_FILE = Icon.rc

QT += network
