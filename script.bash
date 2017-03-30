#!/bin/bash


for i in `ls *".jpg"`
  do
      echo "$i"
      ./read_image $i $i.hist
    
  done




