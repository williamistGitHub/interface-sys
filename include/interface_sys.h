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
extern interface_export_t allExportedInterfaces[];
#ifdef __cplusplus
}
#endif

// the function here is to make sure the static library gets imported, compilers like to not import it if you dont call any of the functions and this prevents that
#define START_INTERFACE_EXPORT() void __GENERATED_(void){UnloadDynModule((DynamicModule)0);} \
	interface_export_t allExportedInterfaces[] = {
#define EXPORT_INTERFACE(iName, ver) { (void*)(&__g_##iName##_impl), ver },
#define END_INTERFACE_EXPORT() {0, 0}};

#endif // INTERFACE_SYS_H