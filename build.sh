#!/usr/bin/env bash

set -e

# Modified from TimescaleDB Source
# (https://www.timescale.com)

# Any flags will be passed on to CMake, e.g.,
# ./bootstrap -DCMAKE_BUILD_TYPE="Debug"

BUILD_DIR=${BUILD_DIR:-./build}
BUILD_FORCE_REMOVE=${BUILD_FORCE_REMOVE:-false}
SRC_DIR=$(dirname $0)
if [[ ! ${SRC_DIR} == /* ]]; then
    SRC_DIR=$(pwd)/${SRC_DIR}
fi

if [ ${BUILD_FORCE_REMOVE} == "true" ]; then
    rm -fr ${BUILD_DIR}
elif [ -d ${BUILD_DIR} ]; then
    echo "Build system already initialized in ${BUILD_DIR}"

    rm -fr ${BUILD_DIR}
fi

set -e
set -u

mkdir -p ${BUILD_DIR} && \
    cd ${BUILD_DIR} && \
    cmake ${SRC_DIR} "$@"

echo -n "build system initialized in ${BUILD_DIR}. To compile, doing:"
echo -e "\033[1mcd ${BUILD_DIR} && make\033[0m"

make install
cd ..

#cd ./$BUILD_DIR/ && make && cd ..

