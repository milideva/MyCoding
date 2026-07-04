/**
 * Problem: Clock Angle Problem
 * Given a time in hh:mm format, find the smaller angle between the hour and 
 * minute hands of a clock.
 * 
 * Strategy: Coordinate-based angle calculation
 * - Minute hand moves 6 degrees per minute (360/60).
 * - Hour hand moves 30 degrees per hour (360/12) + 0.5 degrees per minute (30/60).
 * - Calculate absolute difference and take the minimum of (diff, 360-diff).
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Calculates the smaller angle between hour and minute hands.
 */
double getClockAngle(int hr, int min) {
    // Basic validation
    if (hr < 0 || min < 0 || hr > 12 || min > 60) return -1;
    if (hr == 12) hr = 0;
    if (min == 60) min = 0;

    // Minute hand angle: 6 degrees per minute
    double minAngle = min * 6.0;

    // Hour hand angle: 30 degrees per hour + 0.5 degrees per minute
    double hrAngle = hr * 30.0 + min * 0.5;

    double angle = fabs(hrAngle - minAngle);

    // Return the smaller angle
    if (angle > 180.0) {
        angle = 360.0 - angle;
    }

    return angle;
}

int main() {
    int hours[] = {12, 3, 1, 11};
    int minutes[] = {30, 30, 10, 10};
    int size = sizeof(hours) / sizeof(hours[0]);

    for (int i = 0; i < size; i++) {
        printf("Time %02d:%02d -> Angle: %.1f degrees\n", 
               hours[i], minutes[i], getClockAngle(hours[i], minutes[i]));
    }

    return 0;
}
