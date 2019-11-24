cmake_minimum_required( VERSION 3.9.0 )

project( PassTheError VERSION 1.0.0 DESCRIPTION "A small library to pass the std::error_code objects through processes." )
include(GNUInstallDirs)

ADD_CUSTOM_COMMAND(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/pass_the_error_types.cpp ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/pass_the_error_constants.cpp
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp
  COMMAND thrift --gen cpp --out ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/ ${CMAKE_SOURCE_DIR}/pass_the_error.thrift
  MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/pass_the_error.thrift
)

add_library( PassTheError SHARED 
     ${CMAKE_SOURCE_DIR}/source/pass_the_error.cpp
     ${CMAKE_SOURCE_DIR}/source/pass_the_error_error.cpp
     ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/pass_the_error_types.cpp
     ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/pass_the_error_constants.cpp
)

set_target_properties( PassTheError PROPERTIES VERSION ${PROJECT_VERSION} )
set_target_properties( PassTheError PROPERTIES SOVERSION 1 )

set_target_properties( PassTheError PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/pass_the_error_error.hpp;${CMAKE_SOURCE_DIR}/include/pass_the_error.hpp" )

target_include_directories( PassTheError PRIVATE ${CMAKE_SOURCE_DIR} )
target_include_directories( PassTheError PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp )

install(
  TARGETS PassTheError
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
