#!/bin/bash

gcc main.c -o main -lm -lraylib -lGL -lpthread -ldl -lrt -lX11
./main
