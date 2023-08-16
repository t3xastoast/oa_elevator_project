/*
=================================================================
File: elevator.h
Author: Tim Press
Creation Date: 08/11/2023
File description: Elevator class definition
Copyright Tim Press 2023
=================================================================

Elevator class file

IMPORTANT ASSUMPTIONS:

1. This program defines the valid range for a floor as [0, INT_MAX].

2. Because user input does not specify the tallest floor in this
theoretical building, it's assumed the tallest valid floor specified is
no larger than the tallest floor in the building.

3. The following information is assumed to be static during program execution:
	a. The total number of floors in the building (per assumption 2,
	will be unknown to this program/doesn't matter)
	b. The number of destination floors

4. All floors in the cmd line args are desired to be visited in
in the order specified

5. Travel time is defined as time elapsed while the elevator is moving.
It does NOT include time elapsed while the elevator is stationary. 
Additionally, travel time between any 2 adjacent floors is assumed 
to be constant (10)

*/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdio.h>
#include <iostream>	/* std::cout, std::endl */
#include <string>	/* std::string, stoi() */
#include <vector>	/* std::vector */
#include <queue>	/* std::queue */	
#include <cctype>	/* std::isdigit */
#include <cstdlib>	/* std::abs */
#include <sstream>	/* std::istringstream */

#define TRAVEL_TIME_PER_FLOOR 10

using namespace std;

class Elevator
{
public:
	
	/* Constructors & destructor */
	Elevator();
	Elevator(int start_floor);
	
	/* Generally a good idea to make destructors virtual, 
	but not needed here as no subclasses exist */
	~Elevator();

	/* move function */
	bool move(int new_floor);

	uint64_t get_travel_time();
	void set_curr_floor(int floor_val);


private:

	/* choosing to use int for curr_floor because stoi() returns int */
	int curr_floor;
	/* choosing uint64_t for travel time to allow for large number of input floors */
	uint64_t travel_time;
	/* vector<int> visited_floors;*/
};


#endif /* ELEVATOR_H */