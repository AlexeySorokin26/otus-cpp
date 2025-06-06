cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(homework2)

option(WITH_BOOST_TEST "Whether to build Boost test" ON)
option(WITH_Google_benchmark "Whether to build Google benchmark test" OFF)

add_executable(${PROJECT_NAME} main.cpp)
add_library(ip_filter_lib ip_filter.cpp ip_filter.h)
target_link_libraries(${PROJECT_NAME} PRIVATE ip_filter_lib)
set_target_properties(${PROJECT_NAME} ip_filter_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# copy data file to build folder
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv"
    "${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv"
    COPYONLY
)

if(WITH_BOOST_TEST)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)
    message(STATUS "Boost include directory: ${Boost_INCLUDE_DIRS}")

    add_executable(ip_filter_test  ip_filter_test.cpp)
    target_link_libraries(ip_filter_test
        PRIVATE
            ip_filter_lib
            Boost::unit_test_framework
    )
endif()

if(WITH_Google_benchmark)
    find_package(benchmark REQUIRED)

    #add_executable(benchmark_example benchmark_example.cpp)
    target_link_libraries(benchmark_example
        PRIVATE
            benchmark::benchmark
            helloworld  
    )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
include(CPack)