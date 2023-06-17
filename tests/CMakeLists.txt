
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

# all tests
test(nonexistant_module)
test_dep(basic_interface)
test(load_module)
test(get_interface_func)
test(get_interface)
test(run_interface_func)