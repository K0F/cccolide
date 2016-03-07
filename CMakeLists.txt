project(test)

cmake_minimum_required( VERSION 2.8.11 )

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install" CACHE STRING "Cmake install path" FORCE)
endif()

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Modules)

FIND_PACKAGE(Sc)
FIND_PACKAGE(ScLang)

add_executable(aaa main.cpp)