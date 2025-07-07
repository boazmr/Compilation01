#!/bin/bash

for i in {1..4}
do
  ./hw5 < hw5-tests/t$i.in > gen_code.llvm
  lli gen_code.llvm > hw5-tests/res_$i

  if diff -q hw5-tests/t$i.out hw5-tests/res_$i > /dev/null; then
    echo -e "\e[32mTest $i passed\e[0m"
  else
    echo -e "\e[31mTest $i failed\e[0m"
    diff hw5-tests/t$i.out hw5-tests/res_$i
  fi
done
