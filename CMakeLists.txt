project( property )
cmake_minimum_required( VERSION 3.0 )

option( BUILD_EXAMPLE "Build example use property" OFF )

find_package( Boost 1.65.1 REQUIRED )

file( GLOB property_source ${CMAKE_CURRENT_SOURCE_DIR}/src/*.[ch]pp )
add_library( ${PROJECT_NAME} ${property_source} )
target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIR} )
set_target_properties( ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES )

if( BUILD_EXAMPLE )
    add_executable( example example/example.cpp )
    target_link_libraries( example ${PROJECT_NAME} )
endif()
