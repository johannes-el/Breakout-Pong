#include <iostream>

// ClassB.h
#ifndef CLASSB_H
#define CLASSB_H

class ClassA;  // Forward declaration

class ClassB {
public:
    ClassB(ClassA& a) : a_(a) {}

    void print() {
        std::cout << "ClassB" << std::endl;
        a_.print();
    }

private:
    ClassA& a_;
};

#endif // CLASSB_H