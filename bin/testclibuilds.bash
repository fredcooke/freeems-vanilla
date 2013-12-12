#!/bin/bash

builds=('DEFAULT' 'XGATE' 'TRUCK' 'HOTEL' 'PRESTO' 'SEANKLT1' 'SNOTROCKET' 'SPUDMN' 'SLATER' 'PETERJSERIES' 'DEUCECOUPE' 'PETERTRUCK' 'DEFAULT' 'DEUCES10' 'SCAVENGER')
builds19s=('BenchTest' 'GM-LT1-CAS-360and8' 'MitsiAndMazda-CAS-4and1' 'HallOrOptical-Distributor-4of90' 'EvenTeeth-Cam-24and1' 'GM-LT1-CAS-360and8' 'EvenTeeth-Cam-24and1' 'MissingTeeth-Crank-8minus1' 'MissingTeeth-Crank-12minus1' 'JSeries-12CrankWith6-2Cam' 'EvenTeeth-Cam-6and1' 'MissingTeeth-Cam-12minus1' 'EvenTeeth-Distributor-4of6and1' 'EvenTeeth-Cam-4and1' 'MitsiAndMazda-CAS-4and2')

results[${#builds[*]} - 1]=0
failures=0

mkdir firmware-all

# Perform the tests
for ((i=0; i<${#builds[*]}; i++))
do
  CLIFLAGS="${builds[i]}" make clean ${builds19s[i]}
  results[i]=$?
  if ((${results[i]} != 0)); then
    failures=$(($failures+1))
  fi
  if [ -d firmware ]; then
    mv firmware/* firmware-all
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
