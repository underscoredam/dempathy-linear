#!/usr/bin/env bash

if [ ! -f ./dist/dempathy-linear ]; then
    echo "NOT FOUND EXECUTABLE";
    ./build.sh
fi

if [ ! -f ./ikpMP3.dylib]; then
  echo "NOT FOUND ikpMP3 LIBRARY";
  ln -sf $(pwd)/linear/libs/irrKlang-64bit-1.5.0/bin/macosx-gcc/ikpMP3.dylib  ./ikpMP3.so
else
  echo "FOUND MP3 LIBRARY"
fi

./dist/dempathy-linear
