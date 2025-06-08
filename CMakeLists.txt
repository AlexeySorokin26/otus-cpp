cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(homework_own_allocator 
    VERSION ${PROJECT_VESRION}
    DESCRIPTION "Own allocator"
    LANGUAGES CXX
)

option(WITH_BOOST_TEST "Build with Boost.Test support" ON)
option(WITH_Google_benchmark "Build with Google Benchmark support" OFF)

add_library(own_allocator_lib 
    own_allocator.cpp 
    own_allocator.h
)

add_executable(${PROJECT_NAME} 
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        own_allocator_lib
)

set_target_properties(${PROJECT_NAME} own_allocator_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(WITH_BOOST_TEST)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)
    
    add_executable(own_allocator_test 
        own_allocator_test.cpp
    )
    
    target_link_libraries(own_allocator_test
        PRIVATE
            own_allocator_lib
            Boost::unit_test_framework
    )
    
    enable_testing()
    add_test(NAME own_allocator_test COMMAND own_allocator_test)
endif()

if(WITH_Google_benchmark)
    find_package(benchmark REQUIRED)
    
    add_executable(benchmark_example 
        benchmark_example.cpp
    )
    
    target_link_libraries(benchmark_example
        PRIVATE
            benchmark::benchmark
            own_allocator_lib
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
