#include "interface_sys.h"
#include "basic_interface_dll_cpp.h"

void Func1_v0() {
    // hmm yes this is a very useful function
}

IMPL_INTERFACE(IBasicInterfaceV0, Func1_v0);

START_INTERFACE_EXPORT()
    EXPORT_INTERFACE(IBasicInterfaceV0, "IBASICINTERFACE_V000")
END_INTERFACE_EXPORT()
