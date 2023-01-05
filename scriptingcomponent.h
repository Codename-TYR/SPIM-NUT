#ifndef SCRIPTINGCOMPONENT_H
#define SCRIPTINGCOMPONENT_H

#include <QObject>

class ScriptingComponent : public QObject
{
    //To call functions from JS
    Q_OBJECT

class QJSEngine* JSEngine {nullptr};



    // To be able to use a C++ variable in js you have to use Q_PROPERTY
    // These are the variable name and function-calls you may use from JS
    //  name = x,   read function,  write function
    Q_PROPERTY(float x READ GetX WRITE SetX NOTIFY NotifyX)
public:
    ScriptingComponent(QObject *parent = nullptr, QString JSFileName = "Error");

    void sendSignal();

    // Q_INVOKEABLE must be used infront of functions that will be called from JS
    Q_INVOKABLE int TestFunction();

    // Setter and Getter for the variable x
    // Named the same as in the Q_PROPERTY call above
    float GetX() const {return mX;}
    void SetX(float Value) {mX = Value;}

    // Function which gets called upon reading or changing the x variable, as declared in the Q_PROPERTY
    void NotifyX();
signals:
    void SignalOne();

public slots:
    // A public slot which can be called from JS without Q_INVOKEABLE
    void ScriptFunction(float In);

private:
    // This function cannot be called because it is private
    Q_INVOKABLE void PrivateFunction();

    // This variable has the getter and the setter from above, both of which can be called from JS
    float mX {103};


    /////////////////////////////////////////////////////////////


};

#endif // SCRIPTINGCOMPONENT_H
