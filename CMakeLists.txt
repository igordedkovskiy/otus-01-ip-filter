cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

option(WITH_GTEST "Whether to build google test" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter main.cpp)
add_library(ip_filter_lib ip_filter.cpp ip_filter.h)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(ip_filter_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

if(WITH_GTEST)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest" "googletest")
    add_executable(test_ip_filter test_ip_filter.cpp)

    target_include_directories(test_ip_filter PRIVATE
        ${GTEST_INCLUDE_DIRS}
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )

    set_target_properties(test_ip_filter PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_ip_filter PRIVATE
        ip_filter_lib
        ${GTEST_BOTH_LIBRARIES}
        gtest
        gtest_main
    )
endif()

if(MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4
    )
    if(WITH_GTEST)
        target_compile_options(test_ip_filter PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall
        -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GTEST)
        target_compile_options(test_ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT divmy@yandex.ru)
include(CPack)

if(WITH_GTEST)
    include(CTest)
    enable_testing()
    add_test(test test_ip_filter)
endif()

if(UNIX)
    include(CTest)
    #message(STATUS ">>> Linux or BSD or MacOS")
    enable_testing()
    add_test(NAME "check_md5sum" COMMAND "${PROJECT_SOURCE_DIR}/check_md5sum.sh")
endif()
