#include "Files.h"

void OJFile::initProgramName(){
    DIR *pdir;
    struct dirent * ptr;
    if(!(pdir = opendir(path.c_str()))) return;
    while((ptr = readdir(pdir)) != 0){
        if(strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
            if(strcmp(ptr->d_name, "stdin_format.txt") && strcmp(ptr->d_name, "test_in.txt")
                    && strcmp(ptr->d_name, "test_out1.txt") && strcmp(ptr->d_name, "test_out2.txt")) programName.push_back(path + "/" + ptr->d_name);
        }
    }
    closedir(pdir);
}


void OJFile::initInputFormat() {
    std::ifstream instr;
    std::string p;p.assign(path).append("/").append("stdin_format.txt");
    instr.open(p, std::ios::in);
    if (instr.is_open()) {
        char ch[100] = { 0 };
        std::string argument;
        while (!instr.eof()) {
            int leftrange, rightrange;//左范围 右范围
            instr.getline(ch, sizeof(ch));
            std::regex regspace(" ");
            std::string input = ch;
            std::sregex_token_iterator iter(input.begin(), input.end(), regspace, -1);
            decltype(iter) end;
            for(;iter != end; ++iter){
                argument = iter->str();
                if (argument[0] == 'i' || argument[0] == 's') {
                    std::string const str = ch;
                    std::regex regnum{ "\\d+" };
                    std::sregex_token_iterator iters(str.cbegin(), str.cend(), regnum);
                    decltype(iters) end;
                    leftrange = stoi((iters++)->str());
                    rightrange = stoi(iters->str());
                    this->input.push_back(std::make_pair(argument[0] == 'i' ? 0 : 2, std::make_pair(leftrange, rightrange)));
                }
                else this->input.push_back(std::make_pair(1, std::make_pair(0, 26)));
            }
        }
        instr.close();
    }
}
