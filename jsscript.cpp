#include "jsscript.h"

#include <QDebug>
#include <functional>

#include "qjsvalue.h"
#include "renderwindow.h"
#include "scriptcomponent.h"
//#include <function>




JSScript::JSScript(ScriptComponent* InComponent)
    :mOwningComponent{InComponent}/*, mEngine{InEngine}*/
{
    InputMap = RenderWindow::GetCurrentInputsMap();
    qDebug() << __FUNCTION__ " | Constructor Begins";

//    SignalVectorSetup();

     QFile JSScriptFile(mOwningComponent->GetJSFilePath());


    if (!(JSScriptFile).open(QIODevice::ReadOnly))
    {
        qDebug() << "Error | " __FUNCTION__ " | Failed to read file:" << mOwningComponent->GetJSFilePath();
    }
    else
    {
        // Reads the JS-ScriptFile
        QTextStream JSstream(&JSScriptFile);
        // Holds the contents of the JS-ScriptFile
        QString JSContents = JSstream.readAll();

        JSScriptFile.close();

        mEngine.evaluate(JSContents, mOwningComponent->GetJSFilePath());


        QJSValue objectTest = mEngine.newQObject(this);
        mEngine.globalObject().setProperty("Owner", objectTest);
    }



    //Make a C++ variable to the function
//    QJSValue func = mEngine.evaluate("takeMap");
//    and the arguments
//    QJSValueList args;
////    Read in arguments: 3 is the first (a) 8.9 is the last (b)
//    std::map<int, bool> inMap;
//    inMap[0] = true;
//    inMap[1] = false;
//    inMap[2] = true;
//    inMap[3] = false;

//    std::string tempString;

//    for (auto i = inMap.begin(); i != inMap.end(); i++)
//    {
//        int testKey = i->first;
//        bool test = i->second;
//        tempString.append(std::to_string (testKey));
//        tempString.append(std::to_string (test));
//        tempString.append(" ");
//    }

//    args << tempString.c_str();
//    QJSValue result = func.call(args);
//    qDebug() << result.toString() << "\n";

    QJSValue cFunc = mEngine.evaluate("connectToSlot");
    cFunc.call();


    qDebug() << __FUNCTION__ " | Constructor Ends";
}

void JSScript::SignalVectorSetup()
{
//    SignalVector.push_back(&JSScript::signal_1);






//    SignalTickVector.push_back(&JSScript::signal_tick_1);

}

void JSScript::sendSignal()
{
    qDebug() << __FUNCTION__ " | Begins";

//    std::vector<std::function<void(JSScript*)>> functionVector;

//    for(int i = 0; i < SignalVector.size(); i++)
//    {
//        emit SignalVector[i]();
////        emit *i();
//    }

//    tempFunc = &JSScript::signal_1;

    emit signal_1();
    emit signal_2();
    emit signal_3();

    qDebug() << __FUNCTION__ " | Ends";
    //    emit signalTwo();
}

void JSScript::sendSignal_1()
{
    emit signal_1();
}
void JSScript::sendSignal_2()
{
    emit signal_2();
}
void JSScript::sendSignal_3()
{
    emit signal_3();
}
void JSScript::sendSignalTick_1()
{
    emit signal_tick_1();
}
void JSScript::sendSignalTick_2()
{
    emit signal_tick_2();
}
void JSScript::sendSignalTick_3()
{
    emit signal_tick_3();
}
void JSScript::sendSignalTick_4()
{
    emit signal_tick_4();

}
void JSScript::CallJump()
{
    qDebug() << __FUNCTION__ " | Begins";
    // Owner->CallJumpActor();
//    qDebug() << __FUNCTION__ " | Ends";
}
void JSScript::CallWInput()
{
    qDebug() << __FUNCTION__ " | Begins";

}
void JSScript::CallAInput()
{
    qDebug() << __FUNCTION__ " | Begins";

}
void JSScript::CallSInput()
{
    qDebug() << __FUNCTION__ " | Begins";

}
void JSScript::CallDInput()
{
    qDebug() << __FUNCTION__ " | Begins";

}

//void JSScript::sendSignalTick()
//{
//    qDebug() << __FUNCTION__ " | Begins";


//    emit signal_tick_1();
//    emit signal_tick_2();
//    emit signal_tick_3();



//    qDebug() << __FUNCTION__ " | Ends";

//}

//void JSScript::scriptFunction(float in)
//{
//    qDebug() << __FUNCTION__ " | Begins";
//    qDebug() << in;

//    qDebug() << __FUNCTION__ " | Ends";

//}
