#ifndef COMPONENT_H
#define COMPONENT_H

#include "CommonLibrary.h"


template<class T>
class Iterator;

/*
 * 组合模式，用于描述JSON的树形结构
 */
class Component {
protected:
    Component *parent;
    string name;
    int level;
public:
    void setParent(Component *);

    Component *getParent() const;

    virtual void add(Component *);

    virtual list<Component *> *getChildren() = 0;

    virtual Iterator<Component> *getIterator() = 0;

    virtual string getName() = 0;

    virtual int getLevel() = 0;

    virtual int childrenCount() = 0;
};

/*
 * 中间节点类，可以包含叶子节点及中间节点
 */
class Container : public Component {
protected:
    list<Component *> children;
public:
    Container(int, string);

    void add(Component *) override;

    list<Component *> *getChildren() override;

    Iterator<Component> *getIterator() override;

    string getName() override;

    int getLevel() override;

    int childrenCount() override;
};

/*
 * 叶子节点类
 */
class Leaf : public Component {
public:
    Leaf(int, string);

    list<Component *> *getChildren() override;

    Iterator<Component> *getIterator() override;

    string getName() override;

    int getLevel() override;

    int childrenCount() override;
};

#endif
