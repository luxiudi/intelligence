/*
 * Q learning
 */

#include <stdio.h>
#include <stdlib.h>
#include "darts.h"
#include "solution.h"

location start_game() {
  location result;
  
  result.wedge = NUM_WEDGES;
  result.ring = MIDDLE_RING;

  /* Initialize variables used in Q-learning algorithm */
  for (int i = 0; i < START_SCORE; i++) {
      for (int a = 0; a < NUM_WEDGES*NUM_REGIONS; a++) {
          Q[i][a] = 0;
      }
  }
  Qmax = 0;
  abest = 0;
  next_Qmax = 0;

  return result;
}

location get_target(int score, location prev_loc) {
    location result;

    if (score>NUM_WEDGES) {
        result.wedge = NUM_WEDGES;
        result.ring = MIDDLE_RING;
    } else {
        result.wedge = score;
        result.ring = SECOND_PATCH;
    }



    for (int a = 0; a < NUM_WEDGES*NUM_REGIONS; a++) {
        if (Q[i][a] > Qmax) {
            abest = a;
            Qmax = Q[i][a];
        }
    }
    location aim;
    div_t ans = div(a,NUM_REGIONS);
    if (ans.rem == 0) {
        aim.ring = (ring)NUM_REGIONS;
    } else {
        aim.ring = (ring)ans.rem;
    }
    aim.wedge = ans.quot + 1;
    location result = throw(aim);
    int j = i - location_to_score(result);
    int r = j == 0 ? 1 : 0;
    for (int a = 0; a < NUM_WEDGES*NUM_REGIONS; a++) {
        next_Qmax = max(Q[j][a], nextQmax);
    }
    Q[i][a] = (1 - alpha) * Q[i][a] + alpha * (r + next_Qmax);
    i = j;
    alpha -= alpha0 * 1/1e6;

    return result;
}

void end_game(int turns) {

}
