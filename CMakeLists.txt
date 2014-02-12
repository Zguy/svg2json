cmake_minimum_required (VERSION 2.6)

project (svg2json)

set (SRCROOT "${PROJECT_SOURCE_DIR}/src")

set (SRC
	"${SRCROOT}/JSONPath.cpp"
	"${SRCROOT}/JSONPath.h"
	"${SRCROOT}/main.cpp"
	"${SRCROOT}/SVGParser.cpp"
	"${SRCROOT}/SVGParser.h"
	"${SRCROOT}/SVGPath.cpp"
	"${SRCROOT}/SVGPath.h"
	"${SRCROOT}/Vector.h"
)

find_package (Boost 1.48.0 REQUIRED COMPONENTS program_options)
find_library (pugixml_LIBRARY pugixml)
find_path (pugixml_INCLUDE pugixml.hpp)

set (DEPS_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} ${pugixml_INCLUDE})
set (DEPS_LIBRARIES ${Boost_LIBRARIES} ${pugixml_LIBRARY})

include_directories (${DEPS_INCLUDE_DIRS})

add_executable (svg2json ${SRC})

target_link_libraries (svg2json ${DEPS_LIBRARIES})

if (CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties (svg2json PROPERTIES COMPILE_FLAGS "-std=c++11")
endif ()

