# File: Makefile
# Author: Tim Press
# Creation Date: 08/15/2023
# File description: Makefile for elevator project
# Copyright Tim Press 2023
# =================================================================

# Makefile for elevator project

# There are 2 ways to build this project:
#
# 1. "make elevator", or
# 2. "make elevator graceful=1"

# "make elevator" means code will be compiled such that user input
# will be accepted as is, and upon detection of badinput (eg -3, INT_MAX+1, asdf)
# the program will terminate immediately. It will also provide a reason
# why the input (the first bad input detected) isn't correct

# "make elevator graceful=1" means code will be compiled that more
# gracefully handles bad program inputs. Ie, user will be given 
# as many attempts as needed to correct their input

CC = g++

elevator: elevator.o

elevator.o: elevator.cpp
ifdef graceful
	cc -D GRACEFUL_INPUT_HANDLING -c -v -ggdb elevator.cpp -o elevator.o
else
	cc -c -v -ggdb elevator.cpp -o elevator.o
endif

clean:
	rm -f elevator elevator.o