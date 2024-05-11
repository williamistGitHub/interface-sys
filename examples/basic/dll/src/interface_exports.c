// you need to export interfaces for everything that is built with the interface system linked to it
// even if you dont have anything to export, export an empty table.

#include "interface_sys.h"

#include "ibasicinterface.h"

// declare the implementations of the interfaces, so we can export them
// this could be done here or in the exports file, it doesnt really matter
DECL_INTERFACE_IMPL(IBasicInterfaceV0);
DECL_INTERFACE_IMPL(IBasicInterfaceV1);

START_INTERFACE_EXPORT()
    EXPORT_INTERFACE(IBasicInterfaceV0, "IBASICINTERFACE_V000")
    EXPORT_INTERFACE(IBasicInterfaceV1, "IBASICINTERFACE_V001")
END_INTERFACE_EXPORT()