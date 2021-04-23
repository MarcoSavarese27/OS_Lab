#!/bin/bash
x=$(wc -l < p.txt)
echo $x
y=$(wc -l < prova.txt)
echo $y
z=$((x+y))
echo $z
export z
