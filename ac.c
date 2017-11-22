/*
*The main method for the AC algorithm, also the goto, fail, and output functions
*
*Martin J Smith
*/

#include "ac.h"

//the main processing loop for the aho corasick algorithm.
void AhoProcess(AhoVars *globals){

FILE *processFile = fopen("bigData.txt", "r");
char **inputEvals = malloc(sizeof(char* ) * 151000);

int k = 0;
inputEvals[k] = malloc(sizeof(char) * 200);
//printf("inputEval entry %s\n", inputEvals[k]);

while(fgets(inputEvals[k], 200, processFile) != NULL){
//printf("inputEval entry %s\n", inputEvals[k]);
k++;
inputEvals[k] = malloc(sizeof(char) * 200);
} 


fclose(processFile);
char *decision = malloc(sizeof(char) * 5);
printf("Input and builing done, continue?: ");
fgets(decision, 5, stdin);

if(decision[0] == 'n'){
printf("goodbye, Senpai\n");
exit(0);
}

FILE *outputFile = fopen("outputAnalysis.txt", "w+");
if(outputFile != NULL)
printf("FIFO outputAnalysis.txt working fine\n");

globals->Current = globals->Machine;

int i, j = 0;

for(j = 0; j < k; j++){
  globals->Current = globals->Machine;

  for(i = 0; i < strlen(inputEvals[j]); i++){

    while(AhoGoTo(globals, globals->Current, inputEvals[j][i]) == 1){
	if(globals->Current->ID == 0){
	  printf("got to I value '%d'\n exited trie because current failed to state 0\n", i);
	  break;
	}

	AhoFail(globals);
    }
	   
    fprintf(outputFile, "%s ", AhoOutPut(globals));

  }
fprintf(outputFile,"\n");
}


fclose(outputFile);
exit(0);

}

/*
* function that gives back the output of the current node
*/
char *AhoOutPut(AhoVars *globals){

  return globals->Current->output;
}

/**
*The call the various builder functions, then the main loop of the Aho Corasick algorithm
*/
void AhoAlgo(char **patterns, int patNum){

//globals struct declaration
AhoVars *globals = malloc(sizeof(AhoVars *));
globals->Machine = malloc(sizeof(State *));
globals->IDcounter = 0;

AhoBuildGoto(globals, patterns, patNum); //build the GoTo Trie, start building output
printf("Goto Function Built\n");
int i = 0;


for(i = 0; i < patNum; i++){
  printf("'I got it, I got it' - Mogg Fanatic: %s", patterns[i]);
  } 


AhoBuildFail(globals);  //put in the failstates for each node in the Trie, finish the output building
printf("Fail Traces Added\n");

for(i = 0; i < patNum; i++){
  printf("'I got it, I got it' - Mogg Fanatic: %s", patterns[i]);
  } 


AhoProcess(globals); //the main processing 

}

/**
*The Fail function for the AC algorithm
*/
void AhoFail(AhoVars *globals){

  globals->Current = globals->Current->failState;

}


/**
*The GOTO function for the AC algorithm
*returns 1 if fail, 0 if pass
*/
int AhoGoTo(AhoVars *globals, State *start, char next){

//see if the decendant is a match, if so return, else cycle through the sibling states!
if(start->childState != NULL){

  if(start->childState->stateChar == next){
    globals->Current = start->childState;
    return 0;   
    }
  else{ //sibling cycling 
    if(start->childState->siblingState != NULL){
      start = start->childState;
      while(start != NULL){
	  if(start->stateChar == next){
	    globals->Current = start;
	    return 0;
	  }else{
       	    start = start->siblingState;
	    }
        }
      }
    }
  }

return 1;

}
