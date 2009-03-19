/*
 * Darts playing model for CS181.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "darts.h"

/* Initialize the wedges and angles arrays */
int wedges[NUM_WEDGES] = WEDGES;

void init_board() {
  int i,j;

  for (i=0; i<NUM_WEDGES; i++) {
    j = wedges[i];
    angles[j] = i;
  }
}

/* Determine the raw score for a board location */

int location_to_score(location loc) {
  int result;

  switch (loc.ring) {
  case CENTER : result = 2.5 * NUM_WEDGES; break;
  case INNER_RING : result = 1.25 * NUM_WEDGES; break;
  case FIRST_PATCH : result = loc.wedge; break;
  case MIDDLE_RING : result = 3 * loc.wedge; break;
  case SECOND_PATCH : result = loc.wedge; break;
  case OUTER_RING : result = 2 * loc.wedge; break;
  default : result = 0;
  }

  return result;
}

/* Play a single game */

int play(void) {
  int raw_score, score, turns;
  location target, result;

  score = START_SCORE;
  turns = 0;

  target = start_game();

  do {
    /* printf("Current score: %d\n", score); */

    
    /* result = throw(target); */
    raw_score = location_to_score(result);
		
    /*
    printf("Target: wedge %d, ring %d\n", target.wedge, target.ring);
    printf("Result: wedge %d, ring %d\n", result.wedge, result.ring);
    printf("Score: %d%s\n\n", raw_score, raw_score>score ? " TOO HIGH!" : "");
    */

    if (raw_score <= score) {
      score -= raw_score;
    }
    if (score==0) break;
    result = get_target(score,result);
		turns++;	
  } while (1);

  /*  printf("WOOHOO!  It only took %d turns\n", turns); */

  end_game(turns);

  return turns;
}

/* Play n games and return the average score */

void test(int n) {
  int score, i;

  for (i=0,score=0;i<n;i++) {
    score += play();
  }
  
  printf("Average turns = %f\n", (float)score/(float)n);

}

/* Feel free to modify the main function to set up your experiments. */

int main(int argc, char **argv) {
  int i, a; /* a1, a2; */
  float f1, f2;
  location loc1,loc2;

  init_board();

  /* Initialize variables used in Q-learning algorithm */
  for (i = 0; i < START_SCORE; i++) {
    for (a = 0; a < NUM_WEDGES*NUM_REGIONS; a++) {
      Q[i][a] = 0;
    }
  }
  alpha = ALPHA;

  /* Set the random number generator to a particular seed to establish a particular
     throwing model, and then initialize the throwing model. */
  srand(time(0));
  init_thrower();
	startIteration();


	

  use_simple_thrower();

  /* Initialize the random number generator with a random seed */
  /* srand(time(0)); */

  test(10000);
}


