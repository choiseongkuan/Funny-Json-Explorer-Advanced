#include "Builder.h"


Json *ComponentBuilder::getJson() const {
    return this->json;
}

ComponentBuilder::ComponentBuilder() {
    this->json = new Json();
}

void ComponentBuilder::buildComponent(string jsonStream) const {
    int level = 1;
    int i = 0;
    string name;
    Component *root = new Container(0, "");
    Component *ptr = root;
    while (i < jsonStream.size()) {
        char c = jsonStream[i];
        if (c == '{') {
            ++level;
            root = ptr;
        } else if (c == ':') {
            ptr = new Container(level, name);
            name = "";
            while (jsonStream[i + 1] == 32) {
                ++i;
            }
            if (jsonStream[i + 1] != '{') {
                ++i;
                while (jsonStream[i] != ',' && jsonStream[i] != '}') {
                    name += jsonStream[i];
                    ++i;
                }
                Component *leaf = new Leaf(-1, name);
                ptr->add(leaf);
                name = "";
                --i;
            }
            root->add(ptr);
        } else if (c == '}') {
            --level;
            root = root->getParent();
        } else if (c == ',') {}
        else {
            name += c;
        }
        ++i;
    }
    this->json->componentRoot = root;
}

