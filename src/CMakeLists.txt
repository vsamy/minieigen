include(../../cmake/python.cmake)

configure_file(__init__.py ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/__init__.py COPYONLY)

add_definitions(-DEIGEN_DONT_ALIGN)

FINDPYTHON()
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})

set(CONVSOURCES double-conversion/bignum.cc double-conversion/bignum-dtoa.cc double-conversion/cached-powers.cc
    double-conversion/diy-fp.cc double-conversion/double-conversion.cc double-conversion/fast-dtoa.cc
    double-conversion/fixed-dtoa.cc double-conversion/strtod.cc)
set(CONVHEADERS double-conversion/bignum-dtoa.h double-conversion/bignum.h double-conversion/cached-powers.h
    double-conversion/diy-fp.h double-conversion/double-conversion.h double-conversion/fast-dtoa.h
    double-conversion/fixed-dtoa.h double-conversion/ieee.h double-conversion/strtod.h double-conversion/utils.h)
set(SOURCES expose-boxes.cpp expose-complex.cpp expose-converters.cpp expose-matrices.cpp
    expose-quaternion.cpp expose-vectors.cpp minieigen.cpp)
set(HEADERS common.hpp converters.hpp expose.hpp visitors.hpp)


add_library(_${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${CONVSOURCES} ${CONVHEADERS})
target_link_libraries(_${PROJECT_NAME} ${Boost_LIBRARIES})
set_target_properties(_${PROJECT_NAME} PROPERTIES PREFIX "")

install(TARGETS _${PROJECT_NAME} DESTINATION "${PYTHON_SITELIB}/${PROJECT_NAME}")
PYTHON_INSTALL_BUILD(${PROJECT_NAME} __init__.py "${PYTHON_SITELIB}")