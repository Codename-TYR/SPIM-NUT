#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "basecomponent.h"
#include <QFile>
#include <QJSEngine>



class ScriptComponent : public BaseComponent
{
public:
    ScriptComponent(class QString fileName);


    void ComponentTick(float deltaTime) override;
    void DrawComponent() override {};



private:
    void InitializeComponentType() override {ComponentType = EComponentType::ECT_ScriptComponent;}

    // Instance of QJSEngine
    QJSEngine mEngine;
    // Filepath to this components' JS-File
    QString mJSFilePath;

    class JSScript* JSScriptObject {nullptr};

    std::unordered_map<int, bool> CurrentInputsMap;


public:
    QString GetJSFilePath() {return mJSFilePath;}


};

#endif // SCRIPTCOMPONENT_H
