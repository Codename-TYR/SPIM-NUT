#include "scriptcomponent.h"

#include <QCoreApplication>
#include <QDebug>       //Using qDebug
#include <QFile>        //Reading from file
#include <QJSEngine>    //The script engine itself!

#include "jsscript.h"


ScriptComponent::ScriptComponent(QString fileName)
    :mJSFilePath{fileName}
{
    qDebug() << "ScriptComponent | Constructor | Begins";
    InitializeComponentType();

    // QFile holds the relevant JS-File for reading
    QFile JSScriptFile(mJSFilePath);

    if (!JSScriptFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error | ScriptComponent | Failed to read file:" << fileName;
    }
    else
    {
        // Reads the JS-ScriptFile
        QTextStream JSstream(&JSScriptFile);
        // Holds the contents of the JS-ScriptFile
        QString JSContents = JSstream.readAll();

        JSScriptFile.close();

        mEngine.evaluate(JSContents, mJSFilePath);
    }

    JSScriptObject = new JSScript();

    QJSValue objectTest = mEngine.newQObject(JSScriptObject);

    mEngine.globalObject().setProperty("Owner", objectTest);

    // Function that calls all the slot connecting
    QJSValue cFunc = mEngine.evaluate("connectToSlots");
    cFunc.call();


    JSScriptObject->sendSignal();



    qDebug() << "ScriptComponent | Constructor | Ends";
}

void ScriptComponent::ComponentTick(float deltaTime)
{

}
