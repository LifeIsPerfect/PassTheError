cmake_minimum_required( VERSION 3.7.2 )

if(${CMAKE_VERSION} VERSION_GREATER "3.9.0")
     project( PassTheError VERSION 1.0.0 DESCRIPTION "A small library to pass the std::error_code objects through processes." )
else()
     project( PassTheError VERSION 1.0.0 )
endif()

include(GNUInstallDirs)

set(THRIFT "/usr/bin/thrift" CACHE FILEPATH "thrift compiler path")
set(THRIFT_INCLUDE "/usr/include" CACHE FILEPATH "thrift library include directory path")

ADD_CUSTOM_COMMAND(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/pass_the_error_types.cpp ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/pass_the_error_constants.cpp
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp
  COMMAND ${THRIFT} --gen cpp --out ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/ ${CMAKE_SOURCE_DIR}/pass_the_error.thrift
  MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/pass_the_error.thrift
)

add_library( pass_the_error SHARED 
     ${CMAKE_SOURCE_DIR}/source/pass_the_error.cpp
     ${CMAKE_SOURCE_DIR}/source/pass_the_error_error.cpp
     ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/pass_the_error_types.cpp
     ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/pass_the_error_constants.cpp
)

set_target_properties( pass_the_error PROPERTIES VERSION ${PROJECT_VERSION} )
set_target_properties( pass_the_error PROPERTIES SOVERSION 1 )

set_target_properties( pass_the_error PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/pass_the_error_error.hpp;${CMAKE_SOURCE_DIR}/include/pass_the_error.hpp" )

target_include_directories( pass_the_error PRIVATE ${THRIFT_INCLUDE} )
target_include_directories( pass_the_error PRIVATE ${CMAKE_SOURCE_DIR} )
target_include_directories( pass_the_error PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp )

install(
  TARGETS pass_the_error 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
