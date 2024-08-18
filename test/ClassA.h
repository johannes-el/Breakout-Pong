#include <iostream>

// ClassA.h
#ifndef CLASSA_H
#define CLASSA_H

class ClassB;  // Forward declaration

class ClassA {
public:
    ClassA(ClassB& b) : b_(b) {}

    void print() {
        std::cout << "ClassA" << std::endl;
        b_.print();
    }

private:
    ClassB& b_;
};

#endif // CLASSA_H