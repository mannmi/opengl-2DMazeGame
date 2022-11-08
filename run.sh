#!/bin/bash
PATH_BUILD="${PWD}/${1}"
PATH_CMAKE="${PWD}/${2}"

cd $PATH_BUILD
echo $(ls)
cmake -P $PATH_CMAKE
make
