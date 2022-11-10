#include "mainwindow.h"
#include "soundmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Forces the usage of desktop OpenGL - Qt uses OpenGL ES as default
    //Attribute must be set before Q(Gui)Application is constructed:
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    //Makes a Qt application
    QApplication a(argc, argv);

    SoundManager::getInstance()->init();

    //Makes the Qt MainWindow and shows it.
    MainWindow w;
    w.show();


    int lel = a.exec();

    SoundManager::getInstance()->cleanUp();

    return lel;
}
