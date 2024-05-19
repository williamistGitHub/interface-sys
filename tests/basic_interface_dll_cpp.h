#ifndef BASIC_INTERFACE_CPP_H
#define BASIC_INTERFACE_CPP_H

#include "interface_sys.h"

interface IBasicInterfaceV0 {
    IFUNC(void, Func1);
};

typedef struct IBasicInterfaceV0 IBasicInterface;
#define IBASICINTERFACE_VERSION "IBASICINTERFACE_V000"

#endif
