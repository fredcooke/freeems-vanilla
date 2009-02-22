#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

int main( int argc, char *argv[] ){
	if(argc == 1){
		puts("No argument supplied!! Please supply a file to parse.");
	}else if(argc == 2){
		FILE *inputFile;
		inputFile = fopen(argv[1], "rb");

		/* Could not open file */
		if(inputFile == NULL){
			printf("Error opening file %s, please check the name and try again!\n", argv[1]);
			return 1;
		}

		fseek(inputFile, 0L, SEEK_END);
		int length = ftell(inputFile);
		rewind(inputFile);
		printf("The length of file %s is %u\n\n", argv[1], length);
		printf("Attempting to parse file...\n");

		int processed = 0;
		int packets = 0;
		int charsDropped = 0;
		int badChecksums = 0;
		while(processed < length){
			processed++;
			unsigned char character = fgetc(inputFile);
			if(character != 0xAA){
				charsDropped++;
			}else{
				packets++;
				//do{
					// get char
					// add to checksum
					// look for end byte
					// remember last byte such that when end found correct checksum can be generated.
				//}while(char is not 0xCC);
			}
		}

		printf("There were %u chars dropped and %u packets of which %u had bad checksums.\n", charsDropped, packets, badChecksums);
		//				fgetc(input
	}else{
		/* Subtract one to eliminate command name. */
		printf("Wrong number of arguments!! Was %u should be 1...\n", argc - 1);
	}
	return 0; // non-zero = error
}

