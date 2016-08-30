#include <iostream>
#include <stdio.h>


#include <boost/python.hpp>  
#include <Python.h>  
#include <dlfcn.h>  

using std::cout;
using std::endl;

namespace py = boost::python;

std::string parse_python_exception(){  
    PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;  
    // Fetch the exception info from the Python C API  
    PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);  
  
    // Fallback error  
    std::string ret("Unfetchable Python error");  
    // If the fetch got a type pointer, parse the type into the exception string  
    if(type_ptr != NULL){  
        py::handle<> h_type(type_ptr);  
        py::str type_pstr(h_type);  
        // Extract the string from the boost::python object  
        py::extract<std::string> e_type_pstr(type_pstr);  
        // If a valid string extraction is available, use it   
        //  otherwise use fallback  
        if(e_type_pstr.check())  
            ret = e_type_pstr();  
        else  
            ret = "Unknown exception type";  
    }  
    // Do the same for the exception value (the stringification of the exception)  
    if(value_ptr != NULL){  
        py::handle<> h_val(value_ptr);  
        py::str a(h_val);  
        py::extract<std::string> returned(a);  
        if(returned.check())  
            ret +=  ": " + returned();  
        else  
            ret += std::string(": Unparseable Python error: ");  
    }  
    // Parse lines from the traceback using the Python traceback module  
    if(traceback_ptr != NULL){  
        py::handle<> h_tb(traceback_ptr);  
        // Load the traceback module and the format_tb function  
        py::object tb(py::import("traceback"));  
        py::object fmt_tb(tb.attr("format_tb"));  
        // Call format_tb to get a list of traceback strings  
        py::object tb_list(fmt_tb(h_tb));  
        // Join the traceback strings into a single string  
        py::object tb_str(py::str("\n").join(tb_list));  
        // Extract the string, check the extraction, and fallback in necessary  
        py::extract<std::string> returned(tb_str);  
        if(returned.check())  
            ret += ": " + returned();  
        else  
            ret += std::string(": Unparseable Python traceback");  
    }  
    return ret;  
}  

int main(int argc, char * argv[])
{
    Py_Initialize();
        
    try {
        py::object main_module = py::import("__main__");  
        py::object main_namespace = main_module.attr("__dict__");  

        py::exec("import kevin", main_namespace);
        
        py::object myclass_1 = py::eval("kevin.MyClass()", main_namespace);
        py::object my_1_inc = myclass_1.attr("inc");
        cout << "1 - Num: " << py::extract<int>(myclass_1.attr("i")) << endl;

        py::object myclass_2 = py::eval("kevin.MyClass()", main_namespace);
        py::object my_2_inc = myclass_2.attr("inc");
        cout << "2 - Num: " << py::extract<int>(myclass_2.attr("i")) << endl;
        
        // Increment 1:
        my_1_inc(1);
        
        my_2_inc(10);
        
        cout << "1 - Num: " << py::extract<int>(myclass_1.attr("i")) << endl;
        cout << "2 - Num: " << py::extract<int>(myclass_2.attr("i")) << endl;                      
                
    } catch(boost::python::error_already_set const &){  
        // Parse and output the exception  
        std::string perror_str = parse_python_exception();  
        std::cout << "Error in Python: " << perror_str << std::endl; 
    }

    //Py_Finalize(); // Don't call with boost python?
    
    return 0;
}
