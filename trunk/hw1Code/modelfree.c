/*
 * Q learning
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "darts.h"
#include "solution.h"

location start_game() {
  location result;
  
  result.wedge = NUM_WEDGES;
  result.ring = MIDDLE_RING;

  return result;
}

location get_target(int score, location prev_loc)
{
    int a, j, r;
    double alpha;
    location aim, result;
    div_t ans;

    prev_Qmax = Qmax;
    for (a = 0; a < NUM_WEDGES*NUM_REGIONS; a++) {
        if (Q[score][a] > Qmax) {
            abest = a + 1;
            Qmax = Q[score][a];
        }
    }
    if (Qmax == prev_Qmax) {
        abest = (rand() % (NUM_WEDGES*NUM_REGIONS)) + 1;
    }
    ans = div(abest,NUM_REGIONS);
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
    for (a = 0; a < NUM_WEDGES*NUM_REGIONS; a++) {
        if (Q[j][a] > next_Qmax) {
            next_Qmax = Q[j][a];
        }
    }
    alpha = ALPHA;
    Q[score][abest] = (1 - alpha) * Q[score][abest] + alpha * (r + next_Qmax);
    score = j;

    return result;
}

void end_game(int turns) {

}
