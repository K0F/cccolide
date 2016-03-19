MESSAGE(STATUS "\nFIND CPROCESSING init...")

########################################################################################
##	CPROCESSING_BUILD_FOUND - Found binary folder of Supercollider
##	CPROCESSING_BUILD_DIR - Found binary folder of Supercollider
########################################################################################


SET(CPROCESSING_BUILD_FOUND FALSE)

FIND_PATH(
  CPROCESSING_BUILD_DIR
  NAMES libcprocessing.a
  PATHS
  "${CMAKE_BUILD_PATH}/externals/src/cprocessing-build"
  ONLY_CMAKE_FIND_ROOT_PATH
)


FIND_PATH(
  CPROCESSING_INCLUDE_DIR
  NAMES cprocessing.hpp
  PATHS
  "${CMAKE_BUILD_PATH}/externals/src/cprocessing/include"
  ONLY_CMAKE_FIND_ROOT_PATH
)

IF(CPROCESSING_BUILD_DIR)
	SET(CPROCESSING_BUILD_FOUND TRUE)
	message(STATUS "\tCPROCESSING_INCLUDE_DIR - cprocessing include dir found: " ${CPROCESSING_INCLUDE_DIR})
  message(STATUS "\tCPROCESSING_BUILD_DIR - cprocessing build dir found: " ${CPROCESSING_BUILD_DIR})
else()
  SET(CPROCESSING_BUILD_DIR "Kdepak mas CPROCESSING_build?")
	message(STATUS "Oh no, I coundn't find SuperCollider source path!")
ENDIF()

MESSAGE(STATUS "CPROCESSING FOUND done...\n")
