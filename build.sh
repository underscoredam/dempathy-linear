#!/usr/bin/env bash

mkdir -p dist #create dist directory if not exists

cd dist

cmake .. && make

