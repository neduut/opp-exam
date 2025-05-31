cmake_minimum_required(VERSION 3.25)
project(Egzaminas)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-mconsole")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(LIB_SOURCES
    src/functions.cpp
)

add_library(Egzaminas_lib STATIC ${LIB_SOURCES})

add_executable(Egzaminas src/main.cpp)
target_link_libraries(Egzaminas PRIVATE Egzaminas_lib)


if(WIN32)
    set_target_properties(Egzaminas PROPERTIES LINK_FLAGS "-mconsole")
    set_target_properties(tests PROPERTIES LINK_FLAGS "-mconsole")
endif()