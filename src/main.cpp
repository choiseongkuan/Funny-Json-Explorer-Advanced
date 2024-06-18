#include "CommonLibrary.h"
#include "Component.h"
#include "Builder.h"
#include "Iterator.h"
#include "Strategy.h"

using namespace std;

/*
 * 清除字符串中的引号
 */
string trim(string input) {
    string output;
    for (auto i: input) {
        if (i != 34) {
            output += i;
        }
    }
    output = output.substr(1, output.size() - 2);
    return output;
}

/*
 * 清除字符串前后的空格
 */
void strip(string &input) {
    if (input.empty()) {
        return;
    }
    int i = 0;
    while (input[i] == 32) {
        i++;
    }
    int j = input.size() - 1;
    while (input[j] == 32) {
        j--;
    }
    input = input.substr(i, j - i + 1);
}

/*
 * 用于读取Json文件
 */
string readFile(string filename) {
    string output;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            strip(line);
            output.append(line);
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    return output;

}


int main(int argc, char *argv[]) {
    cout << "test" << endl;
    // 读取参数
    string filepath = argv[2];
    string style = argv[4];
    string icon1 = "", icon2 = "";
    if (argc == 8) {
        icon1 = argv[6];
        icon2 = argv[7];
    }
    // 客户代码
    string getfile = readFile(filepath);  // 读取Json文件
    string jsonStr = trim(getfile);  // 规格化Json字符串
    Builder *jsonComponent = new ComponentBuilder();  // 初始化Builder
    jsonComponent->buildComponent(jsonStr);  // 使用Builder构建JSON结构
    Iterator<Component> *it = jsonComponent->getJson()->componentRoot->getIterator();  // 获取迭代器
    Context<Component> *funnyJsonExplorer = new Context<Component>();  // 初始化策略模式
    funnyJsonExplorer->setStrategy(style);  // 选择绘制策略(风格)
    funnyJsonExplorer->show(it, icon1, icon2);  // 执行策略(绘制)

    return 0;
}
