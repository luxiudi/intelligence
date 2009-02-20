/*
 * Q learning
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "darts.h"
#include "solution.h"

location start_game() {
    int i, a;
  location result;
  
  result.wedge = NUM_WEDGES;
  result.ring = MIDDLE_RING;

  /* Initialize variables used in Q-learning algorithm */
  for (i = 0; i < START_SCORE; i++) {
      for (a = 0; a < NUM_WEDGES*NUM_REGIONS; a++) {
          Q[i][a] = 0;
      }
  }
  Qmax = 0;
  abest = 0;
  next_Qmax = 0;
  prev_Qmax = 0;

  return result;
}

location get_target(int score, location prev_loc)
{
    int a, j, r;
    location aim, result;
    div_t ans;

    prev_Qmax = Qmax;
    for (a = 1; a <= NUM_WEDGES*NUM_REGIONS; a++) {
        if (Q[score][a] > Qmax) {
            abest = a;
            Qmax = Q[score][a];
        }
    }
    if (Qmax == prev_Qmax) {
        abest = (rand() % (NUM_WEDGES*NUM_REGIONS)) + 1;
    }
    ans = div(a,NUM_REGIONS);
    if (ans.rem == 0) {
        aim.ring = (ring)NUM_REGIONS;
    } else {
        aim.ring = (ring)ans.rem;
    }
    aim.wedge = ans.quot + 1;
    result = throw(aim);
    j = score - location_to_score(result);
    r = (j == 0) ? 1 : 0;
    for (a = 0; a < NUM_WEDGES*NUM_REGIONS; a++) {
        if (Q[j][a] > next_Qmax) {
            next_Qmax = Q[j][a];
        }
    }
    Q[score][abest] = (1 - ALPHA) * Q[score][abest] + ALPHA * (r + next_Qmax);
    score = j;

    return result;
}

void end_game(int turns) {

}
