#!/bin/bash

tag=$( tail -n 1 $1 )
echo $(($tag+1)) >> $1
