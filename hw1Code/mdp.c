#include "darts.h"
#include <stdio.h>

/* Components of a darts player. */

/* 
 * Modify the following functions to produce a player.
 * The default player aims for the maximum score, unless the
 * current score is less than the number of wedges, in which
 * case it aims for the exact score it needs.  You can use this
 * player as a baseline for comparison.
 */

//keep track of how many throws we've done
int count = 0;

location start_game() {
  location result;
  
  result.wedge = NUM_WEDGES;
  result.ring = MIDDLE_RING;
	//printf("starting game\n");
	
  return result;
}

location get_target(int score, location prev_loc) {
  location result;

	//printf("calling get target %d th time with score equal to %d\n", count, score);
	//printf("going to throw: ring %d, wedge %d\n", best_policy[score].ring, best_policy[score].wedge);
	count++;
	result = throw(best_policy[score]);
	//printf("the result hit value %d \n", location_to_score(result));

	//printf("total number of throws %d\n", count);	
  return result;
}

void end_game(int turns) {

}
