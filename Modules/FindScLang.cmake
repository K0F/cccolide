########################################################################################
##	SCLANG_FOUND - Found sclang
##	SCLANG_EXE - Exe sclang
########################################################################################

MESSAGE(STATUS "\nFindScLang init...")

MESSAGE(STATUS "SC_BUILD_DIR : " ${SC_BUILD_DIR})

FIND_PROGRAM(
  SCLANG_EXE
  NAMES sclang
  PATHS ${SC_BUILD_DIR}
  PATH_SUFFIXES 
  "Install/Supercollider"
  "lang"
)

SET(SCLANG_FOUND FALSE)

IF(SCLANG_EXE)
  SET(SCLANG_FOUND TRUE)
  MESSAGE(STATUS "SCLANG_PROGRAM : " ${SCLANG_EXE})
ENDIF()

MESSAGE(STATUS "FindScLang done...\n")
