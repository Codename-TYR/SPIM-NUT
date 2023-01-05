#ifndef JSSCRIPT_H
#define JSSCRIPT_H

#include <QObject>

class JSScript : public QObject
{
    Q_OBJECT

//    Q_PROPERTY()


public:
    //Constructor
    JSScript();


    void sendSignal();

signals:
    void signal_1();

public slots:
//  en public slot kan kalles fra javascript, uten Q_INVOKABLE
    void scriptFunction(float in);

};

#endif // JSSCRIPT_H
