#ifndef BUILDER_H
#define BUILDER_H

#include "CommonLibrary.h"
#include "Component.h"

/*
 * Json类，用于存储Build完的Json结构
 */
class Json {
public:
    Component *componentRoot;
};

/*
 * 创建者模式，用于利用组合模式创建Json的树形结构
 */
class Builder {
public:
    virtual void buildComponent(string) const = 0;

    virtual Json *getJson() const = 0;
};

/*
 * 创建Json组合模式的树形结构
 */
class ComponentBuilder : public Builder {
private:
    Json *json;
public:
    Json *getJson() const;

    ComponentBuilder();

    void buildComponent(string) const;

};

#endif