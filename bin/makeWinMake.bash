#!/bin/bash

grep -v "\.\.\." Makefile | grep -v "###################" | grep -v "m68hc11-" > Makefile.windows

