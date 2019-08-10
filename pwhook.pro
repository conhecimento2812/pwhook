QT = core network websockets
QT -= gui

TARGET = pwchat

CONFIG += console 64bit
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    IO/OctetsStream.cpp \
    Network/GDeliveryd.cpp \
    Protocols/WorldChat.cpp \
    Settings.cpp \
    Utils.cpp \
    Workers/BroadcasterWorker.cpp \
    echoserver.cpp \
    Server.cpp \
    main.cpp

HEADERS += \
    IO/Octets.h \
    IO/OctetsStream.h \
    Network/GDeliveryd.h \
    Protocols/WorldChat.h \
    Settings.h \
    Utils.h \
    Server.h \
    Workers/BroadcasterWorker.h \
    echoserver.h

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -static-libstdc++ -static-libgcc -static
