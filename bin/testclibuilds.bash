#!/bin/bash

builds=('DEFAULT' 'XGATE' 'TRUCK' 'HOTEL' 'PRESTO' 'SEANKLT1' 'SNOTROCKET' 'SPUDMN' 'SLATER' 'PETERJSERIES' 'DEUCECOUPE' 'PETERTRUCK')

results[${#builds[*]} - 1]=0
failures=0

# Perform the tests
for ((i=0; i<${#builds[*]}; i++))
do
  CLIFLAGS="-D ${builds[i]}=1" make clean s19
  results[i]=$?
  if ((${results[i]} != 0)); then
    failures=$(($failures+1))
  fi
done

# Report it all
echo
echo "#################" Built the firmware ${#builds[*]} times with $failures failures! "#################"
echo Passes:
for ((i=0; i<${#builds[*]}; i++))
do
  if ((${results[$i]} == 0)); then
    echo ${builds[i]} passed!
  fi
done
if (($failures != 0)); then
  echo
  echo Failures:
  for ((i=0; i<${#builds[*]}; i++))
  do
    if ((${results[$i]} != 0)); then
      echo ${builds[i]} FAILED with result ${results[$i]}
    fi
  done
fi
echo "################################################################################"
