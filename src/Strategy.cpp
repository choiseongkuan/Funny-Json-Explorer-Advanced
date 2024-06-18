#include "Strategy.h"

void TreeStrategy::execute(Iterator<Component> *it, string icon1, string icon2) {
    vector<int> levels;
    vector<string> names;
    vector<int> childrenCounters;
    while (it->hasMore()) {
        Component *cur = it->getNext();
        levels.push_back(cur->getLevel());
        names.push_back(cur->getName());
        childrenCounters.push_back(cur->childrenCount());
    }
    int trunk = childrenCounters[0];
    string out;
    for (int i = 1; i < names.size(); i++) {
        string name = names[i];
        if (levels[i] == -1) {
            out.pop_back();
            if (name != "null") {
                out.append(": ");
                out.append(name);
            }
            out += '\n';
            continue;
        }
        if (levels[i] == 1) {
            --trunk;
        }
        if (trunk > 0 && levels[i] != 1) {
            out.append("│");
        }
        for (int j = 1; j < levels[i]; j++) {
            out.append("  ");
        }
        if (childrenCounters[i - 1] > 1) {
            out.append("├─");
            out.append(levels[i + 1] != -1 ? icon1 : icon2);
            out.append(name);
            out += '\n';
        } else {
            out.append("└─");
            out.append(levels[i + 1] != -1 ? icon1 : icon2);
            out.append(name);
            out += '\n';
        }
        --childrenCounters[i - 1];

    }
    cout << out;
}

void RectangleStrategy::supplement(string &input, int n) {
    for (int i = 0; i < n; i++) {
        input.append("─");
    }
}

void RectangleStrategy::execute(Iterator<Component> *it, string icon1, string icon2) {
    vector<int> levels;
    vector<string> names;
    vector<int> childrenCounters;
    while (it->hasMore()) {
        Component *cur = it->getNext();
        levels.push_back(cur->getLevel());
        names.push_back(cur->getName());
        childrenCounters.push_back(cur->childrenCount());
    }
    int remainder = 42;
    string out;
    out.append("┌─");
    out.append(icon1);
    remainder -= 3;
    out.append(names[1]);
    remainder -= names[1].size();
    supplement(out, remainder);
    out.append("─┐");
    out += '\n';
    int lastContainer = 0;
    int i = names.size() - 1;
    while (i > 0) {
        if (levels[i] != -1) {
            lastContainer = i;
            break;
        }
        --i;
    }
    for (i = 2; i < lastContainer; i++) {
        string name = names[i];
        if (levels[i] == -1) {
            if (name != "null") {
                out.append(": ");
                remainder -= 2;
                out.append(name);
                remainder -= names[i].size();
            }
            supplement(out, remainder);
            out.append("─┤");
            out += '\n';
            continue;
        }
        remainder = 42;
        for (int j = 1; j < levels[i]; j++) {
            out.append("│ ");
            remainder -= 2;
        }
        out.append("├─");
        out.append(levels[i] != -1 ? icon1 : icon2);
        remainder -= 3;
        out.append(name);
        remainder -= name.size();
        if (levels[i + 1] != -1) {
            supplement(out, remainder);
            out.append("─┤");
            out += '\n';
        }
    }
    for (i; i < names.size(); i++) {
        string name = names[i];
        if (levels[i] == -1) {
            if (name != "null") {
                out.append(": ");
                remainder -= 2;
                out.append(name);
                remainder -= names[i].size();
            }
            supplement(out, remainder);
            out.append("─┘");
            out += '\n';
            continue;
        }
        remainder = 42;
        for (int j = 1; j < levels[i]; j++) {
            out.append("└─");
            remainder -= 2;
        }
        out.append("└─");
        out.append(levels[i + 1] != -1 ? icon1 : icon2);
        remainder -= 3;
        out.append(names[i]);
        remainder -= names[i].size();
        if (levels[i + 1] != -1) {
            supplement(out, remainder);
            out.append("─┘");
        }
    }
    cout << out;
}

//template<class T>
//void Context<T>::setStrategy(string style) {
//    if (this->strategy) {
//        delete this->strategy;
//    }
//    if (style == "tree") {
//        this->strategy = new TreeStrategy();
//    }
//    else if(style == "rectangle") {
//        this->strategy = new RectangleStrategy();
//    }
//    else {
//        cout << "undefined style!" << endl;
//    }
//}
//template<class T>
//void Context<T>::show(Iterator<T>* it, string icon1, string icon2){
//    this->strategy->execute(it, icon1, icon2);
//}