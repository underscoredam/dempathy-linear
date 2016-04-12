#!/usr/bin/env bash

if [ ! -f ./dist/dempathy-linear ]; then
    echo "NOT FOUND EXECUTABLE";
    ./build.sh
fi

if [ ! -f ./ikpMP3.so ]; then
  echo "NOT FOUND ikpMP3 LIBRARY";
  ln -sf $(pwd)/dempathy-linear/libs/irrKlang-64bit-1.5.0/bin/linux-gcc-64/ikpMP3.so  ./ikpMP3.so
else
  echo "FOUND MP3 LIBRARY"
fi

./dist/dempathy-linear
