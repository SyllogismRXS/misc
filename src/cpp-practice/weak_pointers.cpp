#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class MyClass;

class MyClass {
 public:
    explicit MyClass(const std::string &name) : name_(name){
        std::cout << "Constructor: " << name_ << endl;
    }
    ~MyClass() {
        std::cout << "Destructor: " << name_ << endl;
    }
    void set_other(std::shared_ptr<MyClass> other) {
        other_ = other;
    }

    std::string &name() {
        return name_;
    }

    std::string &other_name() {
        auto wp = other_.lock();
        return wp->name();
    }

 protected:
    std::string name_;
    std::weak_ptr<MyClass> other_;
};

int main(int argc, char *argv[]) {
    cout << "Weak Pointers!" << endl;

    std::shared_ptr<MyClass> one = std::make_shared<MyClass>("one");
    std::shared_ptr<MyClass> two = std::make_shared<MyClass>("two");

    one->set_other(two);
    two->set_other(one);

    cout << "one->other_name(): " << one->other_name() << endl;
    cout << "two->other_name(): " << two->other_name() << endl;

    cout << "Shutting down..." << endl;
    return 0;
}
