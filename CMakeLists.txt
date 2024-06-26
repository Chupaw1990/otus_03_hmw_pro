cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(allocator VERSION ${PROJECT_VESRION})

option(WITH_GOOGLE_TEST "Whether to build GTest" ON)

configure_file(version.h.in version.h)
add_executable(allocator allocator.cpp)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(allocator PRIVATE "${CMAKE_BINARY_DIR}")

if(WITH_GOOGLE_TEST)
    find_package(GTest REQUIRED)
    add_executable(test_allocator test_allocator.cpp)

    set_target_properties(test_allocator PROPERTIES
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED ON
                         )

    target_link_libraries(test_allocator GTest::gtest GTest::gtest_main) 

endif()

if (MSVC)
    target_compile_options(allocator PRIVATE /W4)
    if(WITH_GOOGLE_TEST)
        target_compile_options(test_allocator PRIVATE /W4)
    endif()

else ()
    target_compile_options(allocator PRIVATE -Wall -Wextra -pedantic -Werror)

    if(WITH_GOOGLE_TEST)
        target_compile_options(test_allocator PRIVATE
                                -Wall -Wextra -pedantic -Werror
    )
    endif()

endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)
if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(test_allocator test_allocator)
endif()