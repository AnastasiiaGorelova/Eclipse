#!/usr/bin/env bash

set -euo pipefail

# serial
mkdir -p "dependencies/serial/build"
cd "dependencies/serial/build"
cmake -DDISABLE_CATKIN=ON -DCATKIN_ENABLE_TESTING=OFF ..
make
sudo make install
