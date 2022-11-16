#include "Test.h"

Test::Test(OJFile* test) :test(test) {
    srand(time(0));
    test->initProgramName();
    test->initInputFormat();
    for (int i = 0; i <= test->ProgramNumber(); i++) father.push_back(i);
}

int Test::spawnIntInput(int left, int right){
    int x = rand() % (right - left + 1) + left;
    return x;
}

char Test::spawnCharInput() {
    char ch = rand() % 26 + rand() % 2 == 0 ? 65 : 97;
    return ch;
}

std::string Test::spawnStringInput(int left, int right){
    std::string s;
    int number = spawnIntInput(left, right);
    for (int i = 0; i < number; i++) s[i] = spawnCharInput();
    return s;
}

void Test::generateExample(std::string path) {
    std::ofstream ofst;
    ofst.open(path, std::ios::trunc);
    if (!ofst.is_open()) {
        exit(-1);
    }
    for (int i = 0; i < test->InputNumber(); i++) {
        if ( i!= 0) ofst << " ";
        std::pair<int, std::pair<int, int>> example = test->getInput(i);
        switch (example.first) {
        case 0:
            ofst << spawnIntInput(example.second.first, example.second.second);
            break;
        case 1:
            ofst << spawnCharInput();
            break;
        case 2:
            ofst << spawnStringInput(example.second.first, example.second.second);
            break;
        default:break;
        }
    }
    ofst.close();
}

void Test::DoTest()
{
    int Number = test->ProgramNumber();
    std::cout << "Start Testing dir:" << test->path << " , Number = " << Number <<"\n";
    for(int i = 0; i < Number; i++){
        for(int j = i+1; j < Number; j++){
            if(j >= Number) break;
            if(Findfa(i)!=Findfa(j)){
                if(Compare(i,j)) Union(i,j),std::cout << i << " and " << j << " is equal.\n";
            }
        }
    }
    std::string del1 = "rm " + test->path + "/test_out1.txt", del2 = "rm " + test->path + "/test_out2.txt", del3 = "rm " + test->path + "/test_in.txt";
    system(del1.c_str());system(del2.c_str());system(del3.c_str());
    system("rm test.out");
}

void Test::WriteRelation(std::string eqpath, std::string uneqpath)
{
    std::ofstream eqs, ueqs;
    eqs.open(eqpath, std::ios::app);
    ueqs.open(uneqpath, std::ios::app);
    int Number = test->ProgramNumber();
    for(int i = 0; i < Number; i++){
        for(int j = i+1; j < Number; j++){
            if(j >= Number) break;
            if(Findfa(i) == Findfa(j)) eqs << test->getProgramName(i) << "," << test->getProgramName(j) << "\n";
            else ueqs << test->getProgramName(i) << "," << test->getProgramName(j) << "\n";
        }
    }
    eqs.close();
    ueqs.close();
}

bool Test::Compare(int p1, int p2) {
    std::string program1 = test->getProgramName(p1), program2 = test->getProgramName(p2);
    program1 = program1.substr(0, program1.length() - 4);
    program2 = program2.substr(0, program2.length() - 4);
    for (int test_num = 0; test_num < MAX_TEST_NUMBER; test_num++) {
        std::string testin_path = test->path + "/test_in.txt";
        std::string testout_path1 = test->path + "/test_out1.txt";
        std::string testout_path2 = test->path + "/test_out2.txt";
        generateExample(testin_path);
        std::string runcommand1 = "g++ -w " + program1 + ".cpp -o test.out";
        std::string runcommand2 = "g++ -w " + program2 + ".cpp -o test.out";
        std::string checkcommand1 = "./test.out <" + testin_path + " >" + testout_path1 + " 2>&1";
        std::string checkcommand2 = "./test.out <" + testin_path + " >" + testout_path2 + " 2>&1";
        std::string cmpcommand = "cmp -s " + testout_path1 + " " + testout_path2;
        system(runcommand1.c_str()); int a1 = system(checkcommand1.c_str());
        system(runcommand2.c_str()); int a2 = system(checkcommand2.c_str());
        if(a1!=0 || a2!=0) return false;
        int ans = system(cmpcommand.c_str());
        if(ans == 256) return false;
    }
    return true;
}
