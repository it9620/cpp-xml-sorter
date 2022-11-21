######################################################################
# MAIN PART
###################################
cmake_minimum_required(VERSION 3.20)
project(CppTemplate VERSION 0.1.1)
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")


# set the cpp and c standard for compilator:
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

#set(TRANSPORTCAT_FILES main.cpp)

# COMPILE EXECUTABLE FILE
add_executable(${PROJECT_NAME}
        main.cpp
        ../lib/pugixml-1.13/src/pugixml.cpp
        )
#
#

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
#


target_compile_options(${PROJECT_NAME} PRIVATE
        -stdlib=libc++ # default library for MacOS
        -fdiagnostics-color=always
        -Wall
        -Werror
        )

#set(CMAKE_BUILD_TYPE "Debug")
if (CMAKE_BUILD_TYPE MATCHES Debug)

        #https://www.stackfinder.ru/questions/67512498/how-to-set-asan-options-environment-variable-in-cmake
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CMAKE_COMMAND} 
                -E env ASAN_OPTIONS=detect_stack_use_after_return=1 
                -E env ASAN_OPTIONS=detect_leaks=1
                ${CMAKE_CXX_COMPILER_LAUNCHER})

        add_definitions(-D DEBUG=1
                -g
                -fsanitize=address
                -fsanitize=undefined
                #-fsanitize=leak
                -O0
                -fno-omit-frame-pointer
                -fno-optimize-sibling-calls
                #-D_LIBCPP_DEBUG=1 # debuging macros turn on spec regime for libc++
                -D_GLIBCXX_DEBUG # debuging macros turn on spec regime for libstdc++
                -D_GLIBCXX_DEBUG_PEDANTIC # debuging macros turn on spec regime for libstdc++
                )
        #

        target_link_options(${PROJECT_NAME} PRIVATE
                -fsanitize=address
                -fsanitize=undefined
                #-fsanitize=leak
                )
endif()


if(CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

target_link_libraries(${PROJECT_NAME} Threads::Threads ${SYSTEM_LIBS})