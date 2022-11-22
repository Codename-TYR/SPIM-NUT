QT          += core gui widgets opengl

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
    camera.cpp \
    light.cpp \
    logger.cpp \
    mainwindow.cpp \
    nutobject.cpp \
    octahedronball.cpp \
    renderwindow.cpp \
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
    light.h \
    camera.h \
    logger.h \
    mainwindow.h \
    nutobject.h \
    objloader.h \
    octahedronball.h \
    renderwindow.h \
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
    phongshader.frag \
    phongshader.vert \
    plainshader.frag \
    plainshader.vert \
    textureshader.frag \
    textureshader.vert
