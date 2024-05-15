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

#ifndef INTERFACE_SYS_H
#define INTERFACE_SYS_H

#ifndef NO_INTERFACE_KEYWORD
#define interface struct
#endif // NO_INTERFACE_KEYWORD

#include <string.h>
#ifdef ISYS_DEBUG
#include <stdio.h>
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

// easier to read function pointer syntax for interfaces
#define IFUNC(retType, name, ...) retType (* name )( __VA_ARGS__ )

#define DECL_INTERFACE_IMPL(iName) extern struct iName __g_##iName##_impl
#define IMPL_INTERFACE(iName, ...) struct iName __g_##iName##_impl = { __VA_ARGS__ }

typedef void*(*ReqInterfaceFn)(const char* interfaceName);

typedef void* DynamicModule;

#ifdef __cplusplus
extern "C" {
#endif
DynamicModule LoadDynModule(const char* name);
ReqInterfaceFn GetInterfaceFn(DynamicModule module);
void UnloadDynModule(DynamicModule module);

typedef struct {
  void* impl;
  const char* version;
} interface_export_t;
#ifdef __cplusplus
}
#endif

#ifndef _WIN32
#define REQUESTINTERFACE_EXPORT void* __attribute__((visibility("default")))
#else // _WIN32
#define REQUESTINTERFACE_EXPORT __declspec(dllexport) void*
#endif // _WIN32

#define IMPL_REQUESTINTERFACE REQUESTINTERFACE_EXPORT RequestInterface(const char* name) { \
    DEBUG_PRINT("RequestInterface loaded from " __FILE__ "\n"); \
    DEBUG_PRINT("Attempting to find interface '%s'\n", name); \
    for (int i = 0; allExportedInterfaces[i].impl != 0; i++) { \
        interface_export_t* exp = &allExportedInterfaces[i]; \
        DEBUG_PRINT("Found '%s'\n", exp->version); \
        if (strncmp(name, exp->version, 256) == 0) { \
            return exp->impl; \
        } \
    } \
\
    DEBUG_PRINT("Couldn't find it!\n"); \
\
    return 0; \
}

// the __GENERATED_ function here is to make sure the static library gets imported, compilers like to not import it if you dont call any of the functions and this prevents that
#define START_INTERFACE_EXPORT() IMPL_REQUESTINTERFACE void __GENERATED_(void){UnloadDynModule((DynamicModule)0);} \
	static interface_export_t allExportedInterfaces[] = {
#define EXPORT_INTERFACE(iName, ver) { (void*)(&__g_##iName##_impl), ver },
#define END_INTERFACE_EXPORT() {0, 0}};

#endif // INTERFACE_SYS_H