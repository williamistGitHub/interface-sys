#include "interface_sys.h"
#include "basic_interface_dll.h"

int main() {
    DynamicModule module = LoadDynModule("basic_interface");

    if (module == 0) {
        return 1;
    }

    ReqInterfaceFn fn = GetInterfaceFn(module);
    if (fn == 0) {
        UnloadDynModule(module);
        return 2;
    }

    IBasicInterface* i = fn(IBASICINTERFACE_VERSION);
    if (i == 0) {
        UnloadDynModule(module);
        return 3;
    }

    UnloadDynModule(module);

    return 0;
}

START_INTERFACE_EXPORT()
END_INTERFACE_EXPORT()