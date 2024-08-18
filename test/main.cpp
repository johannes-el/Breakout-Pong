// main.cpp
#include "ClassA.h"
#include "ClassB.h"

int main() {
    ClassB b;  // Create an instance of ClassB first
    ClassA a(b);  // Now create an instance of ClassA
    a.print();
    return 0;
}