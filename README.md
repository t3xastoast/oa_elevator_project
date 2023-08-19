# Outside Analytics Elevator Project

This program will simulate an elevator by accepting the floors to visit as input, and outputing the travel time followed by all floors visited.

Several key assumptions were made during implementation:

1. This program defines the valid range for a floor as [0, INT_MAX].

3. Because user input does not specify the tallest floor in this
theoretical building, it's assumed the tallest valid floor specified is
no larger than the tallest floor in the building.

4. The following information is assumed to be static during program execution:
	a. The total number of floors in the building (per assumption 2,
	will be unknown to this program/doesn't matter)
	b. The number of destination floors

5. All floors in the cmd line args are desired to be visited in
in the order specified

6. Travel time is defined as time elapsed while the elevator is moving.
It does NOT include time elapsed while the elevator is stationary. 
Additionally, travel time between any 2 adjacent floors is assumed 
to be constant (10)

There are 2 ways to build this project with the Makefile:
1. make elevator
2. make elevator graceful=1

I have also uploaded the binaries in case there are unexpected build issues observed (elevator and elevator_graceful)

"make elevator" means code will be compiled such that user input
will be accepted as is, and upon detection of badinput (eg -3, INT_MAX+1, asdf)
the program will terminate immediately. It will also provide a reason
why the input (the first bad input detected) isn't correct

"make elevator graceful=1" means code will be compiled that more
gracefully handles bad program inputs. Ie, user will be given 
as many attempts as needed to correct their input

Here's a list of nice-to-have's that I opted not to implement:
* Enhanced user input correction for graceful=1 (ie, asking for confirmation that the corrected input is indeed correct)
* Script for validation of overflow protection enforced on distance travelled
