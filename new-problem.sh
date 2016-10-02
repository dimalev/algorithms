#!/bin/bash

NEW_PROBLEM_NAME=$1

if [ -d $NEW_PROBLEM_NAME ]; then
    echo "(EE)	Such problem already exist!"
    exit 1
fi

mkdir $NEW_PROBLEM_NAME
cd $NEW_PROBLEM_NAME

cp ../test/Makefile ./
cp ../test/prototype.cpp ./main.cpp

echo "Generation done!"
