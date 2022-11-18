cmake_minimum_required(VERSION 3.14)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

include_directories($ENV{HOME}/Developer/C++/include)
link_directories($ENV{HOME}/Developer/C++/lib)
link_libraries(dataStructures)

add_executable(calculator main.cpp dictionary.cpp dictionary.h fraction.cpp fraction.h)

