cmake_minimum_required(VERSION 3.12)

# Настройка vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Настройка проекта
project(homework2 
    VERSION 0.0.1
    DESCRIPTION "IP Filter Application"
    LANGUAGES CXX
)

# Опции сборки
option(WITH_BOOST_TEST "Build with Boost.Test support" ON)
option(WITH_Google_benchmark "Build with Google Benchmark support" OFF)

# Основные цели
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

# Настройки стандарта C++
set_target_properties(${PROJECT_NAME} ip_filter_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Копирование файла данных
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv"
    "${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv"
    COPYONLY
)

# Настройка тестов
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

# Установка и упаковка
install(TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION bin
)

# Настройка CPack для генерации DEB пакета
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "helloworld")
set(CPACK_PACKAGE_VENDOR "Example Inc.")
set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.14), libstdc++6 (>= 4.8.4)")

include(CPack)