#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T10:40:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BreakReminder
TEMPLATE = app


SOURCES += main.cpp\
    traytimer.cpp \
    tray.cpp \
    isystemstatenotify.cpp \
    systemidlemonitor.cpp \
    systemidlemonitorimpl.cpp \
    xpsystemidlemonitorimpl.cpp
unix {
    SOURCES += linuxsystemidlemonitorimpl.cpp
}

HEADERS  += \
    traytimer.h \
    tray.h \
    isystemstatenotify.h \
    systemidlemonitor.h \
    systemidlemonitorimpl.h \
    xpsystemidlemonitorimpl.h
unix {
    HEADERS += linuxsystemidlemonitorimpl.h
}

FORMS    +=

RESOURCES += \
    BreakReminder.qrc

unix {
    LIBS += -lXss
}


release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/qrc
UI_DIR = $$DESTDIR/ui

