#!/bin/bash

echo $1
read
if [ $REPLY = $2 ]
then
    echo "OK"
    exit 0
fi

echo "FAIL"
exit 1
