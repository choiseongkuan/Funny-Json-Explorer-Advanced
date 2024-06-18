#ifndef STRATEGY_H
#define STRATEGY_H

#include "Iterator.h"

/*
 * 策略模式
 * 用于选择绘制风格，不同风格对应不同策略
 */
template<class T>
class Strategy {
public:
    virtual void execute(Iterator<T> *, string, string) = 0;
};

/*
 * 树形风格
 */
class TreeStrategy : public Strategy<Component> {
public:
    void execute(Iterator<Component> *, string, string) override;
};

/*
 * 矩形风格
 */
class RectangleStrategy : public Strategy<Component> {
private:
    void supplement(string &input, int n);

public:
    void execute(Iterator<Component> *, string, string) override;
};

/*
 * 上下文
 * 用于与客户端交互
 */
template<class T>
class Context {
private:
    Strategy<T> *strategy;
public:
    void setStrategy(string);

    void show(Iterator<T> *, string, string);
};

template<class T>
void Context<T>::setStrategy(string style) {
    if (this->strategy) {
        delete this->strategy;
    }
    if (style == "tree") {
        this->strategy = new TreeStrategy();
    } else if (style == "rectangle") {
        this->strategy = new RectangleStrategy();
    } else {
        cout << "undefined style!" << endl;
    }
}

template<class T>
void Context<T>::show(Iterator<T> *it, string icon1, string icon2) {
    this->strategy->execute(it, icon1, icon2);
}

#endif
