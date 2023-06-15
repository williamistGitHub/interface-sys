#ifndef IBASICINTERFACE_H
#define IBASICINTERFACE_H

#include "interface_sys.h"

// you can define an interface of function pointers like this:
// interface is just struct #define'd. remove it if you want to
interface IBasicInterfaceV0 {
    void(*DoSomething)();
    int(*Sum)(int a, int b);
};

// never change an interface when its defined, always make a new one and increment the version
// in this example, we've made the Sum function take floats instead of ints, and return a double.
interface IBasicInterfaceV1 {
    void(*DoSomething)();
    double(*Sum)(float a, float b);
};

// declare the implementations of the interfaces, so we can export them
// this could be done here or in the exports file, it doesnt really matter
DECL_INTERFACE_IMPL(IBasicInterfaceV0);
DECL_INTERFACE_IMPL(IBasicInterfaceV1);

// define the latest interface type and version string here
typedef struct IBasicInterfaceV1 IBasicInterface;
// the version string can be anything, but keep it unique within the module
#define IBASICINTERFACE_VERSION "IBASICINTERFACE_V001"

#endif