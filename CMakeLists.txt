project(test)

cmake_minimum_required( VERSION 3.4.0 )

include(ExternalProject)

ExternalProject_Add(oscpack
  GIT_REPOSITORY "https://github.com/K0F/oscpack.git"
  GIT_TAG "master"
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
  )

export(PACKAGE oscpack)

SET(EXECUTABLE_NAME "aaa")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install" CACHE STRING "Cmake install path" FORCE)
endif()

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Modules)

FIND_PACKAGE(Sc)
FIND_PACKAGE(ScLang)

include_directories( "${CMAKE_SOURCE_DIR}/include/" )

add_executable(${EXECUTABLE_NAME} "src/main.cpp")

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/assets/start.scd ${CMAKE_BINARY_DIR}/)
