project(test)

cmake_minimum_required( VERSION 3.4.0 )

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


### EXTERNAL PROJECTS #######################################################################

include(ExternalProject)

ExternalProject_Add(cprocessing
 GIT_REPOSITORY "https://github.com/K0F/cprocessing.git"
 GIT_TAG "origin/master"
 PREFIX "externals"
 UPDATE_COMMAND ""
 TIMEOUT 10
 ALWAYS 1
)
SET(CPROCESSING_INCLUDE_DIR "${CMAKE_BINARY_DIR}/externals/src/cprocessing/include/")
SET(CPROCESSING_BUILD_DIR "${CMAKE_BINARY_DIR}/externals/src/cprocessing-build/")
MESSAGE(STATUS "ok got cprocessing CPROCESSING_INCLUDE_DIR ${CPROCESSING_INCLUDE_DIR}")
MESSAGE(STATUS "ok got cprocessing CPROCESSING_BUILD_DIR ${CPROCESSING_BUILD_DIR}")


ExternalProject_Add(freeglut
 GIT_REPOSITORY "https://github.com/K0F/freeglut.git"
 GIT_TAG "origin/master"
 PREFIX "externals"
 UPDATE_COMMAND ""
 TIMEOUT 10
 ALWAYS 1
)
SET(freeglut_INCLUDE_DIR "${CMAKE_INCLUDE_DIR}/externals/src/freeglut/include/GL")
SET(freeglut_BUILD_DIR "${CMAKE_BINARY_DIR}/externals/src/freeglut-build/lib")

# SET(GLUT_ROOT_PATH ${freeglut_INCLUDE_DIR})
MESSAGE(STATUS "ok got freeglut freeglut_INCLUDE_DIR ${freeglut_INCLUDE_DIR}")
MESSAGE(STATUS "ok got freeglut freeglut_BUILD_DIR ${freeglut_BUILD_DIR}")



if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install" CACHE STRING "Cmake install path" FORCE)
endif()

### OPENGL MODULE FIND #######################################################################

find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)


### SET TARGETS (INCLUDING ORDER) ############################################################


link_directories(
  "${CPROCESSING_BUILD_DIR}"
  "${freeglut_BUILD_DIR}"
)

add_executable(cccolider "src/main.cpp")
add_dependencies(cccolider cprocessing)
add_dependencies(cprocessing freeglut)


### LINKING ############################################################


target_include_directories(cccolider PUBLIC
  "${CPROCESSING_INCLUDE_DIR}"
    "${OPENGL_INCLUDE_DIRS}"
    "${freeglut_INCLUDE_DIR}"
)


# LINUX LIBRARIES
if(UNIX)
    target_link_libraries(cccolider
    glfw
    X11
    Xext
    Xmu
    Xxf86vm
    Xi
    Xrandr
    ${OPENGL_LIBRARIES}
    "libcprocessing.a"
    "libglut.a"
)
endif()

# WINDOWS LIBRARIES
if(WIN32)
  target_link_libraries(cccolider
    ${OPENGL_LIBRARIES}
    "cprocessing.lib"
    "glut.lib"
  )
endif()



### INSTALL (TODO) ############################################################
