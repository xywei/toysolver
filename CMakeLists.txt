#  $Id$


MESSAGE("====================================================")
MESSAGE("============ Configuring Solver ====================")
MESSAGE("====================================================")

# Set the name of the project and target:
SET(TARGET "toysolver")
FILE(GLOB_RECURSE TARGET_SRC "source/*.cpp" "include/*.hpp")
INCLUDE_DIRECTORIES(include)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

FIND_PACKAGE(deal.II 8.3 QUIET
  HINTS ${deal.II_DIR} ${DEAL_II_DIR} ../ ../../ $ENV{DEAL_II_DIR}
  )
IF(NOT ${deal.II_FOUND})
  MESSAGE(FATAL_ERROR "\n*** Could not find a suitably recent version of deal.II. ***\n"
    "You may want to either pass a flag -DDEAL_II_DIR=/path/to/deal.II to cmake "
    "or set an environment variable \"DEAL_II_DIR\" that contains a path to a "
    "sufficiently recent version of deal.II."
    )
ENDIF()

MESSAGE(STATUS "Found deal.II version ${DEAL_II_PACKAGE_VERSION} at '${deal.II_DIR}'")

SET(SOLVER_USE_PETSC OFF CACHE BOOL "Use PETSc instead of Trilinos if set to 'on'.")

MESSAGE(STATUS "Using PETSc = '${SOLVER_USE_PETSC}'")

SET(_DEALII_GOOD ON)

IF(SOLVER_USE_PETSC AND NOT DEAL_II_WITH_PETSC)
    MESSAGE(SEND_ERROR
      "\n-- deal.II was built without support for PETSc!\n"
      )
    SET(_DEALII_GOOD OFF)
ENDIF()

IF(NOT DEAL_II_WITH_P4EST)
    MESSAGE(SEND_ERROR
      "\n-- deal.II was built without support for p4est!\n"
      )
    SET(_DEALII_GOOD OFF)
ENDIF()

IF(NOT SOLVER_USE_PETSC AND NOT DEAL_II_WITH_TRILINOS)
    MESSAGE(SEND_ERROR
      "\n-- deal.II was built without support for Trilinos!\n"
      )
    SET(_DEALII_GOOD OFF)
ENDIF()

IF (NOT _DEALII_GOOD)
  MESSAGE(FATAL_ERROR
    "\nSOLVER requires a deal.II installation built with support for Trilinos/PETSc and p4est but one or both of these appears to be missing!\n"
    )
ENDIF()

DEAL_II_INITIALIZE_CACHED_VARIABLES()
PROJECT(${TARGET})

IF (SOLVER_USE_PETSC)
FOREACH(_source_file ${TARGET_SRC})
  SET_PROPERTY(SOURCE ${_source_file}
    APPEND PROPERTY COMPILE_DEFINITIONS SOLVER_USE_PETSC="1")
ENDFOREACH()
ENDIF()


# Pass down the source directory to the sources. This can be used
# to hard-code the location of data files, such as in
# $SOLVER_SOURCE_DIR/data/*
FOREACH(_source_file ${TARGET_SRC})
  SET_PROPERTY(SOURCE ${_source_file}
    APPEND PROPERTY COMPILE_DEFINITIONS SOLVER_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
ENDFOREACH()


# Configure a cmake fragment that plugins can use to
# set up compiler flags, include paths, etc to compile a
# runtime loadable plugin
CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/SolverConfig.cmake.in
  ${CMAKE_BINARY_DIR}/SolverConfig.cmake
  @ONLY
)

# Next, set up the testsuite
IF(EXISTS ${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt)
  ENABLE_TESTING()
  ADD_SUBDIRECTORY(tests)
ENDIF()

MESSAGE("====================================================")

# Depending on whether we link statically or allow for shared libs,
# we can or can not load plugins via external shared libs. Pass this
# down during compilation so we can disable it in the code
IF (DEAL_II_STATIC_EXECUTABLE STREQUAL "ON")
  MESSAGE(STATUS "Creating a statically linked executable")
  MESSAGE(STATUS "Disabling dynamic loading of plugins from the input file")
  FOREACH(_source_file ${TARGET_SRC})
    SET_PROPERTY(SOURCE ${_source_file}
      APPEND PROPERTY COMPILE_DEFINITIONS SOLVER_USE_SHARED_LIBS=0)
  ENDFOREACH()
ELSE()
  MESSAGE(STATUS "Enabling dynamic loading of plugins from the input file")
  FOREACH(_source_file ${TARGET_SRC})
    SET_PROPERTY(SOURCE ${_source_file}
      APPEND PROPERTY COMPILE_DEFINITIONS SOLVER_USE_SHARED_LIBS=1)
  ENDFOREACH()
ENDIF()

# See whether we can verify that every plugin we load is compiled against
# the same deal.II library
INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES ("link.h" _HAVE_LINK_H)
IF (_HAVE_LINK_H)
  MESSAGE(STATUS "Enabling checking of compatible deal.II library when loading plugins")
  FOREACH(_source_file ${TARGET_SRC})
    SET_PROPERTY(SOURCE ${_source_file}
      APPEND PROPERTY COMPILE_DEFINITIONS SOLVER_HAVE_LINK_H=1)
  ENDFOREACH()
ENDIF()

DEAL_II_INVOKE_AUTOPILOT()

MESSAGE(STATUS "Writing config into detailed.log...")
LIST(APPEND CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}
  )

INCLUDE(write_config)

