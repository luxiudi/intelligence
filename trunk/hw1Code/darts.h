/*
 * CS181 Darts game
 */

/* 
 * Parameters of a dartboard.
 * NUM_WEDGES is simply the number of different wedges around the board.
 * WEDGES is the list of wedges, in counter-clockwise order, beginning
 * with the rightmost edge (angle 0).
 */

/* The standard dartboard */
#define NUM_WEDGES 20
#define WEDGES { 6, 13, 4, 18, 1, 20, 5, 12, 9, 14, 11, 8, 16, 7, 19, 3, 17, 2, 15, 10 }

/* A much smaller dartboard 
#define NUM_WEDGES 4
#define WEDGES { 1, 4, 2, 3 }
*/

/* The number of regions on the dartboard */
#define NUM_REGIONS 7

/* 
 * Two arrays for describing a dartboard.
 * The wedges array converts a position around the dartboard into a wedge number.
 * Positions are numbered from 0, starting at the rightmost position, and
 * move counter-clockwise.  Thus, in the standard dartboard, 6 is in position 0,
 * 13 is in position 1 and so on.
 * The angles array is the inverse of the wedges array.  For each wedge number, 
 * from 1 to NUM_WEDGES, it gives the angle of the wedge.  The angle needs to be scaled 
 * by 2 Pi / NUM_WEDGES to convert into radians.
 *
 * The contents of the wedges array is described in the WEDGES constant.
 *
 * init_board should be called at the beginning of the program to initialize
 * the angles array.
 */
int wedges[NUM_WEDGES];
int angles[NUM_WEDGES + 1];

void init_board();

/*
 * The initial score of players in the game.
 */

/* The standard initial score */
#define START_SCORE 301

/* Initial score for the small game 
#define START_SCORE 9
*/

/* 
 * A location on a dartboard consists of the wedge number, and a ring.
 * Wedges are numbered from 1 to 20. Rings are as follows.
 */

typedef enum ring { 
  CENTER,       /* double bullseye (center of the board) worth 2.5 * NUM_WEDGES     */
  INNER_RING,   /* inner ring                            worth 1.25 * NUM_WEDGES    */
  FIRST_PATCH,  /* area between inner and middle rings   worth the wedge number     */
  MIDDLE_RING,  /* middle ring                           worth 3 * the wedge number */
  SECOND_PATCH, /* area between middle and outer rings   worth the wedge number     */
  OUTER_RING,   /* outer ring                            worth 2 * the wedge number */
  MISS          /* off the board                         worth nothing              */
} ring;

typedef struct {
  ring ring;
  int wedge;
} location;



/* State */
double current_state;
double next_state;

/* Q function */
double Q[START_SCORE][NUM_WEDGES*NUM_REGIONS];

/* Q-learning */

#define ALPHA 1;    /* initial learning rate */
double alpha;    /* learning rate */



/* 
 * A throw takes as argument a target location (the aim), 
 * and produces another location as a result.
 * The result is produced stochastically using the throwing model.
 */

location throw(location target);
  
/*
 * Initialize a throwing model.  The model will be used for all
 * subsequent throws, until initialized again.  The throwing model
 * is randomly generated using the current random seed.
 */

void init_thrower();
 
/*
 * A simpler throwing model, more amenable to analysis, has been provided.
 * Call use_simple_thrower to start using the simpler throwing model.
 */

void use_simple_thrower();

/*
 * To implement your player, implement the following functions.
 */

/* Return the initial target to aim at */
location start_game(); 

/* Return the next target, given the current score and the location
   where the previous throw landed. */
location get_target(int current_score, location previous_loc);

/* Compile statistics for the end of a game.  
   It takes as argument the number of turns the game lasted.
   This function does not have to do anything. */
void end_game(int turns);

/*
 * The play function plays a single game.  
 * It resets the score to START_SCORE, and calls start_game to get a target.
 * It then throws at the target, and keeps track of the score.
 * It will keep calling get_target until the score reaches zero.
 * It will then call end_game to let you know the game has ended.
 * Returns the number of turns taken.
 */

int play(void);

/* Determine the raw score for hitting a location */

int location_to_score(location loc);



/*calculate the transition probabilities from different states*/
double transition();
