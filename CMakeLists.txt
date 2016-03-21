project(ccollider)

cmake_minimum_required( VERSION 3.4.0 )


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


### EXTERNAL PROJECTS #######################################################################

include(ExternalProject)

ExternalProject_Add(oscpack
  GIT_REPOSITORY "https://github.com/K0F/oscpack.git"
  GIT_TAG "master"
  PREFIX "externals"
  UPDATE_DISCONNECTED 0
  TIMEOUT 10
  ALWAYS 1
  )



ExternalProject_Add(cprocessing
  GIT_REPOSITORY "https://github.com/K0F/cprocessing.git"
  GIT_TAG "master"
  PREFIX "externals"
  UPDATE_DISCONNECTED 0
  TIMEOUT 10
  ALWAYS 1
  )



SET(OSCPACK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/externals/src/oscpack/")
SET(OSCPACK_BUILD_DIR "${CMAKE_BINARY_DIR}/externals/src/oscpack-build/")
MESSAGE(STATUS "ok got cprocessing OSCPACK_INCLUDE_DIR ${OSCPACK_INCLUDE_DIR}")
MESSAGE(STATUS "ok got cprocessing OSCPACK_BUILD_DIR ${OSCPACK_BUILD_DIR}")

SET(CPROCESSING_INCLUDE_DIR "${CMAKE_BINARY_DIR}/externals/src/cprocessing/include/")
SET(CPROCESSING_BUILD_DIR "${CMAKE_BINARY_DIR}/externals/src/cprocessing-build/")
MESSAGE(STATUS "ok got cprocessing CPROCESSING_INCLUDE_DIR ${CPROCESSING_INCLUDE_DIR}")
MESSAGE(STATUS "ok got cprocessing CPROCESSING_BUILD_DIR ${CPROCESSING_BUILD_DIR}")


###################################################################################################
###################################################################################################



if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install" CACHE STRING "Cmake install path" FORCE)
endif()

### OPENGL MODULE FIND #######################################################################

find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)


### SET TARGETS (INCLUDING ORDER) ############################################################


link_directories(
  "${CPROCESSING_BUILD_DIR}"
  "${OSCPACK_BUILD_DIR}"
  )

### LINKING ############################################################

if(UNIX)
  include_directories(ccollider
    ${OPENGL_INCLUDE_DIRS}
    )
endif()

include_directories(ccollider PUBLIC
  ${CPROCESSING_INCLUDE_DIR}
  ${OSCPACK_INCLUDE_DIR}
  "${OSCPACK_INCLUDE_DIR}/osc"
  "${OSCPACK_INCLUDE_DIR}/ip"
  )

add_executable(ccollider "src/main.cpp")
add_dependencies(ccollider oscpack)
add_dependencies(ccollider cprocessing)


# LINUX LIBRARIES
if(UNIX)
  target_link_libraries(ccollider
   ${OPENGL_LIBRARIES}
    "libcprocessing.a"
    "liboscpack.a"
    )
endif()

# WINDOWS LIBRARIES
if(WIN32)
  target_link_libraries(ccollider
    ${OPENGL_LIBRARIES}
    "cprocessing.lib"
    "oscpack.lib"
    )
endif()



### INSTALL (TODO) ############################################################
FILE(COPY "${CMAKE_SOURCE_DIR}/assets/start.scd" DESTINATION ${CMAKE_BINARY_DIR})
