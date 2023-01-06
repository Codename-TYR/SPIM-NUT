QT          += core gui widgets opengl qml

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

INCLUDEPATH += .
INCLUDEPATH += ./include

win32 {
    INCLUDEPATH += $(OPENAL_HOME)\include\AL
    LIBS *= $(OPENAL_HOME)\libs\Win64\libOpenAL32.dll.a
}

SOURCES += main.cpp \
    actor.cpp \
    ballcomponent.cpp \
    basecomponent.cpp \
    camera.cpp \
    collisioncomponent.cpp \
    jsscript.cpp \
    light.cpp \
    logger.cpp \
    mainwindow.cpp \
    meshcomponent.cpp \
    meshgenerator.cpp \
    octahedronball.cpp \
    renderwindow.cpp \
    scriptcomponent.cpp \
    scriptreader.cpp \
    shader.cpp \
    sound.cpp \
    texture.cpp \
    triangle.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp \
    world.cpp \
    xyz.cpp

HEADERS += \
    actor.h \
    ballcomponent.h \
    basecomponent.h \
    collisioncomponent.h \
    jsscript.h \
    light.h \
    camera.h \
    logger.h \
    mainwindow.h \
    meshcomponent.h \
    meshgenerator.h \
    objloader.h \
    octahedronball.h \
    renderwindow.h \
    scriptcomponent.h \
    scriptreader.h \
    shader.h \
    sound.h \
    texture.h \
    triangle.h \
    trianglesurface.h \
    vertex.h \
    visualobject.h \
    world.h \
    xyz.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    JS/TestScript_01.js \
    phongshader.frag \
    phongshader.vert \
    plainshader.frag \
    plainshader.vert \
    textureshader.frag \
    textureshader.vert
