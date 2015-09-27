#-------------------------------------------------
#
# Project created by QtCreator 2015-09-13T21:40:27
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = rpi
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lboost_system

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    serial.cpp \
    gpioclass.cpp

HEADERS += \
    serial.h \
    gpioclass.h
