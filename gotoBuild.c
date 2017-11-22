/*
*Used for creation of the goto pattern trie for the AC algorithm.
*
*Martin J Smith
*/

#include "ac.h"


/*
*Build the gotoGraph for the AHO CORASICK algorithm
*/
void AhoBuildGoto(AhoVars *globals, char **patterns, int patNum){

//set the root position of the pattern trie, fails to itself and is the empty char, 0th value node
globals->Machine = malloc(sizeof(State));
globals->Machine->failState = malloc(sizeof(State));
globals->Machine->failState = globals->Machine;
globals->Machine->stateChar = ' ';
globals->Machine->ID = 0;

//null out the array
int f;
for(f = 0; f < OUTSIZE; f++){
  globals->Machine->output[f] = '\0'; 
  }
printf("THIS IS ROOT: '%c'\n", globals->Machine->stateChar);


//encode the goto trie, character by character from the list of patterns
for(int i = 0; i < patNum; i++){

  int tempCt = 0;
  int tempCH = ' ';
  
  //count chars
  while(tempCH != '\n'){
    tempCH = patterns[i][tempCt];
    tempCt++;
    }
    //-1 to not consider newline
    encode(globals, patterns[i], tempCt-1);
  }

}


/*
*Encode the given pattern structure into the trie.
*/
void encode(AhoVars *globals, char *pattern, int count){

//Set Curr to root node
globals->Current = globals->Machine;
printf("Inserting --- %s --- Currently at '%c'%d ------\n", pattern, globals->Current->stateChar, globals->Current->ID);

//Counting variables
int q, i = 0;

//need to go through known states, adding unknown. goto returns 0 when state is present
while(AhoGoTo(globals, globals->Current, pattern[q]) == 0){
  q++;
  }

printf("while loop got to '%c'%d : '%c' was not found in the trie\n", globals->Current->stateChar, globals->Current->ID, pattern[q]);
printf("-----------------------------Start Adding States for current Pattern to Trie-----------------------------\n");
for(i = q; i < count; i++){
  globals->IDcounter++;
  //because value starts at 0 when there is one present;

printf("current state before 'add' block is: '%c'%d \n", globals->Current->stateChar, globals->Current->ID);
  
  //ifelse block responsible for filtering through the sibling states or adding a child
  if(globals->Current->childState == NULL){ 
    globals->Current->childState = malloc(sizeof(State));
printf("Parent state before adding new state is: '%c'%d \n", globals->Current->stateChar, globals->Current->ID);
    globals->Current = globals->Current->childState; //current is now the child
    }else{
    globals->Current = globals->Current->childState;
    while(globals->Current->siblingState != NULL){
	globals->Current = globals->Current->siblingState;
      }
printf("Sibling state before adding new state is: '%c'%d \n", globals->Current->stateChar, globals->Current->ID);
    globals->Current->siblingState = malloc(sizeof(State));
    globals->Current = globals->Current->siblingState;
    }

  //null out the array
  int q;
  for(q = 0; q < OUTSIZE; q++){
    globals->Current->output[q] = '\0';
    }

  globals->Current->stateChar = pattern[i];
  globals->Current->ID = globals->IDcounter;
  globals->Current->outputCount = 0;
printf("Inserted '%c'%d into the trie with output value '%s'\n", globals->Current->stateChar, globals->Current->ID, globals->Current->output);
  }

  globals->Current->outputCount = count;
  for(i = 0; i < count; i++){
    globals->Current->output[i] = pattern[i];
    }
printf("luna '%c'%d is '%p' refers to output string '%s'----\n", globals->Current->stateChar, globals->Current->ID, globals->Current, globals->Current->output);

printf("I noted ::: '%s' as an output value for '%c'%d because I finished adding the states!\n", globals->Current->output, globals->Current->stateChar, globals->Current->ID);
printf("-----------------------------Stop Adding States for current Pattern to Trie-----------------------------\n");


}
