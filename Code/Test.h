#ifndef TEST_H
#define TEST_H
#include "Files.h"
#include <ctime>
class Test{
/*
对于测试代码而言，我们需要一个文件夹一个文件夹的测试
对于每个文件夹，首先获取文件夹内的文件和输入格式文件，接下来随机生成10组输入与输出
在输入输出重定向的情况下执行所有的文件，每次对输入输出进行比较即可
维护程序的等价性使用一个并查集，最开始所有程序等价于自己
两个程序输入输出全部相符时，序号较小的程序成为序号较大的程序的father
*/
private:
    std::vector<int> father;//并查集维护程序关系
    OJFile* test;//需要测试的文件
    const int MAX_TEST_NUMBER = 5;//生成测试的数量
public:
    Test() { srand(time(0)); father.clear(); test = new OJFile; }
    Test(OJFile* test);
    ~Test() { father.clear(); }
    int Findfa(int x) { return father[x] == x ? x : (father[x] = Findfa(father[x])); }
    void Union(int x,int y){
        int rootx = Findfa(x), rooty = Findfa(y);
        if(rootx!=rooty) father[rooty]=rootx;
        else return;
    }
    int spawnIntInput(int left, int right);
    char spawnCharInput();
    std::string spawnStringInput(int left, int right);//按要求随机生成数据
    bool Compare(int p1, int p2);//比较编号为p1与p2的程序
    void generateExample(std::string path);
    void DoTest();
    void WriteRelation(std::string eqpath, std::string uneqpath);//create .csv file
};
#endif // TEST_H
