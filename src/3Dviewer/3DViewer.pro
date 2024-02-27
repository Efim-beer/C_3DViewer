QT       += core gui openglwidgets
#openglwidgets
include(../QtGifImage-master/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QT       += gifimage
CONFIG += c++17

#LIBS += -lopengl32 -lglu32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += GL_SILENCE_DEPRECATION

SOURCES += \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \
    s21_3d.c

HEADERS += \
    glview.h \
    mainwindow.h \
    s21_3d.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    gifimage/qtgifimage.pri
