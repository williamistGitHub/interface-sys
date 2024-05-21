
# test creation macro
macro(test name)
    add_executable(test__${name} ${CMAKE_SOURCE_DIR}/tests/${name}.c)
    target_link_libraries(test__${name} interface_sys)
    target_include_directories(test__${name} PRIVATE tests)

    add_test(NAME ${name} COMMAND test__${name})
endmacro(test)

# test dependency dll
macro(test_dep name)
    add_library(td__${name} SHARED ${CMAKE_SOURCE_DIR}/tests/${name}_dll.c)
    set_target_properties(td__${name} PROPERTIES OUTPUT_NAME "${name}") # make sure output doesnt have "td__" prefixs
    target_link_libraries(td__${name} interface_sys)
    target_include_directories(td__${name} PRIVATE tests)
endmacro()

# Test C++
macro(test_cpp name)
    add_executable(test__${name} ${CMAKE_SOURCE_DIR}/tests/${name}.cpp)
    target_link_libraries(test__${name} interface_sys)
    target_include_directories(test__${name} PRIVATE tests)

    add_test(NAME ${name} COMMAND test__${name})
endmacro(test_cpp)

# Test C++ dep dll
macro(test_dep_cpp name)
    add_library(tdcpp__${name} SHARED
    ${CMAKE_SOURCE_DIR}/tests/${name}_dll_cpp.cpp)
    set_target_properties(tdcpp__${name} PROPERTIES OUTPUT_NAME
    "${name}_cpp") # make sure output doesnt have "td__" prefixs
    target_link_libraries(tdcpp__${name} interface_sys)
    target_include_directories(tdcpp__${name} PRIVATE tests)
endmacro(test_dep_cpp)

# all tests
test(nonexistant_module)
test_dep(basic_interface)
test(load_module)
test(get_interface_func)
test(get_interface)
test(run_interface_func)

test_dep_cpp(basic_interface)
test_cpp(basic_test)
