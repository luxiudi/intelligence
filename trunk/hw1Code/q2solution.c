#include "darts.h"
#include <stdio.h>
#include <string.h>

int angles[NUM_WEDGES + 1] = WEDGES;
int wedges[NUM_WEDGES] = WEDGES;
location possible_actions[NUM_WEDGES*7];
location best_action[START_SCORE][START_SCORE];
double v[START_SCORE][START_SCORE];

void startIteration();
void init_actions();
double sum_expected_reward(location a, int k, int current_score);


int main() {
  	
	init_board();
	init_actions();
	
	printf("\n");

  int x;
/* 	for(x = 0; x<NUM_WEDGES*7; x++){ */
/* 		printf("Action #: %d; ", x); */
/*     printf("Wedge #: %d; ", possible_actions[x].wedge); */
/* 		printf("Ring #: %d\n", possible_actions[x].ring); */
/* 		//printf("\n"); */
/* 	} */


	startIteration();


	//int x;
	int y;
	for( x = 0; x<START_SCORE; x++)
	{

		for( y = 0; y<START_SCORE; y++){

			printf("%f ", v[x][y]);

		}
		printf("\n");
	}

	
	//printf("best action: wedge %d, ring %d\n", best_action[1][3].wedge, best_action[8][8].ring );
	int w;
	for( w = 0; w<START_SCORE; w++){

			int num = 87;
			printf("The best move at is: wedge: %d ring:  %d\n", best_action[w][num].wedge, best_action[w][num].ring);

	}
	

	location b;
	b.ring = 3;
	b.wedge = 1;

	double s = sum_expected_reward(b, 1, 3);	
	printf("Pay off: %f\n",s);
	double d = transition(b, 3, 0);	
	printf("SCORE: %f\n",d);	
	
	return 1;
}



void init_board() {
  int i,j;

  
  for (i=0; i<NUM_WEDGES; i++) {
    j = wedges[i];
    angles[j] = i;
    
  }

  int w;
  for( w = 1; w<NUM_WEDGES+1; w++){

	printf("%d ", angles[w]);
  }	
}

void init_actions(){
	int x;
	int y;
	int z = 0;
	for( x = 0; x< NUM_WEDGES; x++){
		for( y = 0; y<7; y++)
		{
			possible_actions[z].wedge = x+1;
			possible_actions[z].ring = y;
 			z++;
		}
	}
}

void startIteration(){

  printf("START ITERATION\n");
	int k = 0;
	int horizon = START_SCORE;
	int num_states = START_SCORE;
	
	memset(&v, 0, horizon*num_states*sizeof(double));
	memset(&best_action, 0, horizon*num_states*sizeof(location));
	int t = 0;
	v[0][0] = 1.0;

	//for each k step to go
	for( k = 1; k<horizon; k++){
		int i;
		v[k][0] = 1;		
		//for each possible state i 
		for( i = 1; i< num_states; i++){
			
			//foreach action
			int n = 0;
			for( n= 0; n < NUM_WEDGES*7; n++){
				location a = possible_actions[n];
				double temp =  sum_expected_reward(a, k, i);
								
				//double temp;
				//foreach possible result for the action
				if( v[k][i] < temp ){

					
					v[k][i] = temp;
					best_action[k][i] = a;
					if(best_action[k][i].wedge == 3 && best_action[k][i].ring == 3)
						printf("BEST ACTION BEING INSTALLED: k %d, i %d\n", k, i)	;
				}
				
				//printf("Iteration #: %d\n", t);



			if( temp > 0.82 && temp < 0.828 && i == 9){
				printf("value %f\n", temp);	
				printf("Action #: %d\n", n);
    		printf("Wedge #: %d\n", possible_actions[n].wedge);
				printf("Ring #: %d\n", possible_actions[n].ring);
				printf("\n");}
				//printf("value %f\n", temp);	
				t++;
			}
			//printf("\n%f\n", v[k][i]);
		}

	}

}

void getpossible_results(int current_state, location a){


	int w2 = a.wedge;
	int w = angles[w2];
	//printf("\nGetting possible wedges\n");	

	//printf("\nThe angle of the input wedge: %d\n", w);	

	int w1 = wedges[(w-1 == -1) ? NUM_WEDGES -1 : w-1];
	int w0 = wedges[(w-2 == -1) ? NUM_WEDGES -1 : w-2];
	int w3 = wedges[(w+1)%NUM_WEDGES];
	int w4 = wedges[(w+2)%NUM_WEDGES];
	
	int wedge_values[5] = {w0, w1, w2, w3, w4};



}

double sum_expected_reward(location a, int k, int current_score){

	int w2 = a.wedge;
	int w = angles[w2];
	//printf("\nGetting possible wedges\n");	

	//printf("\nThe angle of the input wedge: %d\n", w);	

	int w1 = wedges[(w-1 == -1) ? NUM_WEDGES -1 : w-1];
	int w0 = wedges[(w-2 == -1) ? NUM_WEDGES -1 : w-2];
	int w3 = wedges[(w+1)%NUM_WEDGES];
	int w4 = wedges[(w+2)%NUM_WEDGES];
	
	int wedge_values[5] = {w0, w1, w2, w3, w4};

/* 		int z; */
/* 	for(z=0; z<5; z++){ */
/* 		 */
/* 		printf("The wedge value: %d\n", wedge_values[z]);	 */
/* 	}  */



//printf(" action- wedge: %d ring: %d ;\n", a.wedge, a.ring);	


	int x;
	double expected_score = 0;
	int passed_states[START_SCORE];
	memset(&passed_states, 0, START_SCORE*sizeof(int));
	//foreach possible end state (5 wedges x possible rings)




	for(x = 0; x< 5; x++){

		int center = current_score < 50 ? current_score: current_score - 50;
		int inner_ring = current_score <25 ? current_score : current_score - 25;	
		int first_patch = current_score < wedge_values[x]? current_score : current_score - wedge_values[x];
		int middle_ring = current_score < 3*wedge_values[x]? current_score : current_score - 3*wedge_values[x];
		int second_patch = current_score < wedge_values[x]? current_score : current_score - wedge_values[x];;
		int outer_ring = current_score < 2*wedge_values[x]? current_score : current_score - 2*wedge_values[x];

		//condition ? value if true : value if false 
			
		//int result_states[5]; 
		int result_states[5] = {0, 0, 0, 0 , 0};
			
		switch(a.ring){

				case CENTER :					
					  result_states[0] = center;			
						result_states[1] = inner_ring;
						break;
				case INNER_RING :
						result_states[0] = center;			
						result_states[1] = inner_ring;
						result_states[2] = first_patch;
						break;
				case FIRST_PATCH:
						result_states[0] = center;			
						result_states[1] = inner_ring;
						result_states[2] = first_patch;
						result_states[3] = middle_ring;						
						break;
				case MIDDLE_RING:
						result_states[0] = outer_ring;			
						result_states[1] = inner_ring;
						result_states[2] = first_patch;
						result_states[3] = middle_ring;	
						
						break;
				case SECOND_PATCH:
						result_states[0] = outer_ring;			
						result_states[2] = second_patch;
						result_states[3] = middle_ring;	
						break;
				case OUTER_RING:
						result_states[0] = outer_ring;			
						result_states[2] = second_patch;
						result_states[3] = middle_ring;	
						break;
		}

		int y;
		int has_hit_zero = 0;
		for (y= 0; y< 5;y++){

			if(passed_states[result_states[y]] == 1)
					continue;
			else{

					passed_states[result_states[y]] = 1;
			}
			

			expected_score = expected_score + v[k-1][result_states[y]]*transition(a, current_score, result_states[y]);
/* 			printf("expected reward: %f; ", expected_score); */
/* 			printf("current score %d; ", current_score);			 */
/* 			printf("result score %d; ", result_states[y]);	 */
/* 			printf("k-1 v: %f; ", v[k-1][result_states[y]]); */
/* 			printf(" (x value %d, y value %d); ", wedge_values[x], y);	 */
/* 			printf(" action- wedge: %d ring: %d ;\n", a.wedge, a.ring); */
/* 			printf("probabilites %f; \n", transition(a, current_score, result_states[y]));	 */
			
		
		}

	}
	//printf("%f\n", expected_reward);
	return expected_score;
}





double transition(location a, int current_state, int result_state){
 //check if going from currentScore to finalScore is a valid move given the action.

	
	
 // CENTER,       /* double bullseye (center of the board) worth 2.5 * NUM_WEDGES     */
 // INNER_RING,   /* inner ring                            worth 1.25 * NUM_WEDGES    */
 // FIRST_PATCH,  /* area between inner and middle rings   worth the wedge number     */
 // MIDDLE_RING,  /* middle ring                           worth 3 * the wedge number */
 // SECOND_PATCH, /* area between middle and outer rings   worth the wedge number     */
 // OUTER_RING,   /* outer ring                            worth 2 * the wedge number */
 // MISS          /* off the board                         worth nothing              */


	//condition ? value if true : value if false 
	int w2 = a.wedge;
	int r = a.ring;
	//current_state = 49;
	//int points_needed = 16;

	int points_needed = current_state - result_state;

	

	int w = angles[w2];
	//printf("\nThe angle of the input wedge: %d\n", w);	

	int w1 = wedges[(w-1 == -1) ? NUM_WEDGES -1 : w-1];
	int w0 = wedges[(w-2 == -1) ? NUM_WEDGES -1 : w-2];
	int w3 = wedges[(w+1)%NUM_WEDGES];
	int w4 = wedges[(w+2)%NUM_WEDGES];
	
	int wedge_values[5] = {w0, w1, w2, w3, w4};
	double wedge_probabilities[5] ={0.1, 0.2, 0.4, 0.2, 0.1};
	
/* 	int z; */
/* 	for(z=0; z<5; z++){ */
/* 		 */
/* 		printf("The wedge value: %d\n", wedge_values[z]);	 */
/* 	}  */
	
	
	
	double prob = 0;
	int x = 0;

	for(x = 0; x< 5; x++){

		int center = 50;
		int inner_ring = 25;	
		int first_patch = wedge_values[x];
		int middle_ring = 3*wedge_values[x];;
		int second_patch = wedge_values[x];;
		int outer_ring = 2*wedge_values[x];;
		int miss = 0;
	


	  	switch( r )
    	  	{
        		case CENTER : 
				//printf( "CENTER\n" );
				if(points_needed == center || (points_needed == 0 && current_state<center)){
					//printf("CENTER OF CENTER\n");
					prob = prob + 0.4;}
				if(points_needed == inner_ring || (points_needed == 0 && current_state<inner_ring)){
					//printf("CENTER OF CENTER\n");					
					prob = prob + 0.4;			
				}
				if((points_needed <= NUM_WEDGES && points_needed > 0) ){
					//printf("CENTER OF CENTER\n");
					prob = prob + (double)1/NUM_WEDGES*.2;
				}				
				return prob;

			case INNER_RING : 
				//printf( "INNER_RING\n" );
				if(points_needed == inner_ring || (points_needed == 0 && current_state<inner_ring))
					prob = prob + 0.4;
				if(points_needed == center|| (points_needed == 0 && current_state<center))
					prob = prob + 0.2;
				if( points_needed == inner_ring || (points_needed == 0 && current_state < inner_ring))
					prob = prob + 0.1;			
				if((points_needed <= NUM_WEDGES && points_needed >= 0))
					prob = prob + (double)1/NUM_WEDGES *.2;	
				if( (points_needed%3 == 0 && points_needed <= 60))
					prob = prob + (double)1/NUM_WEDGES*.1;			
				return prob; 
			case FIRST_PATCH : 
				//printf( "FIRST_PATCH\n" );
				if(points_needed == first_patch || (points_needed == 0 && current_state<first_patch))
					prob = prob + 0.4*wedge_probabilities[x];
				if(points_needed == middle_ring || (points_needed == 0 && current_state<middle_ring))
					prob = prob + 0.2*wedge_probabilities[x];
				if(points_needed == second_patch || (points_needed == 0 && current_state<second_patch))
					prob = prob + 0.1*wedge_probabilities[x];
				if(points_needed == inner_ring || (points_needed == 0 && current_state<inner_ring))
					prob = prob + 0.2*wedge_probabilities[x];
				if(points_needed == center || (points_needed == 0 && current_state<center) ) 
					prob = prob + 0.1*wedge_probabilities[x];
								
				break;
			case MIDDLE_RING :
				//printf( "MIDDLE_RING\n" );
				if(points_needed == middle_ring || (points_needed == 0 && current_state<middle_ring))
					prob = prob + 0.4*wedge_probabilities[x];
				if(points_needed == first_patch || (points_needed == 0 && current_state<first_patch))
					prob = prob + 0.2*wedge_probabilities[x];
				if(points_needed == inner_ring || (points_needed == 0 && current_state<inner_ring))
					prob = prob + 0.1*wedge_probabilities[x];				
				if(points_needed == second_patch || (points_needed == 0 && current_state<second_patch))
					prob = prob + 0.2*wedge_probabilities[x];				
				if(points_needed == outer_ring || (points_needed == 0 && current_state<outer_ring))
					prob = prob + 0.1*wedge_probabilities[x];
								
				break;

			case SECOND_PATCH :
				//printf( "SECOND_PATCH\n" );
				if(points_needed == second_patch || (points_needed == 0 && current_state<second_patch))
					prob = prob + 0.4*wedge_probabilities[x];
				if(points_needed == middle_ring || (points_needed == 0 && current_state<middle_ring))
					prob = prob + 0.2*wedge_probabilities[x];
				if(points_needed == first_patch || (points_needed == 0 && current_state<first_patch))
					prob = prob + 0.1*wedge_probabilities[x];				
				if(points_needed == miss)
					prob = prob + 0.1*wedge_probabilities[x];				
				if(points_needed == outer_ring || (points_needed == 0 && current_state<outer_ring))
					prob = prob + 0.2*wedge_probabilities[x];
								
				break;

			case OUTER_RING :
				//printf( "OUTER_RING\n" );
				if(points_needed == outer_ring || (points_needed == 0 && current_state<outer_ring)){
					//printf("OUTER OF OUTER\n");
					prob = prob + 0.4*wedge_probabilities[x];}
				if(points_needed == second_patch || (points_needed == 0 && current_state<second_patch)){
					//printf("SECOND OF OUTER\n");
					prob = prob + 0.2*wedge_probabilities[x];}
				if(points_needed == middle_ring || (points_needed == 0 && current_state< middle_ring))
					prob = prob + 0.1*wedge_probabilities[x];				
				if(points_needed == miss )
					prob = prob + 0.3*wedge_probabilities[x];				
								
				break;
     		}
		
	}
	//printf("%f\n", prob);
	return prob;
}


