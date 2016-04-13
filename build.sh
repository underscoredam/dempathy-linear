#!/usr/bin/env bash

mkdir -p dist #create dist directory if not exists

cd dist

if [ "$1" = "release" ]; then
   cmake -DCMAKE_BUILD_TYPE=Release .. && make
else
  cmake .. && make
fi

