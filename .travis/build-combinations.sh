#!/bin/sh

BUILD_DIR=$(realpath $1)
INSTALL_PATH=$(realpath $2)
BOOST_INCLUDE_DIRS=$3
BOOST_LIBS_DIR=$4
BUILD_TYPE=$5
PROJECT_DIR=$PWD

CPP="/usr/include;/usr/local/include"

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake $PROJECT_DIR \
-DCMAKE_PREFIX_PATH=$CPP \
-DCMAKE_INSTALL_PREFIX=$INSTALL_PATH \
-DBUILD_TESTS=ON \
-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
-DBOOST_INCLUDE_DIRS=$BOOST_INCLUDE_DIRS \
-DBOOST_LIBS_DIR=$BOOST_LIBS_DIR

make
make install
