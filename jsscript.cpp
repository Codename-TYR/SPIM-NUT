#include "jsscript.h"

#include <QDebug>

JSScript::JSScript()
{
    qDebug() << __FUNCTION__ " | Constructor Begins";

    qDebug() << __FUNCTION__ " | Constructor Ends";
}

void JSScript::sendSignal()
{
    qDebug() << __FUNCTION__ " | Begins";
    emit signal_1();
    qDebug() << __FUNCTION__ " | Ends";
//    emit signalTwo();
}

void JSScript::scriptFunction(float in)
{
    qDebug() << __FUNCTION__ " | Begins";
    qDebug() << in;

    qDebug() << __FUNCTION__ " | Ends";

}
