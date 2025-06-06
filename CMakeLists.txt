cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(homework2 
    VERSION ${PROJECT_VESRION}
    DESCRIPTION "IP Filter Application"
    LANGUAGES CXX
)

option(WITH_BOOST_TEST "Build with Boost.Test support" ON)
option(WITH_Google_benchmark "Build with Google Benchmark support" OFF)

add_library(ip_filter_lib 
    ip_filter.cpp 
    ip_filter.h
)

add_executable(${PROJECT_NAME} 
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        ip_filter_lib
)

set_target_properties(${PROJECT_NAME} ip_filter_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv"
    "${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv"
    COPYONLY
)

if(WITH_BOOST_TEST)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)
    
    add_executable(ip_filter_test 
        ip_filter_test.cpp
    )
    
    target_link_libraries(ip_filter_test
        PRIVATE
            ip_filter_lib
            Boost::unit_test_framework
    )
    
    enable_testing()
    add_test(NAME ip_filter_test COMMAND ip_filter_test)
endif()

if(WITH_Google_benchmark)
    find_package(benchmark REQUIRED)
    
    add_executable(benchmark_example 
        benchmark_example.cpp
    )
    
    target_link_libraries(benchmark_example
        PRIVATE
            benchmark::benchmark
            ip_filter_lib
    )
endif()

install(TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION bin
)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "helloworld")
set(CPACK_PACKAGE_FILE_NAME "helloworld-${PROJECT_VERSION}-Linux")
set(CPACK_PACKAGE_VENDOR "Example Inc.")
set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
