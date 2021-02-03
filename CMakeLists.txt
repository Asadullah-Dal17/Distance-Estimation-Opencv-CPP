cmake_minimum_required(VERSION 3.0.0)
project(Distance-Estimation VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(OpenCV REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(Distance-Estimation main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Distance-Estimation ${OpenCV_LIBS} ${CMAKE_THREADS_LIB_INIT})