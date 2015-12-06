
#  $Id$

SET(_log_detailed "${CMAKE_BINARY_DIR}/detailed.log")
FILE(REMOVE ${_log_detailed})

MACRO(_detailed)
  FILE(APPEND ${_log_detailed} "${ARGN}")
ENDMACRO()

_detailed(
"###
#
#  SOLVER configuration:
#        DEAL_II_DIR:            ${deal.II_DIR}
#        DEAL_II VERSION:        ${DEAL_II_PACKAGE_VERSION}
#        SOLVER_USE_PETSC:       ${SOLVER_USE_PETSC}
#        CMAKE_BUILD_TYPE:       ${CMAKE_BUILD_TYPE}
#        CMAKE_INSTALL_PREFIX:   ${CMAKE_INSTALL_PREFIX}
#        CMAKE_SOURCE_DIR:       ${CMAKE_SOURCE_DIR} 
#        CMAKE_BINARY_DIR:       ${CMAKE_BINARY_DIR}
#        CMAKE_CXX_COMPILER:     ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} on platform ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}
#                                ${CMAKE_CXX_COMPILER}
")
IF(CMAKE_C_COMPILER_WORKS)
  _detailed("#        CMAKE_C_COMPILER:       ${CMAKE_C_COMPILER}\n")
ENDIF()


IF(DEAL_II_STATIC_EXECUTABLE)
_detailed(
"#
#        LINKAGE:                STATIC
")
ELSE()
_detailed(
"#
#        LINKAGE:                DYNAMIC
")
ENDIF()

_detailed("#\n###")
