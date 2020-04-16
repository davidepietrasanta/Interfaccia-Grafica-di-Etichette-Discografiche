QT += core
QT += network
QT += widgets
QT += charts

TARGET = Artists_List

CONFIG   -= app_bundle
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

HEADERS += \
    CoreObject.h \
    MainWindow.h \
    downloader.h

SOURCES += \
    downloader.cpp \
    main.cpp
