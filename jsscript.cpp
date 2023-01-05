#include "jsscript.h"

#include <QDebug>

JSScript::JSScript()
{
    qDebug() << "JSScript | Constructor Begins";

    qDebug() << "JSScript| Constructor Ends";
}

void JSScript::sendSignal()
{
    qDebug() << "sendSignal | Begins";
    emit signal_1();
    qDebug() << "sendSignal | Ends";
//    emit signalTwo();
}

void JSScript::scriptFunction(float in)
{
    qDebug() << "scriptFunction | Begins";
    qDebug() << in;

    qDebug() << "scriptFunction | Ends";

}
