#include "interface_sys.h"

int main() {

    DynamicModule module = LoadDynModule("__NONEXISTANT");
    if (module != 0) {
        return 1;
    }

    return 0;
}

START_INTERFACE_EXPORT()
END_INTERFACE_EXPORT()