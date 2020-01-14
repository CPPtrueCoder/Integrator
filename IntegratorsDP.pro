TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        OPRS_2.cpp \
        Object.cpp \
        Pendulum.cpp \
        Spring.cpp \
        arenstorf.cpp \
        dormand_prince.cpp

HEADERS += \
    Object.h \
    Pendulum.h \
    Spring.h \
    arenstorf.h \
    dormand_prince.h
