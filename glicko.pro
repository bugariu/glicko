TEMPLATE = app
TARGET = glicko
INCLUDEPATH += .

CONFIG += c++14

HEADERS +=  exceptions.h \
            glicko.h \
            player.h

SOURCES +=  glicko.cpp \
            main.cpp
