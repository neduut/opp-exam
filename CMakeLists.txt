cmake_minimum_required(VERSION 3.25)
project(Egzaminas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SOURCES
    src/functions.cpp
)

add_library(Egzaminas_lib STATIC ${LIB_SOURCES})
target_include_directories(Egzaminas_lib PUBLIC include)

add_executable(main src/main.cpp)
target_include_directories(main PUBLIC include)
target_link_libraries(main PRIVATE Egzaminas_lib)

if(WIN32)
    set_target_properties(main PROPERTIES LINK_FLAGS "-mconsole")
endif()
