//
//  FoxyTime.cpp
//  CFoxyLib
//
//  Created by Braden Steffaniak on 7/26/13.
//  Copyright (c) 2013 Braden Steffaniak. All rights reserved.
//

#include "CFL.h"

#include <chrono>

namespace sc = std::chrono;

long FoxyTime::currentTimeMillis()
{
	auto time = sc::system_clock::now(); // get the current time
	
	auto since_epoch = time.time_since_epoch(); // get the duration since epoch
	
	// I don't know what system_clock returns
	// I think it's uint64_t nanoseconds since epoch
	// Either way this duration_cast will do the right thing
	auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);
	
	long now = (long)millis.count(); // just like java (new Date()).getTime();
	
	return now;
}