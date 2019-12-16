TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Object.cpp \
        dormand_prince.cpp \
        main.cpp

HEADERS += \
    Object.h \
    dormand_prince.h
