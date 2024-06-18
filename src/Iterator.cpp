#include "Iterator.h"

void JsonIterator::build(Component *root) {
    this->componentCollection.push_back(root);
    list<Component *> *children = root->getChildren();
    if (children) {
        for (auto child: *children) {
            build(child);
        }
    }
    return;
}

JsonIterator::JsonIterator(Component *root) {
    build(root);
    idx = 0;
}

bool JsonIterator::hasMore() {
    return idx < componentCollection.size();
}

Component *JsonIterator::getNext() {
    Component *cur = nullptr;
    if (hasMore()) {
        cur = get();
        idx++;
    }
    return cur;
}

Component *JsonIterator::get() {
    return componentCollection[idx];
}

LeafIterator::LeafIterator(Component *leaf) {
    this->leaf = leaf;
}

Component *LeafIterator::getNext() {
    return leaf;
}

bool LeafIterator::hasMore() {
    return false;
}