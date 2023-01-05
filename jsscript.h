#ifndef JSSCRIPT_H
#define JSSCRIPT_H

#include <QObject>


class JSScript : public QObject
{
    Q_OBJECT

//    Q_PROPERTY()

//    ScriptComponent

    std::unordered_map<int, bool> InputMap;

    void SignalVectorSetup();

    mEngine

    std::vector<std::function<void(JSScript*)>> SignalVector;
    std::vector<std::function<void(JSScript*)>> SignalTickVector;

public:
    //Constructor
    JSScript();

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
