project(test)

cmake_minimum_required( VERSION 3.4.0 )

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(ExternalProject)


ExternalProject_Add(cprocessing
 GIT_REPOSITORY "https://github.com/K0F/cprocessing.git"
 GIT_TAG "origin/master"
 PREFIX "externals"
 UPDATE_COMMAND ""
 TIMEOUT 10
 ALWAYS 1
)
SET(CPROCESSING_INCLUDE_DIR "${CMAKE_INCLUDE_DIR}/externals/src/cprocessing/include/")
SET(CPROCESSING_BUILD_DIR "${CMAKE_BUILD_DIR}/externals/src/cprocessing-build/")
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
SET(freeglut_BUILD_DIR "${CMAKE_BUILD_DIR}/externals/src/freeglut-build/lib")

# SET(GLUT_ROOT_PATH ${freeglut_INCLUDE_DIR})
MESSAGE(STATUS "ok got freeglut freeglut_INCLUDE_DIR ${freeglut_INCLUDE_DIR}")
MESSAGE(STATUS "ok got freeglut freeglut_BUILD_DIR ${freeglut_BUILD_DIR}")



# add_subdirectory(cprocessing)
# add_subdirectory(src)


if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install" CACHE STRING "Cmake install path" FORCE)
endif()

# LIST(APPEND ${CMAKE_SOURCE_DIR}/Modules CMAKE_MODULE_PATH )
# LIST(APPEND ${CMAKE_SOURCE_DIR}/Modules ${CMAKE_MODULE_PATH} CMAKE_MODULE_PATH)


find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)
# include_directories( ${OPENGL_INCLUDE_DIRS}  ${freeglut_INCLUDE_DIR} )
include_directories( ${freeglut_INCLUDE_DIR} )

link_directories(
"${CPROCESSING_BUILD_DIR}"
"${freeglut_BUILD_DIR}"
)

add_executable(cccolider "src/main.cpp")
add_dependencies(cccolider cprocessing)
add_dependencies(cprocessing freeglut)

target_include_directories(cccolider PUBLIC
  "${CMAKE_SOURCE_DIR}/include/"
  "${CPROCESSING_INCLUDE_DIR}"
)


if(UNIX)
target_link_libraries(cccolider
X11
Xext
Xmu
Xxf86vm
Xi
)


target_link_libraries(cccolider
  ${OPENGL_LIBRARIES}
  "libcprocessing.a"
  "libglut.a"
)
endif()

if(WIN32)

  target_link_libraries(cccolider
    ${OPENGL_LIBRARIES}
    "cprocessing.lib"
    "glut.lib"
  )
endif()



# add_custom_command(OUTPUT libcprocessing.a ${cprocessing_src})
# add_custom_command(OUTPUT cccolide "src/main.cpp" ALL DEPENDS cprocessing)

# add_executable(${EXECUTABLE_NAME} "src/main.cpp" "${CMAKE_SOURCE_DIR}/cprocessing/include/cprocessing.hpp")

# add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/assets/start.scd)
