cmake_minimum_required(VERSION 3.25)
project(Lab1_Koshi)

set(CMAKE_CXX_STANDARD 20)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
        INSTALL_FOLDER ${CMAKE_BINARY_DIR}
        BASIC_SETUP
        BUILD missing)

add_executable(Lab1_Koshi
        src/main.cpp
        src/math/Function.cpp
        src/math/Sequence.cpp
        src/math/Operations.cpp
        src/math/Utilities.cpp
        src/Window.cpp
        src/InputSystem.cpp
        src/GraphWindow.cpp src/GraphWindow.h)

target_link_libraries(Lab1_Koshi ${CONAN_LIBS})