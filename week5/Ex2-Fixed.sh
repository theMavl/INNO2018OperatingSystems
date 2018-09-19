#!/bin/bash

while true
do
    if ! [ -f $1.lock ] ;
    then
        if ln -s $1 $1.lock;
        then
            ./Ex2-Writer.sh $1
            rm -f $1.lock;
        fi
    fi
    sleep 0
done
