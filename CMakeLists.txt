cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(filter VERSION ${PROJECT_VESRION})

#option(WITH_BOOST_TEST "Whether to build Boost test" ON)
option(WITH_GTEST "Whether to build google test" ON)

configure_file(version.h.in version.h)

add_executable(filter main.cpp)
add_library(filter_lib filter.cpp filter.h)

set_target_properties(filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(filter PRIVATE
    filter_lib
)

if(WITH_GTEST)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest" "googletest")
    add_executable(test_filter test_filter.cpp)

    target_include_directories(test_filter PRIVATE
        ${GTEST_INCLUDE_DIRS}
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )

    set_target_properties(test_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_filter PRIVATE
        filter_lib
        ${GTEST_BOTH_LIBRARIES}
        gtest
        gtest_main
    )
endif()

if(MSVC)
    target_compile_options(filter PRIVATE
        /W4
    )
    target_compile_options(filter_lib PRIVATE
        /W4
    )
    if(WITH_GTEST)
        target_compile_options(test_filter PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(filter PRIVATE
        -Wall
        -Wextra -pedantic -Werror
    )
    target_compile_options(filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GTEST)
        target_compile_options(test_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_GTEST)
    enable_testing()
    #add_test(test_filter test_filter)
        add_test(test test_filter)
endif()
