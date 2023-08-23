/*
=================================================================
File: elevator.cpp
Author: Tim Press
Creation Date: 08/15/2023
File description: Implementations for Elevator class member functions, main(), and static helper functions
Copyright Tim Press 2023
=================================================================

*/

#include "elevator.h"

using namespace std;

/* =================================================================
FUNCTION: Elevator default constructor

DESCRIPTION: Default constructor for elevator class

INPUTS: 
	None
OUTPUTS: 
	None
=================================================================*/
Elevator::Elevator()
{
	curr_floor = 1;
	travel_time = 0;
}

/* =================================================================
FUNCTION: Elevator floor constructor

DESCRIPTION: Creates an elevator instance starting at floor specified

INPUTS: 
	floor to start at (int)
OUTPUTS: 
	None
=================================================================*/
Elevator::Elevator(int start_floor)
{
	curr_floor = start_floor;
	travel_time = 0;
}

/* =================================================================
FUNCTION: Elevator default destructor

DESCRIPTION: Default destructor for elevator class

INPUTS: 
	None
OUTPUTS: 
	None
=================================================================*/
Elevator::~Elevator()
{

}

/* =================================================================
FUNCTION: Elevator::get_travel_time()

DESCRIPTION: Returns travel_time for elevator

INPUTS: 
	None
OUTPUTS: 
	travel_time (uint64_t)
=================================================================*/
uint64_t Elevator::get_travel_time()
{
	return travel_time;
}

/* =================================================================
FUNCTION: Elevator::set_curr_floor()

DESCRIPTION: Modifies elevator current floor

INPUTS: 
	int floor_val
OUTPUTS: 
	None
=================================================================*/
void Elevator::set_curr_floor(int floor_val)
{
	curr_floor = floor_val;
}

/* =================================================================
FUNCTION: Elevator::move(int new_floor)

DESCRIPTION: Moves elevator to new floor specified in input arg

INPUTS: 
	new_floor: destination floor for elevator
OUTPUTS: 
	true if successful, else false
=================================================================*/
bool Elevator::move(int new_floor)
{	
	bool result = true;
	int diff = abs(new_floor - curr_floor);

	/* update distance traveled. Need to guard against uint64_t overflow */

	/* if travel_time overflow occurs, throw an error */
	if (ULLONG_MAX - travel_time < TRAVEL_TIME_PER_FLOOR*diff)
	{
		result = false;
	}
	else
	{
		travel_time += (TRAVEL_TIME_PER_FLOOR*diff);
	}

	/* only update curr_floor if travel time didn't overflow */
	if (result == true)
	{
		curr_floor = new_floor;
	}

	return result;
}

/* static helper functions for main() */

/* =================================================================
FUNCTION: is_string_number

DESCRIPTION: Determines if string s is a number

INPUTS: 
	string s
OUTPUTS: 
	true if s is a number, else false
=================================================================*/
static bool is_string_number(string s)
{
	bool result = false;
	bool stop = false;
	for (int i = 0; i < s.size(); i++)
	{
		if(isdigit(s[i]) == 0)
		{
			cout << "floor " + s + " is not a valid number." << endl;
			stop = true;
			break;
		}
	}

	result = (stop ? false : true);
	return result;
}

/* =================================================================
FUNCTION: is_negative_number

DESCRIPTION: Determines if string s is a negative number

INPUTS: 
	string s
OUTPUTS: 
	true if s is a negative number, else false
=================================================================*/
static bool is_negative_number(string s)
{
	bool result = false;
	int len = s.size();
	if (len < 2)
	{
		result = false;
	}
	else if ( s[0] == '-' && is_string_number(s.substr(1, len-1)) )
	{
		cout << "negative floor " + s + " not allowed." << endl;
		result = true;
	}

	return result;
}

/* =================================================================
FUNCTION: validate_floor

DESCRIPTION: Validates that floor is in the allowed range [0, INT_MAX]

INPUTS: 
	string floor
OUTPUTS: 
	int floor if in range, else -1
=================================================================*/
static int validate_floor(string floor)
{
	int floor_int;
	try
	{
		floor_int = stoi(floor);
	}
	catch (const std::out_of_range & e)
	{
		cout << "floor  " + floor + " exceeds maxmimum allowed value " + to_string(INT_MAX) << endl;
		floor_int = -1;
	}

	return floor_int;
}

/* =================================================================
FUNCTION: main()

DESCRIPTION: Processes user input, and creates elevator instance
to perform floor traversal. Also gives user chances to correct input
if graceful flag is set

INPUTS: 
	int argc, char const *argv[]
OUTPUTS: 
	0 on success, else -1
=================================================================*/
int main(int argc, char const *argv[])
{
	Elevator my_elevator;
	queue<int> floors_to_visit;
	bool bad_input = false;
	bool initial_args_correct = true;
	bool distance_overflow = false;

	for (int i = 1; i < argc; i++)
	{
		string s(argv[i]);

		/* if arg not a number, or a negative number, flag bad input */
		if ( !is_string_number(s) || is_negative_number(s) ) 
		{
			bad_input = true;
			initial_args_correct = false;

			/* I was originally breaking here, but opting to comment
			it out so that user can see how many bad inputs they provided
			rather than only seeing the first one */

			/* break; */
		}
		/* verify floor is less than INT_MAX */
		else
		{
			int floor = validate_floor(s);

			if (floor >= 0)
			{
				floors_to_visit.push(floor);
			}
			else
			{
				bad_input = true;
				initial_args_correct = false;

				/* I was originally breaking here, but opting to comment
				it out so that user can see how many bad inputs they provided
				rather than only seeing the first one */

				/*break;*/
			}
		}
	}

#ifndef GRACEFUL_INPUT_HANDLING

	/* conditions to terminate program early */
	if (bad_input)
	{
		cout << "Bad input detected. Terminating program early." << endl;
		return -1;
	}

#else

	string new_input = "";
	bool valid_y = false;
	bool valid_n = false;

	while (bad_input)
	{
		/* clear the queue, and ask for new input */
		while(!floors_to_visit.empty())
		{
			floors_to_visit.pop();
		}

		cout << "Bad input detected. Please enter the floors you wish to visit (space separated). You may only enter non-negative numbers: ";
		getline(cin, new_input);

		/* check that valid numbers were entered */
		istringstream iss(new_input);
		string number;
		bad_input = false;

		while (iss >> number)
		{
			if ( !is_string_number(number) || is_negative_number(number) ) 
			{
				bad_input = true;
				break;
			}

			floors_to_visit.push(stoi(number));
		}
	}

#endif

	/* else, we have valid input by this point :) so traverse the floors */
	if (!floors_to_visit.empty())
	{
		my_elevator.set_curr_floor(floors_to_visit.front());
		floors_to_visit.pop();
	}

	while(!floors_to_visit.empty())
	{
		/* visit floors! */ 
		if (my_elevator.move(floors_to_visit.front()) == false)
		{
			/* NOTE: Intentionally waiting to print out visited floors
			until the end in case a distace overflow occurs */

			/* distance overflow occurred, so break out early */
			distance_overflow = true;
			break;
		}

		floors_to_visit.pop();
	}

	if (!distance_overflow)
	{
		/* begin printing out distance traveled, and floors */
		cout << to_string(my_elevator.get_travel_time());

/* for graceful, need to check if initial input was correct */
#ifdef GRACEFUL_INPUT_HANDLING
		if (initial_args_correct)
		{
			for (int i = 1; i < argc; i++)
			{
				string s(argv[i]);
				cout << "," + s;
			}
		}
		else
		{
			cout << " " + new_input;
		}
/* without graceful, initial input is correct by this point */
#else
		for (int i = 1; i < argc; i++)
		{
			string s(argv[i]);
			cout << "," + s;
		}
#endif

		cout << endl;
	}
	else
	{
		cout << "distance overflow occurred. Terminating program early" << endl;
		return -1;
	}

	return 0;
}
