#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    // int v = 5;
    // int * const p1 = &v;
    // v = 6;
    // //p1 = &v;
    // cout << "p1:" << *p1 << endl;

    std::string str = "Kevin";
    for (unsigned int i = 0; i < str.size(); i++) {
        cout << str[i] << endl;
    }

    return 0;
}
