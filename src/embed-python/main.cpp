#include <iostream>
#include <stdio.h>
#include <Python.h>

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
    // initialize the interpreter
    Py_Initialize();
    // evaluate some code
    PyRun_SimpleString("import sys\n");
    cout << "===============================" << endl;
    cout << "Python Version: " << endl;        
    PyRun_SimpleString("print (sys.version_info)");
    cout << "===============================" << endl;
    //ignore line wrap on following line
    //PyRun_SimpleString("sys.stdout.write('Hello from an embedded Python Script')\n");
    // shut down the interpreter
    PyRun_SimpleString("print('Hello Python!')\n");
    Py_Finalize();
    return 0;
}
