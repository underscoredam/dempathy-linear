#!/usr/bin/env bash

SYSTEM="$(uname)"

if [ ! -f ./dist/dempathy-linear ]; then
	echo "NOT FOUND EXECUTABLE";
	./build.sh
fi
if [ ! -f ./ikpMP3.dylib ] || [ ! -f ./ikpMP3.so ] || [ ! -f ./ikMP3.dll ]; then
	echo "NOT FOUND ikpMP3 LIBRARY";

	if [ ${SYSTEM} == "Darwin" ]; then
		ln -sf $(pwd)/dempathy-linear/libs/irrKlang-64bit-1.5.0/bin/macosx-gcc/ikpMP3.dylib  ./ikpMP3.dylib
	elif [ ${SYSTEM} == "Linux" ]; then
		ln -sf $(pwd)/dempathy-linear/libs/irrKlang-64bit-1.5.0/bin/linux-gcc-64/ikpMP3.so  ./ikpMP3.so
	elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
		ln -sf $(pwd)/dempathy-linear/libs/irrKlang-64bit-1.5.0/bin/winx64-visualStudioso/ikpMP3.dll ./ikMP3.dll
	fi
else
  echo "FOUND MP3 LIBRARY"
fi

./dist/dempathy-linear
