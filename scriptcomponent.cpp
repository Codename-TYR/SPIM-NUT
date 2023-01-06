#include "scriptcomponent.h"

#include <QCoreApplication>
#include <QDebug>       //Using qDebug
#include <QFile>        //Reading from file
#include <QJSEngine>    //The script engine itself!

#include "jsscript.h"
#include "renderwindow.h"


ScriptComponent::ScriptComponent(QString fileName)
    :mJSFilePath{fileName}
{
    qDebug() << __FUNCTION__ " | Constructor | Begins";
    InitializeComponentType();

    // QFile holds the relevant JS-File for reading
    QFile JSScriptFile(mJSFilePath);

    if (!JSScriptFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error | " __FUNCTION__ " | Failed to read file:" << fileName;
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

    JSScriptObject = new JSScript(this);

    QJSValue objectTest = mEngine.newQObject(JSScriptObject);

    mEngine.globalObject().setProperty("Owner", objectTest);

    // Function that calls all the slot connecting
    QJSValue cFunc = mEngine.evaluate("SetupInputBindings");
    cFunc.call();


    JSScriptObject->sendSignal();

    qDebug() << __FUNCTION__ " | Constructor | Ends";
}

void ScriptComponent::ComponentTick(float deltaTime)
{
//    qDebug() << __FUNCTION__;

    CurrentInputsMap = RenderWindow::GetCurrentInputsMap();

    //Make a C++ variable to the function
    QJSValue func = mEngine.evaluate("Tick");
//    and the arguments
    QJSValueList args;
//    Read in arguments: 3 is the first (a) 8.9 is the last (b)
//    std::map<int, bool> inMap;
//    inMap[0] = true;
//    inMap[1] = false;
//    inMap[2] = true;
//    inMap[3] = false;

    std::string tempString;

    for (auto i = CurrentInputsMap.begin(); i != CurrentInputsMap.end(); i++)
    {
        int testKey = i->first;
        bool test = i->second;
        tempString.append(std::to_string (testKey));
        tempString.append(",");
        tempString.append(std::to_string (test));
        tempString.append(" ");
    }

    args << tempString.c_str() << deltaTime;
//    Call the function and hold the return value
    QJSValue result = func.call(args);
//    func.call(args);
//    Check the return value (toNumber() makes a double of it)
//    float test = result.to();
//    float test = result.toNumber();
//    qDebug() << result.toString() << "\n";
//    qDebug() << result.toNumber() << "\n";

//    JSScriptObject->sendSignal_1();
//    JSScriptObject->sendSignalTick_1();
//    JSScriptObject->sendSignalTick_2();
//    JSScriptObject->sendSignalTick_3();
//    JSScriptObject->sendSignalTick_4();



}



//void ScriptComponent::ComponentTick(float deltaTime)
//{

//}
