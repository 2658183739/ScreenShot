QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ScreenShotwidget.cpp \
    imgocrclient.cpp \
    infolabel.cpp \
    main.cpp \
    pinchartwindow.cpp \
    screenshot.cpp \
    tool_bar.cpp

HEADERS += \
    ScreenShotwidget.h \
    imgocrclient.h \
    infolabel.h \
    pinchartwindow.h \
    screenshot.h \
    tool_bar.h

FORMS += \
    screenshot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

DISTFILES +=

