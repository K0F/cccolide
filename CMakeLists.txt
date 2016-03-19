project(test)

cmake_minimum_required( VERSION 3.4.0 )

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(ExternalProject)

#ExternalProject_Add(oscpack
#  GIT_REPOSITORY "https://github.com/K0F/oscpack.git"
#  GIT_TAG "origin/master"
# PREFIX "externals"
#  UPDATE_COMMAND ""
#  EXCLUDE_FROM_MAIN "0"
#  )
#  ExternalProject_Get_Property(oscpack source_dir)
#  ExternalProject_Get_Property(oscpack binary_dir)

#  MESSAGE(STATUS "ok got oscpack ${source_dir}")
#  MESSAGE(STATUS "ok got oscpack ${binary_dir}")

#  include_directories(
#  "${source_dir}/osc"
#"${source_dir}/ip"
#)


execute_process(COMMAND git clone "https://github.com/K0F/cprocessing.git" "${CMAKE_SOURCE_DIR}/cprocessing")
SET(CPROCESSING_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/cprocessing/include")
MESSAGE(STATUS "ok got cprocessing CPROCESSING_INCLUDE_DIR ${CPROCESSING_INCLUDE_DIR}")

add_subdirectory(cprocessing)

#ExternalProject_Add(cprocessing
#  GIT_REPOSITORY "https://github.com/K0F/cprocessing.git"
#  GIT_TAG "origin/master"
#  PREFIX "externals"
#  UPDATE_COMMAND ""
#  TIMEOUT 10
#  ALWAYS 1
#)


#ExternalProject_Get_Property(cprocessing source_dir)
#ExternalProject_Get_Property(cprocessing binary_dir)


  include_directories(
  "${CPROCESSING_INCLUDE_DIR}"
)

# export(PACKAGE oscpack)
# export(PACKAGE cprocessing)

SET(EXECUTABLE_NAME "cccolider")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install" CACHE STRING "Cmake install path" FORCE)
endif()

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Modules)

# FIND_PACKAGE(Sc)
# FIND_PACKAGE(ScLang)


include_directories( "${CMAKE_SOURCE_DIR}/include/" )


# add_custom_target(cprocessing_pre ALL DEPENDS cprocessing)
add_executable(${EXECUTABLE_NAME} "src/main.cpp")

link_directories(${EXECUTABLE_NAME} "${CMAKE_BUILD_DIR}/cprocessing/")
link_libraries(${EXECUTABLE_NAME} libcprocessing.a)
# add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/assets/start.scd)
