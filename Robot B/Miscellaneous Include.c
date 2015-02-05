// Returns the greater of two numbers
float max(float Number1, float Number2) {
	if (Number1 > Number2) {
		return Number1;
	}
	return Number2;
}

// Returns the lesser of two numbers
float min(float Number1, float Number2) {
	if (Number1 < Number2) {
		return Number1;
	}
	return Number2;
}

// Returns either the lower or upper bound, if the given number exceeds those bounds,
// or the number itself
float bounds(float Minimum, float Maximum, float Number) {
	return min(max(Minimum, Number), Maximum);
}

// Rounds a number to an optionally specified number of places
float roundTo(float Number, int Places = 0) {
	return floor(Number * (10 ^ Places) + 0.5) / (10 ^ Places);
}

// Waits the specified number of milliseconds, regardless of the implementation restrictions
// (32.767 seconds for wait1Msec, and 327.67 seconds for wait10Msec)
void waitMsec(float Time) {
	// Keep track of the milliseconds remaining
	float Remaining = Time;
	// Repeat until theres no remaining milliseconds
	while (Remaining > 0) {
		// Calculate the time that will be waited this iteration
		// The time cannot be more than 32767 ms per function call
		int WaitTime = min(32767, Remaining);
		// Subtract the wait time from the remaining time
		Remaining -= WaitTime;
		// Wait
		wait1Msec(WaitTime);
	}
}

// Wait for the specified number of seconds, regardless of the implementation restrictions
// (32.767 seconds for wait1Msec, and 327.67 seconds for wait10Msec)
void waitSec(float Time) {
	waitMsec(round(Time * 1000));
}
