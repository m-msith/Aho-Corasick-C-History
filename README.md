# Aho-Corasick-C
Novel Implementation of the Aho-Corasick pattern matching algorithm in C.
Developed by Martin J Smith on Linux Mint (x64) with an AMD A-10 5800k, 8GB of RAM.

To compile, have make installed as well as gcc. Simply navigate to the direcory containing the project and makefile and type
"make", minus quotations. The makefile will produce a binary file called "ac". Patterns should be held in "patternHold.txt" and
the text to search should be held in "bigData.txt". Output will be placed in "outputAnalysis.txt" which will report found output
strings on a line-by-line basis matching up with the lines in "bigData.txt". 

To run the binary, navigate to its directory via command line and type "./ac", then press the Enter key. When asked to continue,
type "n" and press enter to not continue, otherwise, type "y" and press enter.

Planned changes/feature additions include:
-Removal of the static sized output array in the State data structure, replacing with another linked list for dynamic sizing

-Streamlining and improving user interaction as well as general i/o and reporting fixes 

-Improving comments and formatting

-Conditional compilation for debug messages/having a 'production' branch with no debugging prints

-General inevetable bug corrections and patching the probably prolific memory leaks that have yet to show up 
