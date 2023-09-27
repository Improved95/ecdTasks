#!/bin/bash
for ((i = 0; i < 10; i++))
do
  (time ./a.out) &>> res.txt
  echo "---" >> res.txt
done