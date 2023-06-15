/*
    interface-sys
    Copyright (C) 2023  williamist

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "interface_sys.h"
#include <stdio.h>
#include <string.h>

#ifndef _WIN32
#include <dlfcn.h>
#include <stdlib.h>
#include <limits.h>
#else
#include <Windows.h>
#endif

#ifdef _WIN32
LPTSTR GetLastErrorString() {

    LPTSTR allocBuf = NULL;
    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&allocBuf,
        0,
        NULL
    );

    return allocBuf;
}
#endif

#ifndef _WIN32
#define EXPORT_RI void* __attribute__((visibility("default")))
#else // _WIN32
#define EXPORT_RI __declspec(dllexport) void*
#endif // _WIN32

EXPORT_RI RequestInterface(const char* name) {
    for (int i = 0; allExportedInterfaces[i].impl != NULL; i++) {
        interface_export_t* exp = &allExportedInterfaces[i];
        if (strncmp(name, exp->version, 256) == 0) {
            return exp->impl;
        }
    }

    return NULL;
}
#undef EXPORT_RI

// Cross-platform(-ish) way of loading dynamic libraries. 
DynamicModule LoadDynModule(const char *name) {
#ifndef _WIN32
    dlerror();

    char realPath[PATH_MAX];
    sprintf(realPath, "lib%s.so", name);
    realpath(realPath, realPath);

    void* m = dlopen(realPath, RTLD_NOW | RTLD_GLOBAL);
    char* err = dlerror();
    if (err) {
        printf("Error while loading module '%s': %s\n", name, err);
        return NULL;
    }

    return m;
#else
    char fullLibName[MAX_PATH];
    sprintf(fullLibName, "%s.dll", name);
    HMODULE m = LoadLibrary(fullLibName);
    if (m == NULL) {
        LPTSTR err = GetLastErrorString();
        printf("Error while loading module '%s': %s\n", name, err);
        LocalFree(err);
        return NULL;
    }
    return (DynamicModule)m;
#endif
}

ReqInterfaceFn GetInterfaceFn(DynamicModule module) {
#ifndef _WIN32
    dlerror();
    void* fn = dlsym((void*)module, "RequestInterface");
    char* err = dlerror();
    if (err) {
        printf("Error while getting interface function: %s\n", err);
        return NULL;
    }
    return fn;
#else
    FARPROC fn = GetProcAddress((HMODULE)module, "RequestInterface");
    if (fn == NULL) {
        LPTSTR err = GetLastErrorString();
        printf("Error while getting interface function: %s\n", err);
        LocalFree(err);
        return NULL;
    }
    return (ReqInterfaceFn)fn;
#endif
}

void UnloadDynModule(DynamicModule module) {
    if (module == NULL) return;
#ifndef _WIN32
    dlclose((void*)module);
#else
    // FreeLibrary fails if 0, display message.
    if (FreeLibrary((HMODULE)module) == 0) {
        LPTSTR err = GetLastErrorString();
        printf("Error while unloading a module: %s", err);
        LocalFree(err);
    }
#endif
}