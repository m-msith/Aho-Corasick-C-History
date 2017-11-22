/**
*This is the Hfile for the Aho Corasick algorithm developed by Alfred Aho and Margaret Corasick.
*
*The file contains all referenced libraries, global variables, and prototypes used for the Aho Corasick algorithm as well as some for the Parallel *Failureless Aho Corasick - developed by Chen et al.
*
*Coded By: Martin J Smith
*Project Mentor: Dr. Thomas Briggs
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OUTSIZE 100 //determined by max output pattern length, need to make array linked list
#define PRINT 0

//The state Struct
typedef struct State{
char stateChar;
int ID;
int outputCount;
char output[OUTSIZE];
struct State *childState;
struct State *siblingState;
struct State *failState;
}State;

//Global vars Struct
typedef struct AhoVars{
State *Machine; //the patternTrie
State *Current; //the current state

int IDcounter; //counts the created inputs from 0 to n
}AhoVars;

//Fuction prototypes

//Main loop for the AC algorithm :: ac.c
void AhoAlgo(char **patterns, int patNum);

//Processing loop for the AC algorithm :: ac.c
void AhoProcess(AhoVars *globals);

//The patternCollection is the basic input function that grabs all relevant pattern match information from file
void patternCollection();

char *AhoOutPut(AhoVars *globals);

//The goto function for the AC algorithm - from current state to next character
int AhoGoTo(AhoVars *globals, State *start, char next); //ac.c

//The fail function for the AC algorithm - sets current state to the failure state.
void AhoFail(AhoVars *globals);

//The encode and AhoBuildGoto functions handle putting desired strings into the pattern trie
//AhoBuildFail goes through the trie and sets the failure values
void encode(AhoVars *globals, char *pattern, int count); //gotoBuild.c
void AhoBuildGoto(AhoVars *globals, char **patterns, int patNum); //gotoBuild.c
void AhoBuildFail(AhoVars *globals); //failureBuild.c


