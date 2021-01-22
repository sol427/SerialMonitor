QT += widgets serialport

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DEPENDPATH += .
INCLUDEPATH += .


HEADERS += \
    serialmonitor.h

SOURCES += \
    main.cpp \
    serialmonitor.cpp
