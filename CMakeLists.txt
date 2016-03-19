project(test)

cmake_minimum_required( VERSION 3.4.0 )

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(ExternalProject)

ExternalProject_Add(oscpack
  GIT_REPOSITORY "https://github.com/K0F/oscpack.git"
  GIT_TAG "origin/master"
PREFIX "externals"
  UPDATE_COMMAND ""
  EXCLUDE_FROM_MAIN "0"
  )
  ExternalProject_Get_Property(oscpack source_dir)
  ExternalProject_Get_Property(oscpack binary_dir)

  MESSAGE(STATUS "ok got oscpack ${source_dir}")
  MESSAGE(STATUS "ok got oscpack ${binary_dir}")

  include_directories(
  "${source_dir}/osc"
"${source_dir}/ip"
)



ExternalProject_Add(cprocessing
  GIT_REPOSITORY "https://github.com/K0F/cprocessing.git"
  GIT_TAG "origin/master"
  PREFIX "externals"
  UPDATE_COMMAND ""
  EXCLUDE_FROM_MAIN "0"
)
ExternalProject_Get_Property(cprocessing source_dir)
ExternalProject_Get_Property(cprocessing binary_dir)

MESSAGE(STATUS "ok got cprocessing ${source_dir}")
MESSAGE(STATUS "ok got cprocessing ${binary_dir}")

  include_directories(
  "${source_dir}/include"
)

# export(PACKAGE oscpack)
# export(PACKAGE cprocessing)

SET(EXECUTABLE_NAME "aaa")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install" CACHE STRING "Cmake install path" FORCE)
endif()

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Modules)

# FIND_PACKAGE(Sc)
# FIND_PACKAGE(ScLang)

include_directories( "${CMAKE_SOURCE_DIR}/include/" )

add_executable(${EXECUTABLE_NAME} "src/main.cpp")

# add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/assets/start.scd)
