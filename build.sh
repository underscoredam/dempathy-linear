#!/bin/bash

cd dist

if [ "$1" = "lib" ]; then
	echo "building shared library"
	cmake .. -DLIB=ON && make
else
	echo "building executable"
	cmake .. -DLIB=OFF && make
fi;
