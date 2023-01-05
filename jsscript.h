#ifndef JSSCRIPT_H
#define JSSCRIPT_H

#include "qjsengine.h"
#include <QObject>


class JSScript : public QObject
{
    Q_OBJECT

//    Q_PROPERTY()

public:
    //Constructor
    JSScript(class ScriptComponent* InComponent);

//    ScriptComponent
private:
    std::unordered_map<int, bool> InputMap;

    void SignalVectorSetup();

    class ScriptComponent* mOwningComponent {nullptr};

    QJSEngine mEngine;

    std::vector<std::function<void(JSScript*)>> SignalVector;
    std::vector<std::function<void(JSScript*)>> SignalTickVector;
public:
    void sendSignal();

    void sendSignal_1();
    void sendSignal_2();
    void sendSignal_3();

    void sendSignalTick_1();
    void sendSignalTick_2();
    void sendSignalTick_3();

signals:
    void signal_1();
    void signal_2();
    void signal_3();

    void signal_tick_1();
    void signal_tick_2();
    void signal_tick_3();


public slots:
//  en public slot kan kalles fra javascript, uten Q_INVOKABLE

    void CallJump();

//    void scriptFunction(float in);
//    void scriptFunction(float in);
//    void scriptFunction( std::map<int, bool> inMap);

};

#endif // JSSCRIPT_H
