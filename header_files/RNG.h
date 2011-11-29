/*
 * Random.h
 *
 *  Created on: Feb 20, 2010
 *      Author: hartley
 */

#pragma once
#ifndef RNG_H_
#define RNG_H_

class RNG {
public:
	RNG();
	virtual ~RNG();
	int next();
	int next(int);
	int next(int, int);
};

#endif /* RANDOM_H_ */