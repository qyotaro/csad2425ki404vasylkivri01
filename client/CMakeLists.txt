cmake_minimum_required(VERSION 3.10)  

project(client_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
find_package(Qt6 COMPONENTS Core Gui Widgets SerialPort Test REQUIRED)

# Set source files
set(SOURCE_FILES
    main.cpp
    mainwindow.cpp
    serialcommunication.cpp
)

set(HEADER_FILES
    mainwindow.h
    serialcommunication.h
)
# Додайте файл .ui
set(UI_FILES
    mainwindow.ui
)

qt6_wrap_ui(UI_HEADERS ${UI_FILES})
# Create executable
add_executable(client ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

target_link_libraries(client Qt6::Core Qt6::Gui Qt6::Widgets Qt6::SerialPort)

add_executable(client_tester
    tests/test_mainwindow.cpp
    serialcommunication.cpp
)

target_link_libraries(client_tester Qt6::Core Qt6::Gui Qt6::Widgets Qt6::SerialPort Qt6::Test)

set_target_properties(client PROPERTIES AUTOMOC ON)
set_target_properties(client_tester PROPERTIES AUTOMOC ON)

# Add MSVC compile option for C++17
#if(MSVC)
 #   add_compile_options(/Zc:__cplusplus)
#endif()

enable_testing()

add_test(NAME SerialCommunicationTests COMMAND client_tester)
