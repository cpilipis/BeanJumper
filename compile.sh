#!/bin/bash

gcc --std=c99 -Wall src/main.c -lraylib -lchipmunk -oBeanjumper

echo compilation complete
