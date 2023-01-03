#include "scriptingcomponent.h"

#include <QJSEngine>                //The script engine itself!
#include <QFile>                    //Reading from file

#include <QDebug>


ScriptingComponent::ScriptingComponent(QObject *parent, QString JSFileName)
    : QObject{parent}
{
    JSEngine = new QJSEngine;
    QFile ScriptFile(JSFileName);

    if (!ScriptFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error | " __FUNCTION__ " | File Not Found!";
    }
    qDebug() << "Debug | " __FUNCTION__ " | File Found!";
    QTextStream stream(&ScriptFile);
    QString contents = stream.readAll();
    ScriptFile.close();
    JSEngine->evaluate(contents, JSFileName);

    QJSValue func1 = JSEngine->evaluate("print2");
    QJSValue func1Result = func1.call();
    double x = func1Result.toNumber();
//    int x = func1Result.toInt();
//    float x = func1Result.toNumber();
    qDebug() << x;
}

void ScriptingComponent::sendSignal()
{
//    qDebug() << __FUNCTION__ "Hello";
    qDebug() << "Hello0";
    emit SignalOne();
}

int ScriptingComponent::TestFunction()
{
    qDebug() << "Hello9";
    return 0;
}

void ScriptingComponent::ScriptFunction(float In)
{
    qDebug() << "Hello1";
    In ++;
}

void ScriptingComponent::PrivateFunction()
{
    qDebug() << "Hello2";

}

void ScriptingComponent::NotifyX()
{
    qDebug() << "Hello3";

}

