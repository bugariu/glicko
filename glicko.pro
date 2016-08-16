TEMPLATE = app
TARGET = glicko
INCLUDEPATH += .

CONFIG += c++14

HEADERS +=  defines.h \
            exceptions.h \
            game.h \
            glicko.h \
            player.h

SOURCES +=  main.cpp
