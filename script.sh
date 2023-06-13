#!/bin/bash

# set variables
m=$(( $RANDOM % 100 + 1 ))
n=$(( $RANDOM % 100 + 1 ))
numColors=$(( $RANDOM % 20 + 1 ))

# create a map
./geramapa $m $n $numColors > mapa.txt

# generate the moves
./floodit < mapa.txt

# animate
cat mapa.txt solution.txt | ./anima
