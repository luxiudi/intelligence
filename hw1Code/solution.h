#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* The number of regions on the dartboard */
#define NUM_REGIONS 7

/* State */
double current_state;
double next_state;

/* Q function */
double Q[START_SCORE][NUM_WEDGES*NUM_REGIONS];



/* Q-learning */

#define ALPHA 0.9;    /* initial learning rate */
double Qmax, next_Qmax, prev_Qmax;
int abest;



/*calculate the transition probabilities from different states*/
double transition();



/* Miscellaneous functions */

/* max function */
static inline double max(double a, double b)
{
    return a > b ? a : b;
}
