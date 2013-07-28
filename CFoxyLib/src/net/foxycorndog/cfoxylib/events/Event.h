#ifndef EVENT_H
#define EVENT_H

#include "CFL.h"

/**
 * Base class for all of the other Events. Holds the information for the
 * time that the Event happened.
 * 
 * @author	Braden Steffaniak
 * @since	Mar 10, 2013 at 3:28:46 PM
 * @since	v0.2
 * @version	Apr 26, 2013 at 10:32:46 PM
 * @version	v0.2
 */
class Event
{
private:
	long	when;

public:
	Event();

	long	getWhen();
};

#endif