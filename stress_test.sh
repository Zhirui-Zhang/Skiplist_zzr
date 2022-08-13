#!/bin/bash
g++ -o stress_test test/stress_test.cpp --std=c++11 -pthread  
./stress_test