#include "RNG.h"
#include <cstdlib>
#include <ctime>

RNG::RNG() {
	// Seed the random number generator
	srand(time(0));
}

RNG::~RNG() {
}

/*
 * Return the next random integer
 */
int RNG::next()
{
	return rand();
}

/*
 * Return the next random integer greater than or
 * equal to 0 and smaller than the upper limit
 */
int RNG::next(int upperLimit)
{
	return rand() % upperLimit;
}

/*
 * Return the next random integer greater than or equal to the
 * lower limit and less than the upper limit
 */
int RNG::next(int lowerLimit, int upperLimit)
{
	return (rand() % (upperLimit - lowerLimit)) + lowerLimit;
}