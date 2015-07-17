cmake_minimum_required( VERSION 3.1.3 )

project( MiniLD_61 CXX )

set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH} )
set( CMAKE_CXX_STANDARD 11 )

find_package( SFML 2 REQUIRED COMPONENTS audio graphics system window )
include_directories( ${SFML_INCLUDE_DIR} )

add_subdirectory( Source )

