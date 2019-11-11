#!/bin/bash

set -x
set -u

NAME=pass_the_error
THRIFT_FILE_NAME="${NAME}"

GEN_DIR=dist/gen-cpp
mkdir -p "${GEN_DIR}" 
thrift --gen cpp --out "${GEN_DIR}" "${THRIFT_FILE_NAME}".thrift
OBJS="${NAME}.cpp ${NAME}_error.cpp ${GEN_DIR}/${THRIFT_FILE_NAME}_types.cpp ${GEN_DIR}/${THRIFT_FILE_NAME}_constants.cpp"
TARGET_DIR=dist

CXXFLAGS="-Wall -Wpedantic -std=c++14 -g"
g++ ${CXXFLAGS} -I. ${OBJS} -shared -fPIC -o "${TARGET_DIR}"/lib"${NAME}".so
