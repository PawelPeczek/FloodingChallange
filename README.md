# FLOODING


There is a set of water containers (which are flooding from the bottom) and an ammount of water. We need to find out how many of these containers are filled with water to the full.


## INPUT
First line of an input is a number (N) of containers.
The following N lines contain coordinates of two points in format: x1 y1 z1 x2 y2 z2. The points are opposite vertexes of cuboid that represents a container. We can assume x1 < x2 and y1 < y2 and z2 < z1.
The last line of input contains the ammount of water (query).

All coords are given in imaginary unit u and the ammount of water - in u^3. 
N is an integer from range 0 < N <= 10000
Coordinates are floating point numbers from range: -10000 <= x1, y1, z1, x2, y2, z2 <= 10000
The ammount of water is a floating point number from range 0 < query <= 10^12

## OUTPUT
The number of water container that are filled with water to the full and additionally - the information whether overall capacity of containers is overflowed.