#include <Files.h>
#include <Test.h>

void InitFile(std::string path, std::vector<OJFile> &files){
    DIR *pdir;
    struct dirent * ptr;
    if(!(pdir = opendir(path.c_str()))) return;
    while((ptr = readdir(pdir)) != 0){
        if(strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
            std::string path_dir = path + "/" + ptr->d_name;
            // std::cout << path_dir << "\n";
            OJFile newfolder(path_dir);
            files.push_back(newfolder);
        }
    }
    closedir(pdir);
}

int main()
{
    std::vector<OJFile> FileCheck;
    std::string path_in, path_out, path;
    std::cout << "Please insert absolute path for /input's father path.\nPath: ";
    std::cin >> path;
    system(std::string("cd ").append(path).c_str());
    path_out = path + "/output";
    path_in = path + "/input";
    std::string equal_path = path_out + "/equal.csv", unequal_path = path_out + "/inequal.csv";
    system(std::string("mkdir ").append(path_out).c_str());
    std::ofstream eqs, ueqs;
    eqs.open(equal_path, std::ios::app);eqs<<"file1,file2\n";eqs.close();
    ueqs.open(unequal_path, std::ios::app);ueqs<<"file1,file2\n";ueqs.close();
    InitFile(path_in, FileCheck);
    for(OJFile file: FileCheck){
        Test newtest(&file);
        newtest.DoTest();
        newtest.WriteRelation(equal_path, unequal_path);
    }
    FileCheck.clear();
    return 0;
}
