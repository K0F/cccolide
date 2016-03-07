MESSAGE(STATUS "\nFIND SC init...")

########################################################################################
##	SC_BUILD_FOUND - Found binary folder of Supercollider
##	SC_BUILD_DIR - Found binary folder of Supercollider
########################################################################################


SET(SC_BUILD_FOUND FALSE)

FIND_PATH(
  SC_BUILD_DIR
  NAMES SuperCollider.sln build_sclang.cfg
  PATHS 
  "C:/Supercollider/Supercollider_findModules"
  "D:/Supercollider/Supercollider_3.7"
  "/home/kof/src/supercollider/build"
  ONLY_CMAKE_FIND_ROOT_PATH
)

IF(SC_BUILD_DIR)
	SET(SC_BUILD_FOUND TRUE)
	message(STATUS "\t{SC_BUILD_DIR} - Supercollider source dir found: " ${SC_BUILD_DIR})
else()
  SET(SC_BUILD_DIR "Kdepak mas SC_build?")
	message(STATUS "Oh no, I coundn't find SuperCollider source path!")
ENDIF()

MESSAGE(STATUS "SC FOUND done...\n")
