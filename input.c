/*
*File input for the AC and PFAC algorithms
*
*Martin J Smith
*/

#include "ac.h"

//Main, start the program
int main(){
patternCollection();

return 0;
}

/*
*Function used to obtain the different patterns used from matching from a file
*This is what is used to build the state machine.
*/
void patternCollection(){

int numPats = 0; 
int ctLen = 0;
int lngLen = 0;
char temChar;
FILE *pattFP = fopen("patternHold.txt", "r"); 

//Get the number of lines in the file as well as the length of the longest pattern for array sizing purposes
while(temChar != EOF){
  ctLen++;
  temChar=fgetc(pattFP);
  if(temChar == '\n'){
    numPats++;
    if(ctLen > lngLen){
	lngLen = ctLen;
	ctLen = 0;
    }
  }
}

fclose(pattFP);

printf("lnglensize %d\n", lngLen);
//For some reason, need to open up another instance of the file to read in properly.
FILE *pattFP2 = fopen("patternHold.txt","r");

char **patternStore = malloc(sizeof(char*) * numPats);

int i;

//read in the lines of the file
for(i = 0; i < numPats; i++){
  patternStore[i] = malloc(sizeof(char) * lngLen);
  fgets(patternStore[i], lngLen, pattFP2);
  }

fclose(pattFP2);

printf("read patfile\n");

AhoAlgo(patternStore, numPats);

}



























































































