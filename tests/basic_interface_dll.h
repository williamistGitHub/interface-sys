#ifndef BASIC_INTERFACE_H
#define BASIC_INTERFACE_H

#include "interface_sys.h"

interface IBasicInterfaceV0 {
    void(*Func1)();
};

typedef struct IBasicInterfaceV0 IBasicInterface;
#define IBASICINTERFACE_VERSION "IBASICINTERFACE_V000"

#endif