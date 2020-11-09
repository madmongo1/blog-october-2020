cmake_minimum_required(VERSION 3.17)
project(october_2020)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
if (Boost_VERSION VERSION_LESS 1.74)
    message(FATAL_ERROR "Boost 1.74 or higher required")
endif()
find_package(Threads)

file(GLOB_RECURSE src_files CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_executable(october_2020 ${src_files})
target_link_libraries(october_2020 Qt5::Widgets Boost::system Threads::Threads)
target_compile_options(october_2020 PUBLIC -fcoroutines-ts)
