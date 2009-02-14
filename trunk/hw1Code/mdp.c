#include "darts.h"

/* Components of a darts player. */

/* 
 * Modify the following functions to produce a player.
 * The default player aims for the maximum score, unless the
 * current score is less than the number of wedges, in which
 * case it aims for the exact score it needs.  You can use this
 * player as a baseline for comparison.
 */

location start_game() {
  location result;
  
  result.wedge = NUM_WEDGES;
  result.ring = MIDDLE_RING;

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

  return result;
}

void end_game(int turns) {

}
