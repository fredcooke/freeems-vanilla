#!/bin/bash

CLIFLAGS="-D CHECKDEFAULT=1" make clean s19
sleep 1
CLIFLAGS="-D XGATE=1" make clean  s19
sleep 1
CLIFLAGS="-D TRUCK=1" make clean  s19
sleep 1
CLIFLAGS="-D HOTEL=1" make clean  s19
sleep 1
CLIFLAGS="-D PRESTO=1" make clean  s19
sleep 1
CLIFLAGS="-D SEANKR1=1" make clean  s19
sleep 1
CLIFLAGS="-D SEANKLT1=1" make clean  s19
sleep 1
CLIFLAGS="-D JOSHBROWN=1" make clean s19
sleep 1
CLIFLAGS="-D SNOTROCKET=1" make clean s19

# Someone with elite bash skills grab the result from each of these and print them at the end, please.
