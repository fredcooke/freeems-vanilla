#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

int main( int argc, char *argv[] ){
	if(argc == 1){
		puts("No argument supplied!! Please supply a file to parse.");
	}else if(argc == 2){
		FILE *inputFilePtr;
		inputFilePtr = fopen(argv[1], "rb");

		/* Could not open file */
		if(inputFilePtr == NULL){
			printf("Error opening file %s, please check the name and try again!\n", argv[1]);
			return 1;
		}

		fseek(inputFilePtr, 0L, SEEK_END);
		int lFileLen = ftell(inputFilePtr);
		rewind(inputFilePtr);
		printf("The length of file %s is %u\n", argv[1], lFileLen);
		//				fgetc(input
	}else{
		/* Subtract one to eliminate command name. */
		printf("Wrong number of arguments!! Was %u should be 1...\n", argc - 1);
	}
	return 0; // non-zero = error
}

