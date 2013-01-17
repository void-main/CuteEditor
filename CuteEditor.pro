#-------------------------------------------------
#
# Project created by QtCreator 2013-01-17T09:47:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuteEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    templatehandler.cpp \
    templatesdockwidget.cpp

HEADERS  += mainwindow.h \
    templatehandler.h \
    templatesdockwidget.h

FORMS    += mainwindow.ui \
    templatesdockwidget.ui

OTHER_FILES += \
    images/action_undo.png \
    images/action_save_as.png \
    images/action_save.png \
    images/action_redo.png \
    images/action_paste.png \
    images/action_open.png \
    images/action_new.png \
    images/action_info.png \
    images/action_exit.png \
    images/action_cut.png \
    images/action_copy.png

RESOURCES += \
    CuteEditor.qrc
