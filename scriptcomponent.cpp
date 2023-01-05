#include "scriptcomponent.h"

#include <QCoreApplication>
#include <QDebug>       //Using qDebug
#include <QFile>        //Reading from file
#include <QJSEngine>    //The script engine itself!

#include "jsscript.h"


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

    JSScriptObject = new JSScript();

    QJSValue objectTest = mEngine.newQObject(JSScriptObject);

    mEngine.globalObject().setProperty("Owner", objectTest);

    // Function that calls all the slot connecting
    QJSValue cFunc = mEngine.evaluate("SetupInputBindings");
    cFunc.call();


    JSScriptObject->sendSignal();

    //Make a C++ variable to the function
    QJSValue func = mEngine.evaluate("takeMap");
//    and the arguments
    QJSValueList args;
//    Read in arguments: 3 is the first (a) 8.9 is the last (b)
    std::map<int, bool> inMap;
    inMap[0] = true;
    inMap[1] = false;
    inMap[2] = true;
    inMap[3] = false;

    std::string tempString;

    for (auto i = inMap.begin(); i != inMap.end(); i++)
    {
        int testKey = i->first;
        bool test = i->second;
//        tempString.append((std::string)testKey);
//        tempString.append((static_cast<std::string>(testKey));
        tempString.append(std::to_string (testKey));
        tempString.append(std::to_string (test));
        tempString.append(" ");
//        tempString.append(test);
    }

    args << tempString.c_str();
//    Call the function and hold the return value
    QJSValue result = func.call(args);
//    Check the return value (toNumber() makes a double of it)
//    float test = result.to();
//    float test = result.toNumber();
    qDebug() << result.toString() << "\n";
//    qDebug() << result.toNumber() << "\n";







    qDebug() << __FUNCTION__ " | Constructor | Ends";
}

void ScriptComponent::ComponentTick()
{

}
