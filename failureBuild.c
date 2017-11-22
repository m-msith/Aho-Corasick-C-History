/*
*Used for the definition of the failstates for the AC pattern trie.
*
*Martin J Smith
*/

#include "ac.h"

//The queue of states used for the failureBuild
typedef struct QueueSt{

State *id;
struct QueueSt *nextQ;
}QueueSt;

//queue for building failures into trie
QueueSt *stateQueue;
QueueSt *endStQ;
QueueSt *curStQ;

void pushStQ(State *addState);
void popStQ();

/**
* Function used to set the failstate of the individual states in the pattern trie
*/
void AhoBuildFail(AhoVars *globals){

//Queue set up
stateQueue = malloc(sizeof(QueueSt *));
curStQ = malloc(sizeof(QueueSt *));
curStQ->nextQ = malloc(sizeof(QueueSt *));
endStQ = curStQ->nextQ;
stateQueue = curStQ;

//Set trie to first child
globals->Current = globals->Machine->childState;

//go through the first tier (position 1) of states, add them to queue

while(globals->Current != NULL){

  pushStQ(globals->Current);
  globals->Current->failState = globals->Machine;
  printf("current char: '%c' ~~~~ set to fail at: '%c'\n", globals->Current->stateChar, globals->Current->failState->stateChar);
  globals->Current = globals->Current->siblingState;
  }

//increment to the first nonnull
curStQ = curStQ->nextQ;
stateQueue = curStQ;

//While the queue is not empty - add fail states! this goes through the developed trie in its entirety
while(stateQueue->id != NULL){
  State *statiSt = curStQ->id; //holds popped queue state value
  globals->Current = statiSt;

  printf("Queue value that is popped - the root we are working with: '%c'%d\n", curStQ->id->stateChar, curStQ->id->ID);

  popStQ();

  //set the static state to the child state of the current root e.g. the nextState.
  State *statiStK = statiSt->childState;

  //fails through the trie from given point to start looking for proper fail trace
  while(statiStK != NULL){	
	pushStQ(statiStK);

	printf("	Adding this value to the queue: '%c'%d\n", statiStK->stateChar, statiStK->ID);	
	AhoFail(globals);

	//set the failstate for the current node
	while(AhoGoTo(globals, globals->Current, statiStK->stateChar) == 1){ //while can't proceed

	  if(globals->Current->stateChar == ' '){
	    break;
	    }
	  AhoFail(globals);//fail back to find mmore possibilities
	  }
	//set the failstate for the next member

	statiStK->failState = globals->Current;

printf("The output value for '%c' ::: '%s' before strcpy is called\n",statiStK->stateChar,statiStK->output );
	//combine the outputs!
	int x = 0;
	char tempoChar = globals->Current->output[0];
	int k = statiStK->outputCount;
	while(tempoChar != '\0'){
	  tempoChar = globals->Current->output[x];
	  statiStK->output[x + k] = globals->Current->output[x];
	  x++;
	  } 
printf("output value for %c set to the value of ::: '%s' \n",  statiStK->stateChar,statiStK->output); 
printf("	set s: '%c'%d ~~~~ to fail to: '%c'%d \n", statiStK->stateChar, statiStK->ID, statiStK->failState->stateChar, statiStK->failState->ID);

	statiStK  = statiStK->siblingState;

	if(statiStK != NULL){
		printf("pter? %p\n", statiStK);
	}
    }

printf("    exit inner while-loop\n");

  }
printf("    exit outer while-loop\n");
}

//Queue push
void pushStQ(State *addState){
  if(stateQueue == NULL){
printf("STATE QUEEUE NULLLLLL============\n");
    stateQueue = endStQ;
  }

  endStQ->id = malloc(sizeof(State*));
  endStQ->id = addState;

  endStQ->nextQ = malloc(sizeof(QueueSt *));
  endStQ = endStQ->nextQ;
}

//Queue pop
void popStQ(){

  if(curStQ->nextQ != NULL){
    curStQ = curStQ->nextQ;
    stateQueue = curStQ;
  }else{
    stateQueue = NULL;
  }
}
