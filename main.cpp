#include "mainwindow.h"

#include "sound.h"

#include <QApplication>
#include "sound.h"

int main(int argc, char *argv[])
{
    //Forces the usage of desktop OpenGL - Qt uses OpenGL ES as default
    //Attribute must be set before Q(Gui)Application is constructed:
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    //Makes a Qt application
    QApplication a(argc, argv);


    soundManager::getInstance()->initialize();


    //Makes the Qt MainWindow and shows it.
    MainWindow w;
    w.show();
    //Resize the window for your own purposes, Harry
    w.resize(1100, 600);

    int lel = a.exec();


    soundManager::getInstance()->clean();


    return lel;
}
