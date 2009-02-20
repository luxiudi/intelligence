/*
 * Q learning
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "darts.h"

location start_game() {
  location result;
  
  result.wedge = NUM_WEDGES;
  result.ring = MIDDLE_RING;

  return result;
}

location get_target(int score, location prev_loc)
{
  int a, j, r, best, abest;
    double Qmax, next_Qmax;
    location aim, result;
    div_t ans;

    printf("wedges*regions = %d\n",NUM_WEDGES*NUM_REGIONS);

    abest = (rand() % (NUM_WEDGES*NUM_REGIONS));
    best = 0;
    Qmax = Q[score][0];
    for (a = 1; a < NUM_WEDGES*NUM_REGIONS; a++) {
        if (Q[score][a] > Qmax) {
            abest = a;
            Qmax = Q[score][a];
	    best = 1;
        }
    }
    ans = div(abest+1,NUM_REGIONS);    /* a+1 since matrix indeces are all 
					  positive */
    if (ans.rem == 0) {
        aim.ring = (ring)NUM_REGIONS;
    } else {
        aim.ring = (ring)ans.rem;
    }
    aim.wedge = ans.quot + 1;
    
    result = throw(aim);
    j = score - location_to_score(result);
    if (j < 0) {
      j = score;
    }
    r = (j == 0) ? 1 : 0;
    next_Qmax = Q[j][0];
    for (a = 1; a < NUM_WEDGES*NUM_REGIONS; a++) {
        if (Q[j][a] > next_Qmax) {
            next_Qmax = Q[j][a];
        }
    }
    
    Q[score][abest] = (1 - alpha) * Q[score][abest] + alpha * (r + next_Qmax);
    
    score = j;

    return result;
}

void end_game(int turns) {
  alpha -= 0.001;
  if (alpha < 0) {
    alpha = 0;
  }
}
