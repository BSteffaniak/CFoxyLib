#include "CFL.h"

/**
 * Create an Event and save the time in which it was created.
 */
Event::Event()
{
	when = Time::currentTimeMillis();
}

/**
 * Get when the event occurred.
 * 
 * @return When the event occurred.
 */
long Event::getWhen()
{
	return when;
}