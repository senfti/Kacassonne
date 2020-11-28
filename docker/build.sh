#!/bin/bash
cd /data/
mkdir -p docker_build
cd docker_build
cmake ..
make Kacassonne
make create_tar