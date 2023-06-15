// heres some example code that uses the IBasicInterface

#include "interface_sys.h"
#include "ibasicinterface.h"

#include <stdio.h>

int main() {
    // try to load the module
    DynamicModule module = LoadDynModule("example_basic_dll");
    if (!module) {
        printf("Error while loading module.\n");
        return 0;
    }

    // try and get the interface requestor function from the module
    ReqInterfaceFn fn = GetInterfaceFn(module);
    if (!fn) {
        printf("Error while getting interface function.\n");
        UnloadDynModule(module);
        return 0;
    }

    // try and get the interface from the module using the function
    IBasicInterface* i = fn(IBASICINTERFACE_VERSION);
    if (i == NULL) {
        printf("Error: couldn't get interface %s", IBASICINTERFACE_VERSION);
        UnloadDynModule(module);
        return 0;
    }

    // call some things in it
    i->DoSomething();
    printf("5 + 8 = %f", i->Sum(5, 8));

    // ok we done, unload
    UnloadDynModule(module);
}

// as said in interface_exports.c, every project that links to interface_sys needs to export an interface list
// even if it's empty
START_INTERFACE_EXPORT()
END_INTERFACE_EXPORT()