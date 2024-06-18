//#include "Component.h"
# include "iterator.h"

void Component::setParent(Component *parent) {
    this->parent = parent;
}

Component *Component::getParent() const {
    return this->parent;
}

void Component::add(Component *component) {};

Container::Container(int level, string name) {
    this->level = level;
    this->name = name;
}

void Container::add(Component *component) {
    children.push_back(component);
    component->setParent(this);
}

Iterator<Component> *Container::getIterator() {
    return new JsonIterator(this);
}

list<Component *> *Container::getChildren() {
    return &children;
}

string Container::getName() {
    return this->name;
}

int Container::getLevel() {
    return this->level;
}

int Container::childrenCount() {
    return this->children.size();
}


Leaf::Leaf(int level, string name) {
    this->level = level;
    this->name = name;
}


list<Component *> *Leaf::getChildren() {
    return nullptr;
}

string Leaf::getName() {
    return this->name;
}

Iterator<Component> *Leaf::getIterator() {
    return nullptr;
}

int Leaf::getLevel() {
    return this->level;
}

int Leaf::childrenCount() {
    return 0;
}