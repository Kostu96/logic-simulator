cmake_minimum_required(VERSION 3.22)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(logic-simulator LANGUAGES CXX)

set(LSIMAPP_TARGET_NAME lsim_app)
set(LSIMAPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/source/bit.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gates.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
)

add_executable(${LSIMAPP_TARGET_NAME} ${LSIMAPP_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LSIMAPP_SOURCES})

set_target_properties(${LSIMAPP_TARGET_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${LSIMAPP_TARGET_NAME}>
)
