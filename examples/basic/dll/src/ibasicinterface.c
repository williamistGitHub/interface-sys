// this is the implementation of IBasicInterface for this dll

#include "interface_sys.h"
#include "ibasicinterface.h"
#include <stdio.h>

void DoSomething() {
    printf("DoSomething called!\n");
}

int Sum_V0(int a, int b) {
    return a + b;
}

double Sum_V1(float a, float b) {
    return (double)a + (double)b;
}

// now we define what functions to use for each interface
IMPL_INTERFACE(IBasicInterfaceV0,
    DoSomething,
    Sum_V0
)

IMPL_INTERFACE(IBasicInterfaceV1,
    DoSomething,
    Sum_V1
)