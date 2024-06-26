QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        GameEngine.cpp \
        HumanPlayer.cpp \
        ComputerPlayer.cpp \
        RandomStrategy.cpp \
        SmartStrategy.cpp \
        FileManager.cpp
        # Add other source files here

HEADERS += \
        StrategyFactory.h \
        mainwindow.h \
        GameEngine.h \
        HumanPlayer.h \
        ComputerPlayer.h \
        RandomStrategy.h \
        SmartStrategy.h \
        FileManager.h
        # Add other header files here

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
