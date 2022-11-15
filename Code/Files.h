#ifndef FILES_H
#define FILES_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string.h>
#include <assert.h>
#include <regex>
#include <iterator>
#include <dirent.h>
class OJFile {
    /*
      处理所有与文件读写有关的操作
      更具体而言，操作包括：
      读入stdin_format.txt, 返回可处理的格式串
      读入文件夹内的OJ代码，获取他们的名称列表，并在本类中保存一个程序名称列表。
     （拓展接口）读入文件夹内的OJ代码的文本，以char*返回
      因此，每个文件夹我们都需要创建一个File类对象。
    */
private:
    std::vector<std::string> programName;//保存所有OJ文件的名称
    std::vector<std::pair<int,std::pair<int,int>>> input;//从stdin_format中获取的参数列表
    /*
    stdin_format中只有三种参数：
    type0:int(a,b) 生成一个int类型的参数，范围在a-b之间（int this=rand()%(b-a)+a;)
    type1:char 生成一个char类对象，范围在65"A"-90"Z"/97"a"-122"z"之间 (char this = rand()%26 + rand()%2 == 0?65:97;)
    type2:string(a,b) 随机生成一个字符串，字符类型无限制，长度在a-b之间（调用n次char随机函数）
    */
public:
    friend class Test;
    std::string path;//该File类对应文件夹的路径
    OJFile() { programName.clear(); input.clear(); }
    OJFile(std::string path) :path(path) { programName.clear(); input.clear(); }
    ~OJFile() { programName.clear(); input.clear(); }
    void initProgramName();
    void initInputFormat();
    int ProgramNumber() const { return programName.size(); }
    int InputNumber() const { return input.size(); }
    std::string getProgramName(int index) { return programName[index]; }
    std::pair<int, std::pair<int, int>> getInput(int index) { return input[index]; }
};
#endif // FILES_H
