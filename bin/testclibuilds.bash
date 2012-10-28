#!/bin/bash

builds=('DEFAULT' 'XGATE' 'TRUCK' 'HOTEL' 'PRESTO' 'SEANKLT1' 'SNOTROCKET' 'SPUDMN' 'SLATER' 'PETERJSERIES' 'DEUCECOUPE' 'PETERTRUCK')

results[${#builds[*]} - 1]=0
failures=0

# Perform the tests
for ((i=0; i<${#builds[*]}; i++))
do
  CLIFLAGS="${builds[i]}" make clean s19
  results[i]=$?
  if ((${results[i]} != 0)); then
    failures=$(($failures+1))
  fi
  if [ -d firmware ]; then
    mv firmware firmware-${builds[i]}
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
