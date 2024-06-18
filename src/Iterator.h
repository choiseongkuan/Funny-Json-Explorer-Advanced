#ifndef ITERATOR_H
#define ITERATOR_H

#include "CommonLibrary.h"
#include "Component.h"

/*
 * 迭代器
 */
template<class T>
class Iterator {
public:
    virtual T *getNext() = 0;

    virtual bool hasMore() = 0;
};
/*
 * 组合模式Container迭代器
 * 用于遍历组合模式的Container
 */
class JsonIterator : public Iterator<Component> {
private:
    vector<Component *> componentCollection;
    int idx;
public:
    JsonIterator(Component *root);

    void build(Component *root);

    Component *getNext() override;

    bool hasMore() override;

    Component *get();
};

/*
 * 组合模式Leaf迭代器
 * 用于遍历组合模式的Leaf
 */
class LeafIterator : public Iterator<Component> {
private:
    Component *leaf;
public:
    LeafIterator(Component *leaf);

    Component *getNext() override;

    bool hasMore() override;
};

#endif
