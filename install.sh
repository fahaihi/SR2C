#!/bin/bash
g++ src/PCHL.cpp -std=c++11 -w -fpermissive -fopenmp -O3 -o src/PCHL.out
g++ src/RCHL.cpp -std=c++11 -w -fpermissive -fopenmp -O3 -o src/RCHL.out
g++ src/verify.cpp -O3 -std=c++11 -w -o src/verify.out
chmod +x SR2C