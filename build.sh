#!/bin/bash

BUILDDIR="./build"

if [ -d $BUILDDIR ]; then
	echo "Whiping previous build directory"
	rm -rf $BUILDDIR
fi
echo "Creating build directory"
mkdir -p $BUILDDIR

echo "Generating makefile using cmake"
cd $BUILDDIR
cmake -DCMAKE_BUILD_TYPE=Debug ..

echo "Building ..."
make

ls -al sdl-bird

cd ..

