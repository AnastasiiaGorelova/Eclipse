#!/usr/bin/env bash

# https://github.com/travis-ci/travis-ci/issues/5434
set -eo pipefail

mkdir build
cd build
cmake ..
make

# TODO: tests instead of hitting target
./example
