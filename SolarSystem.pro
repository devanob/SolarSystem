TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Moon.cpp \
        OpenGlFuncTools.cpp \
        Orbital.cpp \
        Planet.cpp \
        SolarSystem.cpp \
        SpaceEnterprise.cpp \
        Star.cpp \
        StarDrawer.cpp \
        Sun.cpp \
        main.cpp

HEADERS += \
    Moon.h \
    OpenGlFuncTools.h \
    Orbital.h \
    Planet.h \
    SolarSystem.h \
    SpaceEnterprise.h \
    Star.h \
    StarDrawer.h \
    Sun.h

LIBS += -L"/usr/local/lib"
QT += opengl
CONFIG(release, debug|release): LIBS +=  -framework OpenGL  -lglut
CONFIG(debug, debug|release): LIBS +=  -framework OpenGL -lglut
INCLUDEPATH += "/usr/local/include"
DEPENDPATH += "/usr/local/include"

LIBS+= -lglut



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/Cellar/glew/2.1.0/lib/release/ -lGLEW.2.1.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/Cellar/glew/2.1.0/lib/debug/ -lGLEW.2.1.0
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/Cellar/glew/2.1.0/lib/ -lGLEW.2.1.0

INCLUDEPATH += $$PWD/../../../../../../../usr/local/Cellar/glew/2.1.0/include
DEPENDPATH += $$PWD/../../../../../../../usr/local/Cellar/glew/2.1.0/include
