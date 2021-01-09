QT += multimedia
QT += multimediawidgets
QT += widgets
QT += gui


TEMPLATE = app
TARGET = player


CONFIG += c++11 console


 INES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        dialogadd.cpp \
        main.cpp \
        player.cpp \
        playlist.cpp \
        scrolltext.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Track.h \
    TrackWidget.h \
    dialogadd.h \
    player.h \
    playlist.h \
    scrolltext.h
